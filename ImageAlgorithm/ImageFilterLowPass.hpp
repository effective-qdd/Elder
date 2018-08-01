/**
* \file ImageFilterLowPass.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.06.11
*/
#ifndef _IMAGE_FILTER_LOW_PASS_H
#define _IMAGE_FILTER_LOW_PASS_H


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
			/// \brief CLowPass.
			class CLowPass : IFilter
			{
			public:
				CLowPass()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_maskSize(0)
					, m_buf8u(nullptr)
				{

				}

				/// \brief Free buffer for all subclass.
				virtual ~CLowPass()
				{
					if (m_buf8u != nullptr)
					{
						ippsFree(m_buf8u);
						m_buf8u = nullptr;
					}
				}

				/// \brief Initialize CLowPass params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, int maskSize)
				{
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size			m_imageSize;
				int				m_maskSize;
				IppiMaskSize	m_ippMaskSize;
				Ipp8u*			m_buf8u;
				std::mutex		m_mutex;
			};


			/// \brief CLowPass8u1c.
			class CLowPass8u1c : public CLowPass
			{
			public:
				CLowPass8u1c()
					: CLowPass()
				{}

				~CLowPass8u1c() = default;

				void Initialize(Size imageSize, int maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						m_ippMaskSize = ippMskSize3x3;
						if (m_maskSize == 5)
							m_ippMaskSize = ippMskSize5x5;

						int bufferSize = 0;
						auto status = ippiFilterLowpassGetBufferSize_8u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							m_ippMaskSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterLowpassGetBufferSize_8u_C1R failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");
					}
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut) override
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
					auto status = ippiFilterLowpassBorder_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippMaskSize,
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterLowpassBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CLowPass16u1c.
			class CLowPass16u1c : public CLowPass
			{
			public:
				CLowPass16u1c()
					: CLowPass()
					, m_srcImage32f1c(std::make_shared<CImage32f1cIPPI>())
					, m_dstImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CLowPass16u1c() = default;

				void Initialize(Size imageSize, int maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						m_ippMaskSize = ippMskSize3x3;
						if (m_maskSize == 5)
							m_ippMaskSize = ippMskSize5x5;

						int bufferSize = 0;
						auto status = ippiFilterLowpassGetBufferSize_32f_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							m_ippMaskSize,							
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterLowpassGetBufferSize_32f_C1R failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						m_srcImage32f1c->Initialize(m_imageSize.width, m_imageSize.height);
						m_dstImage32f1c->Initialize(m_imageSize.width, m_imageSize.height);
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
					OPERATOR::CImageConvert<OPERATOR::CConvert16u1cTo32f1c>::Convert(src, m_srcImage32f1c);
					auto status = ippiFilterLowpassBorder_32f_C1R
					(
						m_srcImage32f1c->Data(),
						m_srcImage32f1c->WidthBytes(),
						m_dstImage32f1c->Data(),
						m_dstImage32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippMaskSize,
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterLowpassBorder failed!");
					
					float min = 0.0f;
					float max = 0.0f;
					status = ippiMinMax_32f_C1R
					(
						m_dstImage32f1c->Data(),
						m_dstImage32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						&min,
						&max
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMinMax_32f_C1R failed!");

					if (abs(max - min) > kEpsinon32)
					{
						auto k = (65535.0f - 0.0f) / (max - min);
						OPERATOR::CImageSubConstant<OPERATOR::CSubConstant32f1c>::SubConstant(m_dstImage32f1c, min);
						OPERATOR::CImageMulConstant<OPERATOR::CMulConstant32f1c>::MulConstant(m_dstImage32f1c, k);
					}
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_dstImage32f1c, dst);

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_srcImage32f1c;
				std::shared_ptr<CImage32f1cIPPI> m_dstImage32f1c;
			};


			/// \brief CLowPass32f1c.
			class CLowPass32f1c : public CLowPass
			{
			public:
				CLowPass32f1c()
					: CLowPass()
				{}

				~CLowPass32f1c() = default;

				void Initialize(Size imageSize, int maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						m_ippMaskSize = ippMskSize3x3;
						if (m_maskSize == 5)
							m_ippMaskSize = ippMskSize5x5;

						int bufferSize = 0;
						auto status = ippiFilterLowpassGetBufferSize_32f_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							m_ippMaskSize,							
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterLowpassGetBufferSize_32f_C1R failed!");

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
					auto status = ippiFilterLowpassBorder_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippMaskSize,
						ippBorderRepl,
						0.0f,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterLowpassBorder_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}
#endif
