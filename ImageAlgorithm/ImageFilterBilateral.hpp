/**
* \file ImageFilterBilateral.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.05
*/
#ifndef _IMAGE_FILTER_BILATERAL_H
#define _IMAGE_FILTER_BILATERAL_H

// My Class Includes
#include "ImageFilterBase.hpp"
#include "../ImageOperator/ImageConvert.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			/// \brief CBilateral.
			class CBilateral : public IFilter
			{
			public:
				CBilateral()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_spec(nullptr)
					, m_buf8u(nullptr)
				{}

				/// \brief Free buffer for all subclass.
				virtual ~CBilateral()
				{
					if (m_spec != nullptr)
					{
						ippFree(m_spec);
						m_spec = nullptr;
					}
					if (m_buf8u != nullptr)
					{
						ippsFree(m_buf8u);
						m_buf8u = nullptr;
					}
				}

				/// \brief Initialize CBilateral params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size						m_imageSize;
				IppiFilterBilateralSpec*	m_spec;
				Ipp8u*						m_buf8u;
				std::mutex					m_mutex;
			};


			/// \brief CBilateral8u1c.
			class CBilateral8u1c : public CBilateral
			{
			public:
				CBilateral8u1c()
					: CBilateral()
				{}

				~CBilateral8u1c() = default;

				void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
						
						int specSize = 0;
						int bufferSize = 0;
						auto status = ippiFilterBilateralBorderGetBufferSize
						(
							ippiFilterBilateralGauss,
							{ m_imageSize.width, m_imageSize.height },
							1,
							ipp8u,
							1,
							ippDistNormL1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBilateralBorderGetBufferSize failed!");

						if (m_spec != nullptr) ippFree(m_spec);
						m_spec = (IppiFilterBilateralSpec*)ippMalloc(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						status = ippiFilterBilateralBorderInit
						(
							ippiFilterBilateralGauss,
							{ m_imageSize.width, m_imageSize.height },
							1,
							ipp8u,
							1,
							ippDistNormL1,
							400.0f,
							100.0f,
							m_spec
						);
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
					Ipp8u borderValue = 0;
					auto status = ippiFilterBilateralBorder_8u_C1R
					(
						src->Data() + src->WidthBytes(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						static_cast<IppiBorderType>(ippBorderRepl | ippBorderInMemTop | ippBorderInMemRight),
						&borderValue,
						m_spec,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBilateralBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CBilateral16u1c.
			class CBilateral16u1c : public CBilateral
			{
			public:
				CBilateral16u1c()
					: CBilateral()
					, m_srcImage32f1c(std::make_shared<CImage32f1cIPPI>())
					, m_dstImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CBilateral16u1c() = default;

				void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;

						int specSize = 0;
						int bufferSize = 0;
						auto status = ippiFilterBilateralBorderGetBufferSize
						(
							ippiFilterBilateralGauss,
							{ m_imageSize.width, m_imageSize.height },
							1,
							ipp32f,
							1,
							ippDistNormL1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBilateralBorderGetBufferSize failed!");

						if (m_spec != nullptr) ippFree(m_spec);
						m_spec = (IppiFilterBilateralSpec*)ippMalloc(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						status = ippiFilterBilateralBorderInit
						(
							ippiFilterBilateralGauss,
							{ m_imageSize.width, m_imageSize.height },
							1,
							ipp32f,
							1,
							ippDistNormL1,
							400.0f,
							100.0f,
							m_spec
						);

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
					Ipp32f borderValue = 0.0f;
					auto status = ippiFilterBilateralBorder_32f_C1R
					(
						m_srcImage32f1c->Data() + src->WidthBytes(),
						m_srcImage32f1c->WidthBytes(),
						m_dstImage32f1c->Data(),
						m_dstImage32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						static_cast<IppiBorderType>(ippBorderRepl | ippBorderInMemTop | ippBorderInMemRight),
						&borderValue,
						m_spec,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBilateralBorder_32f_C1R failed!");
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_dstImage32f1c, dst);

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_srcImage32f1c;
				std::shared_ptr<CImage32f1cIPPI> m_dstImage32f1c;
			};


			/// \brief CBilateral32f1c.
			class CBilateral32f1c : public CBilateral
			{
			public:
				CBilateral32f1c()
					: CBilateral()
				{}

				~CBilateral32f1c() = default;

				void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;

						int specSize = 0;
						int bufferSize = 0;
						auto status = ippiFilterBilateralBorderGetBufferSize
						(
							ippiFilterBilateralGauss,
							{ m_imageSize.width, m_imageSize.height },
							1,
							ipp32f,
							1,
							ippDistNormL1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBilateralBorderGetBufferSize failed!");

						if (m_spec != nullptr) ippFree(m_spec);
						m_spec = (IppiFilterBilateralSpec*)ippMalloc(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						status = ippiFilterBilateralBorderInit
						(
							ippiFilterBilateralGauss,
							{ m_imageSize.width, m_imageSize.height },
							1,
							ipp32f,
							1,
							ippDistNormL1,
							400.0f,
							100.0f,
							m_spec
						);
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
					Ipp32f borderValue = 0.0f;
					auto status = ippiFilterBilateralBorder_32f_C1R
					(
						src->Data() + src->WidthBytes(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						static_cast<IppiBorderType>(ippBorderRepl | ippBorderInMemTop | ippBorderInMemRight),
						&borderValue,
						m_spec,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBilateralBorder_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}
#endif
