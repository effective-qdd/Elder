/**
* \file ImageThreshold.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.09
*/
#ifndef _IMAGE_INTENSITY_THRESHOLD_H
#define _IMAGE_INTENSITY_THRESHOLD_H

// My Class Includes
#include "ImageIntensityBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CThreshold.
			class CThreshold : public IIntensity
			{
			public:
				CThreshold()
					: IIntensity()
					, m_thresholdLT(0)
					, m_valueLT(0)
					, m_thresholdGT(0)
					, m_valueGT(0)
				{

				}

				virtual ~CThreshold()
				{

				}


				virtual void Initialize(Size imageSize, int thresholdLT, int valueLT, int thresholdGT, int valueGT) {}

				virtual void SetThresholdValue(int thresholdLT, int valueLT, int thresholdGT, int valueGT) {}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;
				int m_thresholdLT;
				int m_valueLT;
				int m_thresholdGT;
				int m_valueGT;
			};


			/// \brief CThreshold8u1c.
			class CThreshold8u1c : public CThreshold
			{
			public:
				CThreshold8u1c()
					: CThreshold()
				{

				}


				~CThreshold8u1c()
				{

				}

				void Initialize(Size imageSize, int thresholdLT = kMinIntensity8u, int valueLT = kMinIntensity8u, int thresholdGT = kMaxIntensity8u, int valueGT = kMaxIntensity8u) override
				{
					m_imageSize = imageSize;
					this->SetThresholdValue(thresholdLT, valueLT, thresholdGT, valueGT);
				}

				void SetThresholdValue(int thresholdLT, int valueLT, int thresholdGT, int valueGT) override
				{
					ENSURE_THROW_MSG(thresholdLT >= kMinIntensity8u, "low threshold value must >= 0");
					ENSURE_THROW_MSG(thresholdLT <= kMaxIntensity8u, "low threshold value must <= 255");
					ENSURE_THROW_MSG(valueLT >= kMinIntensity8u, "low threshold value must >= 0");
					ENSURE_THROW_MSG(valueLT <= kMaxIntensity8u, "low output value must <= 255");
					ENSURE_THROW_MSG(thresholdGT >= kMinIntensity8u, "upper threshold value must >= 0");
					ENSURE_THROW_MSG(thresholdGT <= kMaxIntensity8u, "upper threshold value must <= 255");
					ENSURE_THROW_MSG(valueGT >= kMinIntensity8u, "upper output value must >= 0");
					ENSURE_THROW_MSG(valueGT <= kMaxIntensity8u, "upper output value must <= 255");
					ENSURE_THROW_MSG(thresholdLT <= thresholdGT, "low threshold value must <= upper threshold value");
					m_thresholdLT = thresholdLT;
					m_valueLT = valueLT;
					m_thresholdGT = thresholdGT;
					m_valueGT = valueGT;
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

					auto status = ippiThreshold_LTValGTVal_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						static_cast<Ipp8u>(m_thresholdLT),
						static_cast<Ipp8u>(m_valueLT),
						static_cast<Ipp8u>(m_thresholdGT),
						static_cast<Ipp8u>(m_valueGT)
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "CThreshold8u1c::Apply => ippiThreshold_LTValGTVal_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CThreshold16u1c.
			class CThreshold16u1c : public CThreshold
			{
			public:
				CThreshold16u1c()
					: CThreshold()
				{

				}


				~CThreshold16u1c()
				{

				}

				void Initialize(Size imageSize, int thresholdLT = kMinIntensity16u, int valueLT = kMinIntensity16u, int thresholdGT = kMaxIntensity16u, int valueGT = kMaxIntensity16u) override
				{
					m_imageSize = imageSize;
					this->SetThresholdValue(thresholdLT, valueLT, thresholdGT, valueGT);
				}

				void SetThresholdValue(int thresholdLT, int valueLT, int thresholdGT, int valueGT) override
				{
					ENSURE_THROW_MSG(thresholdLT >= kMinIntensity16u, "low threshold value must >= 0");
					ENSURE_THROW_MSG(thresholdLT <= kMaxIntensity16u, "low threshold value must <= 65535");
					ENSURE_THROW_MSG(valueLT >= kMinIntensity16u, "low threshold value must >= 0");
					ENSURE_THROW_MSG(valueLT <= kMaxIntensity16u, "low output value must <= 65535");
					ENSURE_THROW_MSG(thresholdGT >= kMinIntensity16u, "upper threshold value must >= 0");
					ENSURE_THROW_MSG(thresholdGT <= kMaxIntensity16u, "upper threshold value must <= 65535");
					ENSURE_THROW_MSG(valueGT >= kMinIntensity16u, "upper output value must >= 0");
					ENSURE_THROW_MSG(valueGT <= kMaxIntensity16u, "upper output value must <= 65535");
					ENSURE_THROW_MSG(thresholdLT <= thresholdGT, "low threshold value must <= upper threshold value");
					m_thresholdLT = thresholdLT;
					m_valueLT = valueLT;
					m_thresholdGT = thresholdGT;
					m_valueGT = valueGT;
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

					auto status = ippiThreshold_LTValGTVal_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						static_cast<Ipp16u>(m_thresholdLT),
						static_cast<Ipp16u>(m_valueLT),
						static_cast<Ipp16u>(m_thresholdGT),
						static_cast<Ipp16u>(m_valueGT)
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "CThreshold16u1c::Apply => ippiThreshold_LTValGTVal_16u_C1R failed!");

					return true;
				}
			};
		}
	}
}


#endif