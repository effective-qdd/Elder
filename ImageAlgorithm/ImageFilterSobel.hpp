/**
* \file ImageFilterSobel.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.05
*/
#ifndef _IMAGE_FILTER_SOBEL_H
#define _IMAGE_FILTER_SOBEL_H

// My Class Includes
#include "ImageFilterBase.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageSubConstant.hpp"
#include "../ImageOperator/ImageMulConstant.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			/// \brief CSobel.
			class CSobel : public IFilter
			{
			public:
				CSobel()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_maskSize(0)
					, m_buf8u(nullptr)
				{}

				/// \brief Free buffer for all subclass.
				virtual ~CSobel()
				{
					if (m_buf8u != nullptr)
					{
						ippsFree(m_buf8u);
						m_buf8u = nullptr;
					}
				}

				/// \brief Initialize CSobel params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, int kernelSize)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size					m_imageSize;
				int						m_maskSize;
				IppiMaskSize			m_ippMaskSize;
				Ipp8u*					m_buf8u;
				std::mutex				m_mutex;
			};


			/// \brief CSobel8u1c.
			class CSobel8u1c : public CSobel
			{
			public:
				CSobel8u1c()
					: CSobel()
					, m_tmpBuf16s1c(nullptr)
					, m_tmpBufWidthBytes(0)
					, m_tmpBuf32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CSobel8u1c()
				{
					if (m_tmpBuf16s1c != nullptr)
					{
						ippFree(m_tmpBuf16s1c);
						m_tmpBuf16s1c = nullptr;
					}
				}

				void Initialize(Size imageSize, int maskSize)
				{
					ENSURE_THROW_MSG(maskSize == 3 ||
						maskSize == 5,
						"Unsupported Mask Size");
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						m_ippMaskSize = ippMskSize3x3;
						if (m_maskSize == 5)
							m_ippMaskSize = ippMskSize5x5;
				
						int bufferSize = 0;
						auto status = ippiFilterSobelGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							m_ippMaskSize,
							ippNormL1,
							ipp8u,
							ipp16s,
							1,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterSobelGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						if (m_tmpBuf16s1c != nullptr) ippsFree(m_tmpBuf16s1c);
						m_tmpBuf16s1c = ippiMalloc_16s_C1(m_imageSize.width, m_imageSize.height, &m_tmpBufWidthBytes);

						m_tmpBuf32f1c->Initialize(m_imageSize.width, m_imageSize.height);
					}
				}

				bool  Apply(std::any const& imageIn, std::any const& imageOut) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					auto status = ippiFilterSobel_8u16s_C1R
					(
						src->Data(),
						src->WidthBytes(),
						m_tmpBuf16s1c,
						m_tmpBufWidthBytes,
						{ m_imageSize.width, m_imageSize.height },
						m_ippMaskSize,
						ippNormL1,
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterSobel_8u16s_C1R failed!");

					status = ippiConvert_16s32f_C1R
					(
						m_tmpBuf16s1c,
						m_tmpBufWidthBytes,
						m_tmpBuf32f1c->Data(),
						m_tmpBuf32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16s32f_C1R failed!");

					float min = 0.0f;
					float max = 0.0f;
					status = ippiMinMax_32f_C1R
					(
						m_tmpBuf32f1c->Data(),
						m_tmpBuf32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						&min,
						&max
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMinMax_32f_C1R failed!");

					status = ippiScale_32f8u_C1R
					(
						m_tmpBuf32f1c->Data(),
						m_tmpBuf32f1c->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						min,
						max
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiScale_32f8u_C1R failed!");

					return true;
				}

			private:
				Ipp16s* m_tmpBuf16s1c;
				int m_tmpBufWidthBytes;
				std::shared_ptr<CImage32f1cIPPI> m_tmpBuf32f1c;
			};


			/// \brief CSobel16u1c.
			class CSobel16u1c : public CSobel
			{
			public:
				CSobel16u1c()
					: CSobel()
					, m_tmpBuf32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CSobel16u1c() = default;

				void Initialize(Size imageSize, int maskSize)
				{
					ENSURE_THROW_MSG(maskSize == 3 ||
						maskSize == 5,
						"Unsupported Mask Size");

					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						m_ippMaskSize = ippMskSize3x3;
						if (m_maskSize == 5)
							m_ippMaskSize = ippMskSize5x5;

						int bufferSize = 0;
						auto status = ippiFilterSobelGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							m_ippMaskSize,
							ippNormL1,
							ipp16u,
							ipp32f,
							1,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterSobelGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						m_tmpBuf32f1c->Initialize(m_imageSize.width, m_imageSize.height);
					}
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					auto status = ippiFilterSobel_16u32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						m_tmpBuf32f1c->Data(),
						m_tmpBuf32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippMaskSize,
						ippNormL1,
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterSobel_16u32f_C1R failed!");

					float min = 0.0f;
					float max = 0.0f;
					status = ippiMinMax_32f_C1R
					(
						m_tmpBuf32f1c->Data(),
						m_tmpBuf32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						&min,
						&max
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMinMax_32f_C1R failed!");

					if (abs(max - min) > kEpsinon32)
					{
						auto k = (65535.0f - 0.0f) / (max - min);
						OPERATOR::CImageSubConstant<OPERATOR::CSubConstant32f1c>::SubConstant(m_tmpBuf32f1c, min);
						OPERATOR::CImageMulConstant<OPERATOR::CMulConstant32f1c>::MulConstant(m_tmpBuf32f1c, k);
					}
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_tmpBuf32f1c, dst);

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_tmpBuf32f1c;
			};


			/// \brief CSobel32f1c.
			class CSobel32f1c : public CSobel
			{
			public:
				CSobel32f1c()
					: CSobel()
				{}

				~CSobel32f1c() = default;

				void Initialize(Size imageSize, int maskSize)
				{
					ENSURE_THROW_MSG(maskSize == 3 ||
						maskSize == 5,
						"Unsupported Mask Size");

					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						m_ippMaskSize = ippMskSize3x3;
						if (m_maskSize == 5)
							m_ippMaskSize = ippMskSize5x5;

						int bufferSize = 0;
						auto status = ippiFilterSobelGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							m_ippMaskSize,
							ippNormL1,
							ipp32f,
							ipp32f,
							1,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterSobelGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");
					}

				}

				bool Apply(std::any const& imageIn, std::any const& imageOut) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_srcImgSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_srcImgSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					auto status = ippiFilterSobel_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippMaskSize,
						ippNormL1,
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterSobel_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}
#endif
