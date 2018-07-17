/**
* \file ImageNegative.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.15
*/
#ifndef _IMAGE_INTENSITY_NEGATIVE_H
#define _IMAGE_INTENSITY_NEGATIVE_H


// My Class Includes
#include "ImageIntensityBase.hpp"
#include "../ImageOperator/ImageSubConstant.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageMulConstant.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CNegative
			/// s = L - 1 - r;
			/// L = 2^n;
			class CNegative : public IIntensity
			{
			public:
				CNegative()
					: IIntensity()
					, m_imageSize{ 0, 0 }
				{

				}

				virtual ~CNegative()
				{

				}

				virtual void Initialize(Size imageSize)
				{
					m_imageSize = imageSize;
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;

			};


			/// \brief CNegative8u1c.
			class CNegative8u1c : public CNegative
			{
			public:
				CNegative8u1c()
					: CNegative()
				{

				}

				~CNegative8u1c()
				{

				}

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						CNegative::Initialize(imageSize);
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

					auto status = ippiNot_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiNot_8u_C1R failed!");


					return true;
				}
			};

			/// \brief CNegative16u1c.
			class CNegative16u1c : public CNegative
			{
				//const float kMaxIntensity = 65535.0f;
			public:
				CNegative16u1c()
					: CNegative()
					, m_tmpImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{

				}

				~CNegative16u1c()
				{

				}

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						CNegative::Initialize(imageSize);
						m_tmpImage32f1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
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

					OPERATOR::CImageConvert<OPERATOR::CConvert16u1cTo32f1c>::Convert(src, m_tmpImage32f1c);
					OPERATOR::CImageSubConstant<OPERATOR::CSubConstant32f1c>::SubConstant(m_tmpImage32f1c, kMaxIntensity16u);
					OPERATOR::CImageMulConstant<OPERATOR::CMulConstant32f1c>::MulConstant(m_tmpImage32f1c, -1.0f);
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_tmpImage32f1c, dst);

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_tmpImage32f1c;
			};
		}
	}
}
#endif
