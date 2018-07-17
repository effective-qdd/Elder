/**
* \file ImageFilterMedian.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.05
*/
#ifndef _IMAGE_FILTER_MEDIAN_H
#define _IMAGE_FILTER_MEDIAN_H


// My Class Includes
#include "ImageFilterBase.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			/// \brief CMedian.
			class CMedian : IFilter
			{
			public:
				CMedian()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_maskSize{ 0, 0 }
					, m_buf8u(nullptr)
				{

				}

				/// \brief Free buffer for all subclass.
				virtual ~CMedian()
				{
					if (m_buf8u != nullptr)
					{
						ippsFree(m_buf8u);
						m_buf8u = nullptr;
					}
				}

				/// \brief Initialize CMedian params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, Size maskSize)
				{
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size			m_imageSize;
				Size			m_maskSize;
				Ipp8u*			m_buf8u;
				std::mutex		m_mutex;
			};


			/// \brief CMedian8u1c.
			class CMedian8u1c : public CMedian
			{
			public:
				CMedian8u1c()
					: CMedian()
				{}

				~CMedian8u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						int bufferSize = 0;
						auto status = ippiFilterMedianBorderGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							ipp8u,
							1,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterMedianBorderGetBufferSize failed!");

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
					auto status = ippiFilterMedianBorder_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						{ m_maskSize.width, m_maskSize.height },
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterMedianBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CMedian16u1c.
			class CMedian16u1c : public CMedian
			{
			public:
				CMedian16u1c()
					: CMedian()
				{}

				~CMedian16u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						int bufferSize = 0;
						auto status = ippiFilterMedianBorderGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							ipp16u,
							1,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterMedianBorderGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");
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
					auto status = ippiFilterMedianBorder_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						{ m_maskSize.width, m_maskSize.height },
						ippBorderRepl,
						0,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterMedianBorder_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CMedian32f1c.
			class CMedian32f1c : public CMedian
			{
			public:
				CMedian32f1c()
					: CMedian()
				{}

				~CMedian32f1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						int bufferSize = 0;
						auto status = ippiFilterMedianBorderGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							ipp32f,
							1,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterMedianBorderGetBufferSize failed!");

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
					auto status = ippiFilterMedianBorder_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						{ m_maskSize.width, m_maskSize.height },
						ippBorderRepl,
						0.0f,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterMedianBorder_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}
#endif
