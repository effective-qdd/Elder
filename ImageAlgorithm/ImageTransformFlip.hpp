/**
* \file ImageTransformFlip.hpp
* \brief Flip image up2down or down2up or left2right or right2left.
*
* detail description
*
* \author mbq
* \email
* \version 1.0.0.0
* \date 2017.06.14
*/
#ifndef _IMAGE_TRANSFORM_FLIP_H
#define _IMAGE_TRANSFORM_FLIP_H


// My Class Includes
#include "ImageTransformBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace TRANSFORM
		{
			/// \brief CFlip.
			class CFlip : public ITransform
			{
			public:

				enum FlipModes
				{
					kHorizintal = 1,
					kVertical,
					kHorizontalVertical
				};


				CFlip()
					: ITransform()
					, m_flipMode(kHorizintal)
					, m_ippiAxis(ippAxsVertical)
				{

				}

				virtual ~CFlip() override = default;


				void Initialize(Size imageSize, FlipModes flipMode = kHorizintal)
				{
					m_imageSize = imageSize;

					SetMode(flipMode);
				}

				void SetMode(FlipModes flipMode)
				{
					ENSURE_THROW_MSG(flipMode == kHorizintal ||
						flipMode == kVertical ||
						flipMode == kHorizontalVertical,
						"Error FlipModes");
					std::lock_guard<std::mutex> lock(m_mutex);
					if (m_flipMode != flipMode)
					{
						m_flipMode = flipMode;
						if (flipMode == kHorizintal) m_ippiAxis = ippAxsVertical;
						else if (flipMode == kVertical) m_ippiAxis = ippAxsHorizontal;
						else if (flipMode == kHorizontalVertical) m_ippiAxis = ippAxsBoth;
					}
				}

				virtual bool Apply(std::any const&, std::any const&, ImageInfo&) { return true; };

			protected:
				Size		m_imageSize;
				FlipModes	m_flipMode;
				IppiAxis    m_ippiAxis;
				std::mutex	m_mutex;
			};

			/// \brief CFlip8u1c.
			class CFlip8u1c : public CFlip
			{
			public:
				CFlip8u1c()
					: CFlip()
				{

				}

				~CFlip8u1c()
				{

				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
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
					auto status = ippiMirror_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippiAxis
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CFlip16u1c.
			class CFlip16u1c : public CFlip
			{
			public:
				CFlip16u1c()
					: CFlip()
				{

				}

				~CFlip16u1c()
				{

				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
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
					auto status = ippiMirror_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippiAxis
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CFlip32f1c.
			class CFlip32f1c : public CFlip
			{
			public:
				CFlip32f1c()
					: CFlip()
				{

				}

				~CFlip32f1c()
				{

				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
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
					auto status = ippiMirror_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_ippiAxis
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}

#endif