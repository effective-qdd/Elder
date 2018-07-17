/**
* \file ImageLog.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.15
*/
#ifndef _IMAGE_INTENSITY_LOG_H
#define _IMAGE_INTENSITY_LOG_H


// My Class Includes
#include "ImageIntensityBase.hpp"
#include "../ImageOperator/ImageMulConstant.hpp"
#include "../ImageOperator/ImageAddConstant.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CLog
			/// s = Log(1+r) / b; b -> (0, 1.0]
			class CLog : public IIntensity
			{
			public:
				CLog()
					: IIntensity()
					, m_imageSize{ 0, 0 }
				{

				}

				virtual ~CLog()
				{

				}

				virtual void Initialize(Size imageSize, double b)
				{
					
				}

				virtual void SetValue(double b)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;
				double  m_b;
				std::mutex m_mutex;
			};


			/// \brief CLog8u1c.
			class CLog8u1c : public CLog
			{
			public:
				CLog8u1c()
					: CLog()
					, m_table8u(nullptr)
				{
					m_table8u = new Ipp8u[kLevelsIntensity8u];
					memset(m_table8u, 0, kLevelsIntensity8u);
				}

				~CLog8u1c()
				{
					if (m_table8u != nullptr)
					{
						delete[] m_table8u;
						m_table8u = nullptr;
					}
				}

				void Initialize(Size imageSize, double b = 1.0) override
				{
					m_imageSize = imageSize;
					m_b = b;
					BuildLutTable();
				}

				void SetValue(double b) override
				{
					if (abs(b) > kEpsinon64)
					{
						m_b = b;
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

// 					OPERATOR::CImageAddConstant<OPERATOR::CAddConstant8u1c>::AddConstant(dst, src, 1);
// 
// 					auto status = ippiLn_8u_C1IRSfs
// 					(
// 						dst->Data(),
// 						dst->WidthBytes(),
// 						{ m_imageSize.width, m_imageSize.height },
// 						0
// 					);
// 					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiLn_8u_C1RSfs failed!");
// 
// 					OPERATOR::CImageMulConstant<OPERATOR::CMulConstant8u1c>::MulConstant(dst, 46);
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
					auto f = 0.0;
					for (int i = 0; i < kLevelsIntensity8u; i++)
					{
						f = log(double(i + 1)) / m_b;
						m_table8u[i] = (Ipp8u)(f + 0.5);
					}
				}

			private:
				Ipp8u* m_table8u;
			};

			/// \brief CLog16u1c.
			class CLog16u1c : public CLog
			{
			public:
				CLog16u1c()
					: CLog()
					, m_table16u(nullptr)
				{
					m_table16u = new Ipp16u[kLevelsIntensity16u];
					memset(m_table16u, 0, kLevelsIntensity16u * sizeof(Ipp16u));
				}

				~CLog16u1c()
				{
					if (m_table16u != nullptr)
					{
						delete[] m_table16u;
						m_table16u = nullptr;
					}
				}

				void Initialize(Size imageSize, double b = 1.0) override
				{
					m_imageSize = imageSize;
					m_b = b;
					BuildLutTable();
				}

				void SetValue(double b) override
				{
					if (abs(b) > kEpsinon64)
					{
						m_b = b;
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

// 					OPERATOR::CImageAddConstant<OPERATOR::CAddConstant16u1c>::AddConstant(dst, src, 1);
// 
// 					auto status = ippiLn_16u_C1RSfs
// 					(
// 						src->Data(),
// 						src->WidthBytes(),
// 						dst->Data(),
// 						dst->WidthBytes(),
// 						{ m_imageSize.width, m_imageSize.height },
// 						0
// 					);
// 					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiLn_16u_C1RSfs failed!");
// 
// 					OPERATOR::CImageMulConstant<OPERATOR::CMulConstant16u1c>::MulConstant(dst, 5909);
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
					auto f = 0.0;
					for (int i = 0; i < kLevelsIntensity16u; i++)
					{
						f = log(double(i + 1)) / m_b;
						m_table16u[i] = (Ipp16u)(f + 0.5);
					}
				}

			private:
				Ipp16u* m_table16u;
			};
		}
	}
}
#endif
