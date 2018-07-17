/**
* \file ImageHistogramLocal.hpp
* \brief It seems a little slow. 
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.15
*/
#ifndef _IMAGE_INTENSITY_HISTOGRAM_LOCAL_H
#define _IMAGE_INTENSITY_HISTOGRAM_LOCAL_H


// My Class Includes
#include "ImageIntensityBase.hpp"

#include "../ImageOperator/ImageMeanStdDev.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CHistogramLocal
			/// s = c(r)^y;
			class CHistogramLocal : public IIntensity
			{
			public:
				CHistogramLocal()
					: IIntensity()
					, m_imageSize{ 0, 0 }
				{

				}

				virtual ~CHistogramLocal()
				{

				}

				virtual void Initialize(Size imageSize, float e = 4.0f, float k0 = 0.4f, float k1 = 0.02f, float k2 = 0.4f)
				{
					m_imageSize = imageSize;
					SetParams(e, k0, k1, k2);
				}

				virtual void SetParams(float e, float k0, float k1, float k2)
				{
					m_e = e;
					m_k0 = k0;
					m_k1 = k1;
					m_k2 = k2;
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size	m_imageSize;
				float	m_e;
				float	m_k0;
				float	m_k1;
				float	m_k2;
				std::mutex m_mutex;
			};


			/// \brief CHistogramLocal8u1c.
			class CHistogramLocal8u1c : public CHistogramLocal
			{
			public:
				CHistogramLocal8u1c()
					: CHistogramLocal()
				{

				}

				~CHistogramLocal8u1c()
				{

				}


				bool Apply(std::any const& imageIn, std::any const& imageOut) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(src->Data() != nullptr, "imageIn data ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(dst->Data() != nullptr, "imageOut data ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					double srcMean = 0.0;
					double srcStdDev = 0.0;
					OPERATOR::CImageMeanStdDev<OPERATOR::CMeanStdDev8u1c>::MeanStdDev(src, srcMean, srcStdDev);
					//auto srcData = src->Data();
					//auto dstData = dst->Data();
					auto srcWidthBytes = src->WidthBytes();
					auto dstWidthBytes = dst->WidthBytes();
					auto ippiSize = IppiSize{ 3, 3 };
					double localMean = 0.0;
					double localStdDev = 0.0;
					for (auto y = 0; y < m_imageSize.height; ++y)
					{
						for (auto x = 0; x < m_imageSize.width; ++x)
						{
							auto srcData = src->Data() + x + y * srcWidthBytes;
							auto dstData = dst->Data() + x + y * dstWidthBytes;
							if (x <= (m_imageSize.width - ippiSize.width) && y <= (m_imageSize.height - ippiSize.height))
							{
								IppStatus status = ippiMean_StdDev_8u_C1R
								(
									srcData,
									srcWidthBytes,
									ippiSize,
									&localMean,
									&localStdDev
								);
							}

							if ((localMean <= m_k0 * srcMean) && (localStdDev >= m_k1 * srcStdDev) && (localStdDev <= m_k2 * srcStdDev))
							{
								*dstData = static_cast<unsigned char>((*srcData) * m_e);
							}
							else
							{
								*dstData = *srcData;
							}

						}
					}

					return true;
				}
			};

			/// \brief CHistogramLocal16u1c.
			class CHistogramLocal16u1c : public CHistogramLocal
			{
			public:
				CHistogramLocal16u1c()
					: CHistogramLocal()
				{

				}

				~CHistogramLocal16u1c()
				{

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
					double srcMean = 0.0;
					double srcStdDev = 0.0;
					OPERATOR::CImageMeanStdDev<OPERATOR::CMeanStdDev16u1c>::MeanStdDev(src, srcMean, srcStdDev);
					auto srcData = src->Data();
					auto dstData = dst->Data();
					auto srcWidthStep = static_cast<int>(src->WidthBytes() / sizeof(unsigned short));
					auto dstWidthStep = static_cast<int>(dst->WidthBytes() / sizeof(unsigned short));
					auto ippiSize = IppiSize{ 3, 3 };
					double localMean = 0.0;
					double localStdDev = 0.0;
					for (auto y = 0; y < m_imageSize.height; ++y)
					{
						for (auto x = 0; x < m_imageSize.width; ++x)
						{
							srcData = src->Data() + x + y * srcWidthStep;
							dstData = dst->Data() + x + y * dstWidthStep;
							if (x <= (m_imageSize.width - ippiSize.width) && y <= (m_imageSize.height - ippiSize.height))
							{
								IppStatus status = ippiMean_StdDev_16u_C1R
								(
									srcData,
									srcWidthStep,
									ippiSize,
									&localMean,
									&localStdDev
								);
							}
							if ((localMean <= m_k0 * srcMean) && (localStdDev >= m_k1 * srcStdDev) && (localStdDev <= m_k2 * srcStdDev))
							{
								*dstData = static_cast<unsigned char>((*srcData) * m_e);
							}
							else
							{
								*dstData = *srcData;
							}

						}
					}

					return true;
				}
			};
		}
	}
}
#endif
