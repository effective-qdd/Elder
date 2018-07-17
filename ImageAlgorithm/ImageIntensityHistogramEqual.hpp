/**
* \file ImageHistogramEqualization.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.15
*/
#ifndef _IMAGE_INTENSITY_HISTOGRAM_EQUALIZATION_H
#define _IMAGE_INTENSITY_HISTOGRAM_EQUALIZATION_H


// My Class Includes
#include "ImageIntensityBase.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CHistogramEqualization
			class CHistogramEqualization : public IIntensity
			{
			public:
				CHistogramEqualization()
					: IIntensity()
					, m_imageSize{ 0, 0 }
					, m_factor(0.0f)
					, m_histObjSize(0)
					, m_bufferSize(0)
					, m_histObj(nullptr)
					, m_buffer(nullptr)
					, m_hist(nullptr)
				{

				}

				virtual ~CHistogramEqualization()
				{
					if (m_histObj != nullptr)
					{
						ippsFree(m_histObj);
						m_histObj = nullptr;
					}
					if (m_buffer != nullptr)
					{
						ippsFree(m_buffer);
						m_buffer = nullptr;
					}
					if (m_hist != nullptr)
					{
						delete[] m_hist;
						m_hist = nullptr;
					}
				}

				virtual void Initialize(Size imageSize)
				{
					m_imageSize = imageSize;
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;
				float m_factor;
				int m_histObjSize;
				int m_bufferSize;
				IppiHistogramSpec* m_histObj;
				Ipp8u* m_buffer;
				unsigned int* m_hist;
			};


			/// \brief CHistogramEqualization8u1c.
			class CHistogramEqualization8u1c : public CHistogramEqualization
			{
				const int kBitDepth = 8;

			public:
				CHistogramEqualization8u1c()
					: CHistogramEqualization()
					, m_LUT(nullptr)
					, m_levels(1 << kBitDepth)
				{

				}

				~CHistogramEqualization8u1c()
				{
					if (m_LUT != nullptr)
					{
						delete[] m_LUT;
						m_LUT = nullptr;
					}
				}

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						CHistogramEqualization::Initialize(imageSize);

						auto status = ippiHistogramGetBufferSize
						(
							ipp8u,
							{ m_imageSize.width, m_imageSize.height },
							&m_levels,
							1,
							1,
							&m_histObjSize,
							&m_bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiHistogramGetBufferSize failed!");

						if (m_histObj != nullptr) ippFree(m_histObj);
						m_histObj = (IppiHistogramSpec*)ippsMalloc_8u(m_histObjSize);

						if (m_buffer != nullptr) ippsFree(m_buffer);
						m_buffer = (Ipp8u*)ippsMalloc_8u(m_bufferSize);

						float lowerLevel = 0;
						float upperLevel = m_levels - 1.0f;

						status = ippiHistogramUniformInit
						(
							ipp8u,
							&lowerLevel,
							&upperLevel,
							&m_levels,
							1,
							m_histObj
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiHistogramUniformInit failed!");

						m_factor = upperLevel / m_imageSize.width / m_imageSize.height;
						Ipp32f* pLevels = new Ipp32f[m_levels];
						memset(pLevels, 0, m_levels * sizeof(Ipp32f));
						status = ippiHistogramGetLevels(m_histObj, &pLevels);
						delete[] pLevels;

						if (m_hist != nullptr) delete[] m_hist;
						m_hist = new unsigned int[m_levels];

						if (m_LUT != nullptr) delete[] m_LUT;
						m_LUT = new Ipp8u[m_levels];
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

					IppStatus status = ippiHistogram_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_hist,
						m_histObj,
						m_buffer
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiHistogram_8u_C1R failed!");

					int sum = 0;

					for (int i = 0; i < m_levels - 1; i++)
					{
						sum += m_hist[i];
						m_LUT[i] = static_cast<Ipp8u>(sum * m_factor);
					}

					status = ippiLUTPalette_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_LUT,
						kBitDepth
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiLUTPalette_8u_C1R failed!");

					return true;
				}

			private:
				Ipp8u *m_LUT;
				int m_levels;
			};


			/// \brief CHistogramEqualization16u1c.
			class CHistogramEqualization16u1c : public CHistogramEqualization
			{
				const int kBitDepth = 16;
			public:
				CHistogramEqualization16u1c()
					: CHistogramEqualization()
					, m_LUT(nullptr)
					, m_levels(1 << kBitDepth)
				{
				}

				~CHistogramEqualization16u1c()
				{
					if (m_LUT != nullptr)
					{
						delete[] m_LUT;
						m_LUT = nullptr;
					}
				}

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						CHistogramEqualization::Initialize(imageSize);

						auto status = ippiHistogramGetBufferSize
						(
							ipp16u,
							{ m_imageSize.width, m_imageSize.height },
							&m_levels,
							1,
							1,
							&m_histObjSize,
							&m_bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiHistogramGetBufferSize failed!");

						if (m_histObj != nullptr) ippFree(m_histObj);
						m_histObj = (IppiHistogramSpec*)ippsMalloc_8u(m_histObjSize);

						if (m_buffer != nullptr) ippsFree(m_buffer);
						m_buffer = (Ipp8u*)ippsMalloc_8u(m_bufferSize);

						float lowerLevel = 0;
						float upperLevel = m_levels - 1.0f;

						status = ippiHistogramUniformInit
						(
							ipp16u,
							&lowerLevel,
							&upperLevel,
							&m_levels,
							1,
							m_histObj
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiHistogramUniformInit failed!");

						m_factor = upperLevel / m_imageSize.width / m_imageSize.height;
						Ipp32f* pLevels = new Ipp32f[m_levels];
						memset(pLevels, 0, m_levels * sizeof(Ipp32f));
						status = ippiHistogramGetLevels(m_histObj, &pLevels);
						delete[] pLevels;

						if (m_hist != nullptr) delete[] m_hist;
						m_hist = new unsigned int[m_levels];

						if (m_LUT != nullptr) delete[] m_LUT;
						m_LUT = new Ipp16u[m_levels];
					}
				}

				bool  Apply(std::any const& imageIn, std::any const& imageOut) override
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

					auto status = ippiHistogram_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_hist,
						m_histObj,
						m_buffer
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiHistogram_16u_C1R failed!");

					int sum = 0;
					for (int i = 0; i < m_levels; i++)
					{
						sum += m_hist[i];
						m_LUT[i] = static_cast<Ipp16u>(sum * m_factor);
					}

					status = ippiLUTPalette_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_LUT,
						kBitDepth
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiLUTPalette_16u_C1R failed!");

					return true;
				}

			private:
				Ipp16u *m_LUT;
				int m_levels;
			};
		}
	}
}
#endif
