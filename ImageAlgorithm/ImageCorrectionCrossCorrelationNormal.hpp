/**
* \file ImageCorrectionCrossCorrelationNormal.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.18
*/
#ifndef _IMAGE_CORRECTION_CROSS_CORRELATION_NORMAL_H
#define _IMAGE_CORRECTION_CROSS_CORRELATION_NORMAL_H


// My Class Includes
#include "ImageCorrectionBase.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageCopy.hpp"
#include "../ImageOperator/ImageMulConstant.hpp"
#include "../ImageOperator/ImageMax.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace CORRECTION
		{
			/// \brief CCorssCorrelationNormal
			class CCorssCorrelationNormal : public ICorrection
			{
			public:
				CCorssCorrelationNormal()
					: ICorrection()
					, m_buf8u(nullptr)
				{}

				virtual ~CCorssCorrelationNormal() = default;

				virtual void Initialize(Size imageSize) {};

				virtual void SetTemplateReference(void const*const) {};

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size m_imageSize;
				Ipp8u* m_buf8u;
				std::mutex	m_mutex;
			};


			/// \brief CCorssCorrelationNormal8u1c.
			class CCorssCorrelationNormal8u1c : public CCorssCorrelationNormal
			{
			public:
				CCorssCorrelationNormal8u1c()
					: CCorssCorrelationNormal()
					, m_refImage8u1c(std::make_shared<CImage8u1cIPPI>())
					, m_tmpImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CCorssCorrelationNormal8u1c() = default;

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
						int bufferSize = 0;
						IppEnum funCfg = (IppEnum)(ippAlgAuto | ippiROISame | ippiNorm);
						auto status = ippiCrossCorrNormGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							funCfg, 
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCrossCorrNormGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						m_refImage8u1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
						m_tmpImage32f1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
					}
				}

				void SetTemplateReference(void const*const refImage) override
				{
					ASSERT_LOG(refImage != nullptr, "Input image is null");
					ASSERT_LOG(m_refImage8u1c != nullptr, "m_refImage8u1c is null");
					
					auto status = ippiCopy_8u_C1R
					(
						reinterpret_cast<Ipp8u*>(const_cast<void*>(refImage)),
						m_imageSize.width,
						m_refImage8u1c->Data(),
						m_refImage8u1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
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
					IppEnum funCfg = (IppEnum)(ippAlgAuto | ippiROISame | ippiNorm);
					auto status = ippiCrossCorrNorm_8u32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_refImage8u1c->Data(),
						m_refImage8u1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_tmpImage32f1c->Data(),
						m_tmpImage32f1c->WidthBytes(),
						funCfg,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCrossCorrNorm_8u32f_C1R failed!");
					OPERATOR::CImageMulConstant<OPERATOR::CMulConstant32f1c>::MulConstant(m_tmpImage32f1c, 255.0);
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo8u1c>::Convert(m_tmpImage32f1c, dst);
					
					//auto max = OPERATOR::CImageMax<OPERATOR::CMax32f1c>::Max(m_tmpImage32f1c);
					return true;
				}

			private:
				std::shared_ptr<CImage8u1cIPPI> m_refImage8u1c;
				std::shared_ptr<CImage32f1cIPPI> m_tmpImage32f1c;
			};


			/// \brief CCorssCorrelationNormal16u1c
			class CCorssCorrelationNormal16u1c : public CCorssCorrelationNormal
			{
			public:
				CCorssCorrelationNormal16u1c()
					: CCorssCorrelationNormal()
					, m_refImage16u1c(std::make_shared<CImage16u1cIPPI>())
					, m_tmpImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CCorssCorrelationNormal16u1c() = default;

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
						int bufferSize = 0;
						IppEnum funCfg = (IppEnum)(ippAlgAuto | ippiROISame | ippiNorm);
						auto status = ippiCrossCorrNormGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							funCfg,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCrossCorrNormGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						m_refImage16u1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
						m_tmpImage32f1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
					}
				}

				void SetTemplateReference(void const*const refImage) override
				{
					ASSERT_LOG(refImage != nullptr, "Input image is null");
					ASSERT_LOG(m_refImage16u1c != nullptr, "m_refImage16u1c is null");

					auto status = ippiCopy_16u_C1R
					(
						reinterpret_cast<Ipp16u*>(const_cast<void*>(refImage)),
						m_imageSize.width * sizeof(unsigned short),
						m_refImage16u1c->Data(),
						m_refImage16u1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
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
					IppEnum funCfg = (IppEnum)(ippAlgAuto | ippiROISame | ippiNorm);
					auto status = ippiCrossCorrNorm_16u32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_refImage16u1c->Data(),
						m_refImage16u1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_tmpImage32f1c->Data(),
						m_tmpImage32f1c->WidthBytes(),
						funCfg,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCrossCorrNorm_16u32f_C1R failed!");
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_tmpImage32f1c, dst);

					return true;
				}

			private:
				std::shared_ptr<CImage16u1cIPPI> m_refImage16u1c;
				std::shared_ptr<CImage32f1cIPPI> m_tmpImage32f1c;
			};


			/// \brief CCorssCorrelationNormal32f1c.
			class CCorssCorrelationNormal32f1c : public CCorssCorrelationNormal
			{
			public:
				CCorssCorrelationNormal32f1c()
					: CCorssCorrelationNormal()
					, m_refImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CCorssCorrelationNormal32f1c() = default;

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
						int bufferSize = 0;
						IppEnum funCfg = (IppEnum)(ippAlgAuto | ippiROISame | ippiNorm);
						auto status = ippiCrossCorrNormGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_imageSize.width, m_imageSize.height },
							funCfg,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCrossCorrNormGetBufferSize failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");

						m_refImage32f1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
					}
				}

				void SetTemplateReference(void const*const refImage) override
				{
					ASSERT_LOG(refImage != nullptr, "Input image is null");
					ASSERT_LOG(m_refImage32f1c != nullptr, "m_refImage32f1c is null");

					auto status = ippiCopy_32f_C1R
					(
						reinterpret_cast<Ipp32f*>(const_cast<void*>(refImage)),
						m_imageSize.width * sizeof(float),
						m_refImage32f1c->Data(),
						m_refImage32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
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
					IppEnum funCfg = (IppEnum)(ippAlgAuto | ippiROISame | ippiNorm);
					auto status = ippiCrossCorrNorm_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						m_refImage32f1c->Data(),
						m_refImage32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						dst->Data(),
						dst->WidthBytes(),
						funCfg,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCrossCorrNorm_32f_C1R failed!");

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_refImage32f1c;
			};
		}
	}
}


#endif
