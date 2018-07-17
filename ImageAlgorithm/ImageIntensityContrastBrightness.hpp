/**
* \file ImageContrastBrightness.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.15
*/
#ifndef _IMAGE_INTENSITY_CONTRAST_BRIGHTNESS_H
#define _IMAGE_INTENSITY_CONTRAST_BRIGHTNESS_H


// My Class Includes
#include "ImageIntensityBase.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CContrastBrightness
			class CContrastBrightness : public IIntensity
			{
			public:
				CContrastBrightness()
					: IIntensity()
					, m_imageSize{ 0, 0 }
					, m_contrast(0.0)
					, m_brightness(0.0)
				{

				}

				virtual ~CContrastBrightness()
				{

				}

				virtual void Initialize(Size, double, double)
				{

				}

				/// -1.0 ~ 1.0
				virtual void SetContrastBrightness(double, double)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;
				std::mutex m_mutex;
				double m_contrast;
				double m_brightness;
			};


			/// \brief CContrastBrightness8u1c.
			class CContrastBrightness8u1c : public CContrastBrightness
			{
			public:
				CContrastBrightness8u1c()
					: CContrastBrightness()
					, m_table8u(nullptr)
				{
					m_table8u = new Ipp8u[kLevelsIntensity8u];
					memset(m_table8u, 0, kLevelsIntensity8u);
				}

				~CContrastBrightness8u1c()
				{
					if (m_table8u != nullptr)
					{
						delete[] m_table8u;
						m_table8u = nullptr;
					}
				}

				void Initialize(Size imageSize, double contrast = 0.0, double brightness = 0.0) override
				{
					m_imageSize = imageSize;
					m_contrast = contrast;
					m_brightness = brightness;
					BuildLutTable();
				}

				virtual void SetContrastBrightness(double contrast, double brightness)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (abs(m_contrast - contrast) > kEpsinon64 || abs(m_brightness - brightness) > kEpsinon64)
					{
						m_contrast = contrast;
						m_brightness = brightness;
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
					for (int i = 0; i < kLevelsIntensity8u; ++i)
					{
						double k = tan((45 + 44 * m_contrast) / 180.0 * kPI);
						auto value = ((i - 127.5 * (1 - m_brightness)) * k + 127.5 * (1 + m_brightness));
						if (value < 0.0)
						{
							value = 0.0;
						}
						else if (value > kMaxIntensity8u)
						{
							value = kMaxIntensity8u;
						}
						m_table8u[i] = (Ipp8u)value;
					}
				}

			private:
				Ipp8u * m_table8u;
			};

			/// \brief CContrastBrightness16u1c.
			class CContrastBrightness16u1c : public CContrastBrightness
			{
			public:
				CContrastBrightness16u1c()
					: CContrastBrightness()
					, m_table16u(nullptr)
				{
					m_table16u = new Ipp16u[kLevelsIntensity16u];
					memset(m_table16u, 0, kLevelsIntensity16u * sizeof(Ipp16u));
				}

				~CContrastBrightness16u1c()
				{
					if (m_table16u != nullptr)
					{
						delete[] m_table16u;
						m_table16u = nullptr;
					}
				}

				void Initialize(Size imageSize, double contrast = 0.0, double brightness = 0.0) override
				{
					m_imageSize = imageSize;
					m_contrast = contrast;
					m_brightness = brightness;
					BuildLutTable();
				}

				virtual void SetContrastBrightness(double contrast, double brightness)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (abs(m_contrast - contrast) > kEpsinon64 || abs(m_brightness - brightness) > kEpsinon64)
					{
						m_contrast = contrast;
						m_brightness = brightness;
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
					for (int i = 0; i < kLevelsIntensity16u; ++i)
					{
						double k = tan((45 + 44 * m_contrast) / 180.0 * kPI);
						auto value = ((i - 32767.5 * (1 - m_brightness)) * k + 32767.5 * (1 + m_brightness));
						if (value < 0.0)
						{
							value = 0.0;
						}
						else if (value > kMaxIntensity16u)
						{
							value = kMaxIntensity16u;
						}
						m_table16u[i] = (Ipp8u)value;
					}
				}
			private:
				Ipp16u * m_table16u;
			};
		}
	}
}
#endif
