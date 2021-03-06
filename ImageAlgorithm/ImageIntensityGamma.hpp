/**
* \file ImageGamma.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.15
*/
#ifndef _IMAGE_INTENSITY_GAMMA_H
#define _IMAGE_INTENSITY_GAMMA_H


// My Class Includes
#include "ImageIntensityBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CGamma
			/// s = c(r)^y;
			class CGamma : public IIntensity
			{
			public:
				CGamma()
					: IIntensity()
					, m_imageSize{ 0, 0 }
					, m_gammaVal(0.0f)
				{

				}

				virtual ~CGamma()
				{

				}

				virtual void Initialize(Size imageSize, float gammaVal)
				{

				}

				virtual void SetGammaValue(float gammaVal)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size	m_imageSize;
				float	m_gammaVal;
				std::mutex m_mutex;
			};


			/// \brief CGamma8u1c.
			class CGamma8u1c : public CGamma
			{
			public:
				CGamma8u1c()
					: CGamma()
					, m_table8u(nullptr)
				{
					m_table8u = new Ipp8u[kLevelsIntensity8u];
					memset(m_table8u, 0, kLevelsIntensity8u);
				}

				~CGamma8u1c()
				{
					if (m_table8u != nullptr)
					{
						delete[] m_table8u;
						m_table8u = nullptr;
					}
				}

				void Initialize(Size imageSize, float gammaVal = 1.0f) override
				{
					m_imageSize = imageSize;
					m_gammaVal = gammaVal;
					BuildLutTable();
				}

				void SetGammaValue(float gammaVal) override
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (abs(m_gammaVal - gammaVal) > kEpsinon64)
					{
						m_gammaVal = gammaVal;
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
					float fPrecompensation = 1.0f / m_gammaVal;
					float f = 0.0f;
					for (int i = 0; i < kLevelsIntensity8u; i++)
					{
						f = i * 1.0f / (kMaxIntensity8u);
						f = (float)pow(f, fPrecompensation);
						m_table8u[i] = (Ipp8u)(f * kMaxIntensity8u);
					}
				}

			private:
				Ipp8u* m_table8u;
			};

			/// \brief CGamma16u1c.
			class CGamma16u1c : public CGamma
			{
			public:
				CGamma16u1c()
					: CGamma()
					, m_table16u(nullptr)
				{
					m_table16u = new Ipp16u[kLevelsIntensity16u];
					memset(m_table16u, 0, kLevelsIntensity16u * sizeof(Ipp16u));
				}

				~CGamma16u1c()
				{
					if (m_table16u != nullptr)
					{
						delete[] m_table16u;
						m_table16u = nullptr;
					}
				}

				void Initialize(Size imageSize, float gammaVal = 1.0f) override
				{
					m_imageSize = imageSize;
					m_gammaVal = gammaVal;
					BuildLutTable();
				}

				void SetGammaValue(float gammaVal) override
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (abs(m_gammaVal - gammaVal) > kEpsinon64)
					{
						m_gammaVal = gammaVal;
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
					float fPrecompensation = 1.0f / m_gammaVal;
					float f = 0.0f;
					for (int i = 0; i < kLevelsIntensity16u; i++)
					{
						f = i * 1.0f / (kMaxIntensity16u);
						f = pow(f, fPrecompensation);
						m_table16u[i] = (Ipp16u)(f * kMaxIntensity16u);
					}
				}

			private:
				Ipp16u * m_table16u;
			};
		}
	}
}
#endif
