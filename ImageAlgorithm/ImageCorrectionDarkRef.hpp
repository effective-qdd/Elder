/**
* \file ImageCorrectionDarkRef.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.18
*/
#ifndef _IMAGE_CORRECTION_DARK_REF_H
#define _IMAGE_CORRECTION_DARK_REF_H


// My Class Includes
#include "ImageCorrectionBase.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageSub.hpp"
#include "../ImageOperator/ImageAddConstant.hpp"
#include "../ImageOperator/ImageCopy.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		namespace CORRECTION
		{
			/// \brief CCorrectionDarkRef
			class CCorrectionDarkRef : public ICorrection
			{
			public:
				CCorrectionDarkRef()
					: ICorrection()
					, m_darkRef32f1c(nullptr)
					, m_tmpImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				virtual ~CCorrectionDarkRef() = default;

				virtual void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
						m_tmpImage32f1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
					}
				}

				virtual void SetReferences(std::shared_ptr<CImage32f1cIPPI> const& darkRef)
				{
					ASSERT_LOG(darkRef != nullptr, "Ref image is null");
					m_darkRef32f1c = darkRef;
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				std::shared_ptr<CImage32f1cIPPI> m_darkRef32f1c;
				std::shared_ptr<CImage32f1cIPPI> m_tmpImage32f1c;
				Size m_imageSize;
				std::mutex	m_mutex;
			};


			/// \brief CCorrectionDarkRef8u1c.
			class CCorrectionDarkRef8u1c : public CCorrectionDarkRef
			{
			public:
				CCorrectionDarkRef8u1c()
					: CCorrectionDarkRef()
				{}

				~CCorrectionDarkRef8u1c() = default;

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
					OPERATOR::CImageConvert<OPERATOR::CConvert8u1cTo32f1c>::Convert(src, m_tmpImage32f1c);
					OPERATOR::CImageSub<OPERATOR::CSub32f1c>::Sub(m_tmpImage32f1c, m_darkRef32f1c);
					//OPERATOR::CImageAddConstant<OPERATOR::CAddConstant32f1c>::AddConstant(m_tmpImage32f1c, 0.5f);
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo8u1c>::Convert(m_tmpImage32f1c, dst);

					return true;
				}
			};


			/// \brief CCorrectionDarkRef16u1c
			class CCorrectionDarkRef16u1c : public CCorrectionDarkRef
			{
			public:
				CCorrectionDarkRef16u1c()
					: CCorrectionDarkRef()
				{}

				~CCorrectionDarkRef16u1c() = default;

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
					OPERATOR::CImageConvert<OPERATOR::CConvert16u1cTo32f1c>::Convert(src, m_tmpImage32f1c);
					OPERATOR::CImageSub<OPERATOR::CSub32f1c>::Sub(m_tmpImage32f1c, m_darkRef32f1c);
					//OPERATOR::CImageAddConstant<OPERATOR::CAddConstant32f1c>::AddConstant(m_tmpImage32f1c, 0.5f);
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_tmpImage32f1c, dst);

					return true;
				}
			};


			/// \brief CCorrectionDarkRef32f1c.
			class CCorrectionDarkRef32f1c : public CCorrectionDarkRef
			{
			public:
				CCorrectionDarkRef32f1c()
					: CCorrectionDarkRef()
				{}

				~CCorrectionDarkRef32f1c() = default;

				void Initialize(Size imageSize) override
				{
					m_imageSize = imageSize;
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
					//OPERATOR::CImageCopy<OPERATOR::CCopy32f1c>::Copy(m_tmpImage32f1c, src);
					OPERATOR::CImageSub<OPERATOR::CSub32f1c>::Sub(dst, src, m_darkRef32f1c);
					//OPERATOR::CImageAddConstant<OPERATOR::CAddConstant32f1c>::AddConstant(m_tmpImage32f1c, 0.5f);
					//OPERATOR::CImageCopy<OPERATOR::CCopy32f1c>::Copy(dst, m_tmpImage32f1c);

					return true;
				}
			};
		}
	}
}


#endif