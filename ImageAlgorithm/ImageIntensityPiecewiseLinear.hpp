/**
* \file ImagePiecewiseLinear.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.15
*/
#ifndef _IMAGE_INTENSITY_PIECEWISE_LINEAR_H
#define _IMAGE_INTENSITY_PIECEWISE_LINEAR_H

// My Class Includes
#include "ImageIntensityBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CPiecewiseLinear
			class CPiecewiseLinear : public IIntensity
			{
			public:
				CPiecewiseLinear()
					: IIntensity()
					, m_imageSize{ 0, 0 }
					, m_lowIn(0)
					, m_lowOut(0)
					, m_highIn(0)
					, m_highOut(0)
				{

				}

				virtual ~CPiecewiseLinear()
				{

				}

				virtual void Initialize(Size imageSize, int lowIn, int lowOut, int hightIn, int highOut)
				{

				}

				virtual void SetPiecewisePoint(int lowIn, int lowOut, int hightIn, int highOut)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;
				int m_lowIn;
				int m_lowOut;
				int m_highIn;
				int m_highOut;
				std::mutex m_mutex;
			};


			/// \brief CPiecewiseLinear8u1c.
			class CPiecewiseLinear8u1c : public CPiecewiseLinear
			{
			public:
				CPiecewiseLinear8u1c()
					: CPiecewiseLinear()
					, m_table8u(nullptr)
				{
					m_table8u = new Ipp8u[kLevelsIntensity8u];
					memset(m_table8u, 0, kLevelsIntensity8u);
				}

				~CPiecewiseLinear8u1c()
				{
					if (m_table8u != nullptr)
					{
						delete[] m_table8u;
						m_table8u = nullptr;
					}
				}

				void Initialize(Size imageSize, int lowIn = 0, int lowOut = 0, int highIn = kMaxIntensity8u, int highOut = kMaxIntensity8u) override
				{
					m_imageSize = imageSize;
					m_lowIn = lowIn;
					m_lowOut = lowOut;
					m_highIn = highIn;
					m_highOut = highOut;
					BuildLutTable();
				}

				void SetPiecewisePoint(int lowIn, int lowOut, int highIn, int highOut)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if ((m_lowIn != lowIn) || (m_lowOut != lowOut) || (m_highIn != highIn) || (m_highOut != highOut))
					{
						m_lowIn = lowIn;
						m_lowOut = lowOut;
						m_highIn = highIn;
						m_highOut = highOut;
						BuildLutTable();
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
					auto status = ippiLUTPalette_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_table8u,
						8
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiLUTPalette_8u_C1R failed!");

					return true;
				}

			private:
				void BuildLutTable()
				{
					int i = 0;
					// 0 ~ lowIn
					if (m_lowIn != 0)
					{
						float a1 = 1.0f * m_lowOut / m_lowIn;
						for (; i < m_lowIn; ++i)
						{
							m_table8u[i] = (Ipp8u)(i * a1);
						}
					}

					// lowIn ~ highIn
					if (m_highIn != m_lowIn)
					{
						float a2 = 1.0f * (m_highOut - m_lowOut) / (m_highIn - m_lowIn);
						for (; i <= m_highIn; ++i)
						{
							m_table8u[i] = (Ipp8u)(a2 *(i - m_lowIn) + m_lowOut);
						}
					}

					// highIn ~ kMaxIntensity8u
					if (m_highIn != kMaxIntensity8u)
					{
						float a3 = 1.0f * (kMaxIntensity8u - m_highOut) / (kMaxIntensity8u - m_highIn);
						for (; i < kLevelsIntensity8u; ++i)
						{
							m_table8u[i] = (Ipp8u)(a3 * (i - m_highIn) + m_highOut);
						}
					}
				}

			private:
				Ipp8u *m_table8u;
			};

			/// \brief CPiecewiseLinear16u1c.
			class CPiecewiseLinear16u1c : public CPiecewiseLinear
			{
			public:
				CPiecewiseLinear16u1c()
					: CPiecewiseLinear()
					, m_table16u(nullptr)
				{
					m_table16u = new Ipp16u[kLevelsIntensity16u];
					memset(m_table16u, 0, kLevelsIntensity16u * sizeof(Ipp16u));
				}

				~CPiecewiseLinear16u1c()
				{
					if (m_table16u != nullptr)
					{
						delete[] m_table16u;
						m_table16u = nullptr;
					}
				}

				void Initialize(Size imageSize, int lowIn = 0, int lowOut = 0, int highIn = kMaxIntensity16u, int highOut = kMaxIntensity16u) override
				{
					m_imageSize = imageSize;
					m_lowIn = lowIn;
					m_lowOut = lowOut;
					m_highIn = highIn;
					m_highOut = highOut;
					BuildLutTable();
				}

				void SetPiecewisePoint(int lowIn, int lowOut, int highIn, int highOut)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if ((m_lowIn != lowIn) || (m_lowOut != lowOut) || (m_highIn != highIn) || (m_highOut != highOut))
					{
						m_lowIn = lowIn;
						m_lowOut = lowOut;
						m_highIn = highIn;
						m_highOut = highOut;
						BuildLutTable();
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
					auto status = ippiLUTPalette_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_table16u,
						16
					);

					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiLUTPalette_16u_C1R failed!");

					return true;
				}

			private:
				void BuildLutTable()
				{
					int i = 0;
					// 0 ~ lowIn
					if (m_lowIn != 0)
					{
						float a1 = 1.0f * m_lowOut / m_lowIn;
						for (; i < m_lowIn; ++i)
						{
							m_table16u[i] = (Ipp16u)(i * a1);
						}
					}

					// lowIn ~ highIn
					if (m_highIn != m_lowIn)
					{
						float a2 = 1.0f * (m_highOut - m_lowOut) / (m_highIn - m_lowIn);
						for (; i <= m_highIn; ++i)
						{
							m_table16u[i] = (Ipp16u)(a2 * (i - m_lowIn) + m_lowOut);
						}
					}

					// highIn ~ kMaxIntensity16u
					if (kMaxIntensity16u != m_highIn)
					{
						float a3 = 1.0f * (kMaxIntensity16u - m_highOut) / (kMaxIntensity16u - m_highIn);
						for (; i < kLevelsIntensity16u; ++i)
						{
							m_table16u[i] = (Ipp16u)(a3 * (i - m_highIn) + m_highOut);
						}
					}
				}
			private:
				Ipp16u *m_table16u;
			};
		}
	}
}
#endif
