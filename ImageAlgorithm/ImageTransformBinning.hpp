/**
* \file ImageBinning.hpp
* \brief Image binning
*
* detail description
*
* \author lcg
* \email
* \version 1.0.0.0
* \date 2017.07.13
*/
#ifndef _IMAGE_TRANSFORM_BINNING_H
#define _IMAGE_TRANSFORM_BINNING_H


// My Class Includes
#include "ImageTransformBase.hpp"
#include "../ImageOperator/ImageCopy.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace TRANSFORM
		{
			/// \brief CBinning.
			class CBinning : public ITransform
			{
			public:
				CBinning()
					:ITransform(),
					m_pBuffer(nullptr),
					m_pSpec(nullptr),
					m_srcImageSize{ 0, 0 },
					m_border(ippBorderInMem),
					m_binning(0)
				{
					m_dstOffset.x = 0;
					m_dstOffset.y = 0;
				}


				virtual ~CBinning()
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


				virtual void Initialize(Size imageSize, int binning)
				{
					m_srcImageSize = imageSize;
					m_binning = binning;
					m_dstImageSize.width = m_srcImageSize.width / m_binning;
					m_dstImageSize.height = m_srcImageSize.height / m_binning;
				}

				virtual bool Apply(std::any const&, std::any const&, ImageInfo&) { return true; };

			protected:
				Size				m_srcImageSize;
				Size				m_dstImageSize;
				IppiBorderType		m_border;
				IppiResizeSpec_32f* m_pSpec;
				Ipp8u*				m_pBuffer;
				IppiPoint			m_dstOffset;
				int					m_binning;
			};


			/// \brief CBinning8u1c.
			class CBinning8u1c : public CBinning
			{
			public:
				CBinning8u1c()
					:CBinning()
				{

				}

				~CBinning8u1c()
				{

				}


				void Initialize(Size imageSize, int binning)
				{
					if (m_srcImageSize != imageSize || m_binning != binning)
					{
						CBinning::Initialize(imageSize, binning);

						auto specSize = 0;
						auto initSize = 0;
						auto status = ippiResizeGetSize_8u
						(
							{ m_srcImageSize.width, m_srcImageSize.height },
							{ m_dstImageSize.width, m_dstImageSize.height },
							ippLinear,
							0,
							&specSize,
							&initSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeGetSize_8u failed!");
						if (m_pSpec != nullptr) ippsFree(m_pSpec);
						m_pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_pSpec != nullptr, "ippsMalloc_8u failed!");
						status = ippiResizeLinearInit_8u
						(
							{ m_srcImageSize.width, m_srcImageSize.height },
							{ m_dstImageSize.width, m_dstImageSize.height },
							m_pSpec
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeLinearInit_8u failed!");

						auto bufSize = 0;
						status = ippiResizeGetBufferSize_8u
						(
							m_pSpec,
							{ m_dstImageSize.width, m_dstImageSize.height },
							1,
							&bufSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeGetBufferSize_8u failed!");

						if (m_pBuffer != nullptr) ippsFree(m_pBuffer);
						m_pBuffer = ippsMalloc_8u(bufSize);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippsMalloc_8u failed!");
					}
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
					if ((m_dstImageSize.width != dst->Width()) || (m_dstImageSize.height == dst->Height()))
					{
						outImageInfo.size = m_dstImageSize;
						outImageInfo.bitDepth = 8;

						return false;
					}

					IppStatus status = ippiResizeLinear_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						m_dstOffset,
						{ m_dstImageSize.width, m_dstImageSize.height },
						m_border,
						0,
						m_pSpec,
						m_pBuffer
					);

					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeLinear_8u_C1R failed!");

					return true;
				}

			};


			/// \brief CBinning16u1c.
			class CBinning16u1c : public CBinning
			{
			public:
				CBinning16u1c()
					: CBinning()
				{

				}

				~CBinning16u1c()
				{


				}


				void Initialize(Size imageSize, int binning)
				{
					if (m_srcImageSize != imageSize || m_binning != binning)
					{
						CBinning::Initialize(imageSize, binning);

						auto specSize = 0;
						auto initSize = 0;
						auto status = ippiResizeGetSize_16u
						(
							{ m_srcImageSize.width, m_srcImageSize.height },
							{ m_dstImageSize.width, m_dstImageSize.height },
							ippLinear,
							0,
							&specSize,
							&initSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeGetSize_16u failed!");
						if (m_pSpec != nullptr) ippsFree(m_pSpec);
						m_pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_pSpec != nullptr, "ippsMalloc_8u failed!");
						status = ippiResizeLinearInit_16u
						(
							{ m_srcImageSize.width, m_srcImageSize.height },
							{ m_dstImageSize.width, m_dstImageSize.height },
							m_pSpec
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeLinearInit_16u failed!");

						auto bufSize = 0;
						status = ippiResizeGetBufferSize_16u
						(
							m_pSpec,
							{ m_dstImageSize.width, m_dstImageSize.height },
							1,
							&bufSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeGetBufferSize_16u failed!");

						if (m_pBuffer != nullptr) ippsFree(m_pBuffer);
						m_pBuffer = ippsMalloc_8u(bufSize);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippsMalloc_8u failed!");
					}
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
					if ((m_dstImageSize.width != dst->Width()) || (m_dstImageSize.height == dst->Height()))
					{
						outImageInfo.size = m_dstImageSize;
						outImageInfo.bitDepth = 16;

						return false;
					}

					IppStatus status = ippiResizeLinear_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						m_dstOffset,
						{ m_dstImageSize.width, m_dstImageSize.height },
						m_border,
						0,
						m_pSpec,
						m_pBuffer
					);

					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeLinear_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CBinning32f1c.
			class CBinning32f1c : public CBinning
			{
			public:
				CBinning32f1c()
					: CBinning()
				{

				}

				~CBinning32f1c()
				{

				}


				void Initialize(Size imageSize, int binning)
				{
					if (m_srcImageSize != imageSize || m_binning != binning)
					{
						CBinning::Initialize(imageSize, binning);

						auto specSize = 0;
						auto initSize = 0;
						auto status = ippiResizeGetSize_32f
						(
							{ m_srcImageSize.width, m_srcImageSize.height },
							{ m_dstImageSize.width, m_dstImageSize.height },
							ippLinear,
							0,
							&specSize,
							&initSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeGetSize_32f failed!");
						if (m_pSpec != nullptr) ippsFree(m_pSpec);
						m_pSpec = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_pSpec != nullptr, "ippsMalloc_8u failed!");
						status = ippiResizeLinearInit_32f
						(
							{ m_srcImageSize.width, m_srcImageSize.height },
							{ m_dstImageSize.width, m_dstImageSize.height },
							m_pSpec
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeLinearInit_32f failed!");

						auto bufSize = 0;
						status = ippiResizeGetBufferSize_32f
						(
							m_pSpec,
							{ m_dstImageSize.width, m_dstImageSize.height },
							1,
							&bufSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeGetBufferSize_32f failed!");

						if (m_pBuffer != nullptr) ippsFree(m_pBuffer);
						m_pBuffer = ippsMalloc_8u(bufSize);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippsMalloc_8u failed!");
					}
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
					if ((m_dstImageSize.width != dst->Width()) || (m_dstImageSize.height == dst->Height()))
					{
						outImageInfo.size = m_dstImageSize;
						outImageInfo.bitDepth = 32;

						return false;
					}

					IppStatus status = ippiResizeLinear_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						m_dstOffset,
						{ m_dstImageSize.width, m_dstImageSize.height },
						m_border,
						0,
						m_pSpec,
						m_pBuffer
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiResizeLinear_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}

#endif