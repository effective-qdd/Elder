/**
* \file ImageRotation.hpp
* \brief Rotate image by a angle, x offset and y offset.
*
* detail description
*
* \author mbq
* \email
* \version 1.0.0.0
* \date 2017.10.31
*/
#ifndef _IMAGE_TRANSFORM_ROTATION_H
#define _IMAGE_TRANSFORM_ROTATION_H


// My Class Includes
#include "ImageTransformBase.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		namespace TRANSFORM
		{
			/// \brief CRotationSpecial
			class CRotationSpecial : public ITransform
			{
			public:
				enum SpecialAngle
				{
					k90Degrees = 1,
					k180Degrees,
					k270Degrees
				};

				CRotationSpecial()
					: ITransform()
				{
				}

				virtual ~CRotationSpecial()
				{
				}

				virtual void Initialize(Size imageSize, SpecialAngle degrees)
				{
					m_srcImageSize = imageSize;
					SetAngle(degrees);
				}

				void SetAngle(SpecialAngle degrees)
				{
					ENSURE_THROW_MSG(degrees == k90Degrees ||
						degrees == k180Degrees ||
						degrees == k270Degrees,
						"Error SpecialAngle");

					std::lock_guard<std::mutex> lock(m_mutex);
					if (m_specialAngle != degrees)
					{
						m_specialAngle = degrees;
						if (m_specialAngle == k90Degrees)
						{
							m_flip = ippAxsVertical;
							m_dstImageSize.width = m_srcImageSize.height;
							m_dstImageSize.height = m_srcImageSize.width;
						}
						else if (m_specialAngle == k180Degrees)
						{
							m_flip = ippAxsBoth;
							m_dstImageSize.width = m_srcImageSize.width;
							m_dstImageSize.height = m_srcImageSize.height;
						}
						else if (m_specialAngle == k270Degrees)
						{
							m_flip = ippAxsHorizontal;
							m_dstImageSize.width = m_srcImageSize.height;
							m_dstImageSize.height = m_srcImageSize.width;
						}
					}
				}

				virtual bool Apply(std::any const&, std::any const&, ImageInfo&) { return true; };

			protected:
				Size			m_srcImageSize;
				Size			m_dstImageSize;
				IppiAxis		m_flip;
				SpecialAngle	m_specialAngle;
				std::mutex		m_mutex;
			};


			/**************************************************************
			** Class Name: CRotationSpecial8u1c
			***************************************************************/
			class CRotationSpecial8u1c : public CRotationSpecial
			{
			public:
				CRotationSpecial8u1c()
					: CRotationSpecial()
					, m_transposeImage(std::make_shared<CImage8u1cIPPI>())
				{

				}

				~CRotationSpecial8u1c()
				{

				}

				void Initialize(Size imageSize, SpecialAngle degrees)
				{
					if (m_srcImageSize != imageSize)
					{
						m_transposeImage->Initialize(imageSize.height, imageSize.width);
					}
					CRotationSpecial::Initialize(imageSize, degrees);
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_srcImageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_srcImageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

					std::lock_guard<std::mutex> lock(m_mutex);
					if ((m_dstImageSize.width != dst->Width()) || (m_dstImageSize.height != dst->Height()))
					{
						outImageInfo.size = m_dstImageSize;
						outImageInfo.bitDepth = 8;

						return false;
					}

					if (m_flip == ippAxsBoth)
					{
						auto status = ippiMirror_8u_C1R
						(
							src->Data(),
							src->WidthBytes(),
							dst->Data(),
							dst->WidthBytes(),
							{ m_srcImageSize.width, m_srcImageSize.height },
							m_flip
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");
					}
					else
					{
						auto status = ippiTranspose_8u_C1R
						(
							src->Data(),
							src->WidthBytes(),
							m_transposeImage->Data(),
							m_transposeImage->WidthBytes(),
							{ m_srcImageSize.width, m_srcImageSize.height }
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiTranspose_8u_C1R failed!");
						status = ippiMirror_8u_C1R
						(
							m_transposeImage->Data(),
							m_transposeImage->WidthBytes(),
							dst->Data(),
							dst->WidthBytes(),
							{ m_dstImageSize.width, m_dstImageSize.height },
							m_flip
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");
					}

					return true;
				}

			private:
				std::shared_ptr<CImage8u1cIPPI> m_transposeImage;
			};


			/// \brief CRotationSpecial16u1c
			class CRotationSpecial16u1c : public CRotationSpecial
			{
			public:
				CRotationSpecial16u1c()
					: CRotationSpecial()
					, m_transposeImage(std::make_shared<CImage16u1cIPPI>())
				{

				}

				~CRotationSpecial16u1c()
				{

				}

				void Initialize(Size imageSize, SpecialAngle degrees)
				{
					if (m_srcImageSize != imageSize)
					{
						m_transposeImage->Initialize(imageSize.height, imageSize.width);
					}
					CRotationSpecial::Initialize(imageSize, degrees);
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_srcImageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_srcImageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

					std::lock_guard<std::mutex> lock(m_mutex);
					if ((m_dstImageSize.width != dst->Width()) || (m_dstImageSize.height != dst->Height()))
					{
						outImageInfo.size = m_dstImageSize;
						outImageInfo.bitDepth = 16;

						return false;
					}

					if (m_flip == ippAxsBoth)
					{
						auto status = ippiMirror_16u_C1R
						(
							src->Data(),
							src->WidthBytes(),
							dst->Data(),
							dst->WidthBytes(),
							{ m_srcImageSize.width, m_srcImageSize.height },
							m_flip
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");
					}
					else
					{
						auto status = ippiTranspose_16u_C1R
						(
							src->Data(),
							src->WidthBytes(),
							m_transposeImage->Data(),
							m_transposeImage->WidthBytes(),
							{ m_srcImageSize.width, m_srcImageSize.height }
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiTranspose_8u_C1R failed!");
						status = ippiMirror_16u_C1R
						(
							m_transposeImage->Data(),
							m_transposeImage->WidthBytes(),
							dst->Data(),
							dst->WidthBytes(),
							{ m_dstImageSize.width, m_dstImageSize.height },
							m_flip
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");
					}

					return true;
				}

			private:
				std::shared_ptr<CImage16u1cIPPI> m_transposeImage;
			};


			/// \brief CRotationSpecial32f1c
			class CRotationSpecial32f1c : public CRotationSpecial
			{
			public:
				CRotationSpecial32f1c()
					: CRotationSpecial()
					, m_transposeImage(std::make_shared<CImage32f1cIPPI>())
				{

				}

				~CRotationSpecial32f1c()
				{

				}

				void Initialize(Size imageSize, SpecialAngle degrees)
				{
					if (m_srcImageSize != imageSize)
					{
						m_transposeImage->Initialize(imageSize.height, imageSize.width);
					}

					CRotationSpecial::Initialize(imageSize, degrees);
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_srcImageSize.width == src->Width(), "m_srcImgSize.width != src->Width()");
					ASSERT_LOG(m_srcImageSize.height == src->Height(), "m_srcImgSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

					std::lock_guard<std::mutex> lock(m_mutex);
					if ((m_dstImageSize.width != dst->Width()) || (m_dstImageSize.height != dst->Height()))
					{
						outImageInfo.size = m_dstImageSize;
						outImageInfo.bitDepth = 32;

						return false;
					}

					if (m_flip == ippAxsBoth)
					{
						auto status = ippiMirror_32f_C1R
						(
							src->Data(),
							src->WidthBytes(),
							dst->Data(),
							dst->WidthBytes(),
							{ m_srcImageSize.width, m_srcImageSize.height },
							m_flip
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");
					}
					else
					{
						auto status = ippiTranspose_32f_C1R
						(
							src->Data(),
							src->WidthBytes(),
							m_transposeImage->Data(),
							m_transposeImage->WidthBytes(),
							{ m_srcImageSize.width, m_srcImageSize.height }
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiTranspose_8u_C1R failed!");
						status = ippiMirror_32f_C1R
						(
							m_transposeImage->Data(),
							m_transposeImage->WidthBytes(),
							dst->Data(),
							dst->WidthBytes(),
							{ m_dstImageSize.width, m_dstImageSize.height },
							m_flip
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMirror_8u_C1R failed!");
					}

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_transposeImage;
			};


			/// \brief CRotationArbitrary
			class CRotationArbitrary : public ITransform
			{
			public:
				CRotationArbitrary()
					: ITransform()
					, m_pSpec(nullptr)
					, m_pBuffer(nullptr)
				{
					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							m_coeffs[i][j] = 0.0;
						}
					}
				}

				virtual ~CRotationArbitrary()
				{
					if (m_pSpec != nullptr)
					{
						ippsFree(m_pSpec);
						m_pSpec = nullptr;
					}

					if (m_pBuffer != nullptr)
					{
						ippsFree(m_pBuffer);
						m_pBuffer = nullptr;
					}
				}


				virtual void Initialize(Size imageSize, double degrees)
				{
					m_imageSize = imageSize;
					m_degrees = degrees;

					auto centerX = m_imageSize.width / 2;
					auto centerY = m_imageSize.height / 2;
					auto xShiftTmp = 0.0;
					auto yShiftTmp = 0.0;

					auto status = ippiGetRotateShift(centerX, centerY, degrees, &xShiftTmp, &yShiftTmp);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiGetRotateShift failed!");
					status = ippiGetRotateTransform(m_degrees, xShiftTmp, yShiftTmp, m_coeffs);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiGetRotateTransform failed!");
				}

				virtual void SetAngle(double degrees)
				{

				}

				virtual bool Apply(std::any const&, std::any const&, ImageInfo&) { return true; };

			protected:
				Size			m_imageSize;
				double			m_degrees;
				double          m_coeffs[2][3];
				IppiWarpSpec*	m_pSpec;
				Ipp8u*			m_pBuffer;
				std::mutex		m_mutex;
			};


			/// \brief CRotationArbitrary8u1c.
			class CRotationArbitrary8u1c : public CRotationArbitrary
			{
			public:
				CRotationArbitrary8u1c()
					: CRotationArbitrary()
				{

				}

				~CRotationArbitrary8u1c()
				{

				}

				void Initialize(Size imageSize, double degrees)
				{
					if (m_imageSize != imageSize || abs(m_degrees - degrees) > kEpsinon64)
					{
						CRotationArbitrary::Initialize(imageSize, degrees);

						auto specSize = 0;
						auto initSize = 0;
						auto status = ippiWarpAffineGetSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp8u,
							m_coeffs,
							ippLinear,
							ippWarpForward,
							ippBorderConst,
							&specSize,
							&initSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineGetSize failed!");

						if (m_pSpec != nullptr) ippsFree(m_pSpec);
						m_pSpec = (IppiWarpSpec*)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_pSpec != nullptr, "ippsMalloc_8u failed!");

						auto borderValue = 0.0;
						status = ippiWarpAffineLinearInit
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp8u,
							m_coeffs,
							ippWarpForward,
							1,
							ippBorderConst,
							&borderValue,
							0,
							m_pSpec
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineLinearInit failed!");

						auto bufferSize = 0;
						status = ippiWarpGetBufferSize
						(
							m_pSpec,
							{ m_imageSize.width, m_imageSize.height },
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpGetBufferSize failed!");

						if (m_pBuffer != nullptr) ippsFree(m_pBuffer);
						m_pBuffer = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_pBuffer != nullptr, "ippsMalloc_8u failed!");
					}
				}

				void SetAngle(double degrees)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					this->Initialize(m_imageSize, degrees);
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage8u1cIPPI>()), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage8u1cIPPI>()), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					auto status = ippiWarpAffineLinear_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ 0, 0 },
						{ m_imageSize.width, m_imageSize.height },
						m_pSpec,
						m_pBuffer
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineLinear_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CRotationArbitrary16u1c.
			class CRotationArbitrary16u1c : public CRotationArbitrary
			{
			public:
				CRotationArbitrary16u1c()
					: CRotationArbitrary()
				{

				}

				~CRotationArbitrary16u1c()
				{

				}

				void Initialize(Size imageSize, double degrees)
				{
					if (m_imageSize != imageSize || abs(m_degrees - degrees) > kEpsinon64)
					{
						CRotationArbitrary::Initialize(imageSize, degrees);

						auto specSize = 0;
						auto initSize = 0;
						auto status = ippiWarpAffineGetSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp16u,
							m_coeffs,
							ippLinear,
							ippWarpForward,
							ippBorderConst,
							&specSize,
							&initSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineGetSize failed!");

						if (m_pSpec != nullptr) ippsFree(m_pSpec);
						m_pSpec = (IppiWarpSpec*)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_pSpec != nullptr, "ippsMalloc_8u failed!");

						auto borderValue = 0.0;
						status = ippiWarpAffineLinearInit
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp16u,
							m_coeffs,
							ippWarpForward,
							1,
							ippBorderConst,
							&borderValue,
							0,
							m_pSpec
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineLinearInit failed!");

						auto bufferSize = 0;
						status = ippiWarpGetBufferSize
						(
							m_pSpec,
							{ m_imageSize.width, m_imageSize.height },
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpGetBufferSize failed!");

						if (m_pBuffer != nullptr) ippsFree(m_pBuffer);
						m_pBuffer = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_pBuffer != nullptr, "ippsMalloc_8u failed!");
					}
				}

				void SetAngle(double degrees)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					this->Initialize(m_imageSize, degrees);
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage16u1cIPPI>()), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage16u1cIPPI>()), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					IppiPoint dstOffset = { 0, 0 };
					auto status = ippiWarpAffineLinear_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ 0, 0 },
						{ m_imageSize.width, m_imageSize.height },
						m_pSpec,
						m_pBuffer
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineLinear_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CRotationArbitrary32f1c.
			class CRotationArbitrary32f1c : public CRotationArbitrary
			{
			public:
				CRotationArbitrary32f1c()
					: CRotationArbitrary()
				{

				}

				~CRotationArbitrary32f1c()
				{

				}

				void Initialize(Size imageSize, double degrees)
				{
					if (m_imageSize != imageSize || abs(m_degrees - degrees) > kEpsinon64)
					{
						CRotationArbitrary::Initialize(imageSize, degrees);

						auto specSize = 0;
						auto initSize = 0;
						auto status = ippiWarpAffineGetSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp32f,
							m_coeffs,
							ippLinear,
							ippWarpForward,
							ippBorderConst,
							&specSize,
							&initSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineGetSize failed!");

						if (m_pSpec != nullptr) ippsFree(m_pSpec);
						m_pSpec = (IppiWarpSpec*)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_pSpec != nullptr, "ippsMalloc_8u failed!");

						auto borderValue = 0.0;
						status = ippiWarpAffineLinearInit
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp32f,
							m_coeffs,
							ippWarpForward,
							1,
							ippBorderConst,
							&borderValue,
							0,
							m_pSpec
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineLinearInit failed!");

						auto bufferSize = 0;
						status = ippiWarpGetBufferSize
						(
							m_pSpec,
							{ m_imageSize.width, m_imageSize.height },
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpGetBufferSize failed!");

						if (m_pBuffer != nullptr) ippsFree(m_pBuffer);
						m_pBuffer = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_pBuffer != nullptr, "ippsMalloc_8u failed!");
					}
				}

				void SetAngle(double degrees)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					this->Initialize(m_imageSize, degrees);
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage32f1cIPPI>()), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage32f1cIPPI>()), "Error imageOut Format");
					auto src = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageIn);
					ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
					ASSERT_LOG(m_imageSize.width == src->Width(), "m_srcImgSize.width != src->Width()");
					ASSERT_LOG(m_imageSize.height == src->Height(), "m_srcImgSize.height != src->Height()");
					auto dst = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					std::lock_guard<std::mutex> lock(m_mutex);
					auto status = ippiWarpAffineLinear_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ 0, 0 },
						{ m_imageSize.width, m_imageSize.height },
						m_pSpec,
						m_pBuffer
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiWarpAffineLinear_16u_C1R failed!");

					return true;
				}
			};
		}
	}
}

#endif