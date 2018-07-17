/**
* \file ImageFFT.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.27
*/
#ifndef _IMAGE_FFT_H
#define _IMAGE_FFT_H

// System Class Includes
#include <math.h>

// My Class Includes
#include "ImageAlgorithmBase.hpp"
#include "../ImageOperator/ImageSetConstant.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageConvertCrop.hpp"
#include "../ImageOperator/ImageConvertROI.hpp"
#include "../ImageOperator/ImageMulConstant.hpp"
#include "../ImageOperator/ImageMax.hpp"
#include "../ImageOperator/ImageMin.hpp"
#include "../ImageOperator/ImageAddConstant.hpp"
#include "../ImageOperator/ImageSubConstant.hpp"
#include "../ImageOperator/ImageCopyCrop.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		/// \brief CFFT.
		class CFFT : public IAlgorithm<std::any const&, std::any const&, ImageInfo&>
		{
		public:
			CFFT()
				: IAlgorithm()
				, m_spec(nullptr)
				, m_ipp8uBuf(nullptr)
				, m_ipp8uPackBuf(nullptr)
				, m_ipp32FftBuf(nullptr)
				, m_ipp32Quad1Buf(nullptr)
				, m_ipp32Quad2Buf(nullptr)
				, m_ipp32Quad3Buf(nullptr)
				, m_ipp32Quad4Buf(nullptr)
				, m_fftImage32f1c(std::make_shared<CImage32f1cIPPI>())
				, m_magImage32f1c(std::make_shared<CImage32f1cIPPI>())
			{

			}


			virtual ~CFFT() override
			{
				if (m_ipp8uBuf != nullptr)
				{
					ippFree(m_ipp8uBuf);
					m_ipp8uBuf = nullptr;
				}
				if (m_spec != nullptr)
				{
					ippFree(m_spec);
					m_spec = nullptr;
				}
				if (m_ipp32FftBuf != nullptr)
				{
					ippsFree(m_ipp32FftBuf);
					m_ipp32FftBuf = nullptr;
				}
				if (m_ipp8uPackBuf != nullptr)
				{
					ippFree(m_ipp8uPackBuf);
					m_ipp8uPackBuf = nullptr;
				}
				if (m_ipp32Quad1Buf != nullptr)
				{
					ippsFree(m_ipp32Quad1Buf);
					m_ipp32Quad1Buf = nullptr;
				}
				if (m_ipp32Quad2Buf != nullptr)
				{
					ippsFree(m_ipp32Quad2Buf);
					m_ipp32Quad2Buf = nullptr;
				}
				if (m_ipp32Quad3Buf != nullptr)
				{
					ippsFree(m_ipp32Quad3Buf);
					m_ipp32Quad3Buf = nullptr;
				}
				if (m_ipp32Quad4Buf != nullptr)
				{
					ippsFree(m_ipp32Quad4Buf);
					m_ipp32Quad4Buf = nullptr;
				}
			}

			void Initialize(Size imageSize)
			{
				m_imageSize = imageSize;
				m_orderX = int(ceil(log10(m_imageSize.width) / log10(2)));
				m_orderY = int(ceil(log10(m_imageSize.height) / log10(2)));;
				m_fftImageSize.width = 1 << m_orderX;
				m_fftImageSize.height = 1 << m_orderY;
				m_quadImageWidth = m_fftImageSize.width / 2;
				m_quadImageHeight = m_fftImageSize.height / 2;

				int sizeSpec = 0;
				int sizeInit = 0;
				int sizeBuf = 0;
				auto status = ippiFFTGetSize_R_32f(m_orderX, m_orderY, IPP_FFT_DIV_INV_BY_N, ippAlgHintAccurate, &sizeSpec, &sizeInit, &sizeBuf);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFFTGetSize_R_32f failed!");
				ENSURE_THROW_MSG(sizeSpec > 0, "sizeSpec must > 0!");
				//ENSURE_THROW_MSG(sizeInit > 0, "sizeInit must > 0!");
				ENSURE_THROW_MSG(sizeBuf > 0, "sizeBuf must > 0!");

				if(m_spec != nullptr) ippsFree(m_spec);
				m_spec = (IppiFFTSpec_R_32f*)ippMalloc(sizeSpec);
				ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

				Ipp8u* memBuf = nullptr;
				if (sizeInit > 0)
				{
					memBuf = (Ipp8u*)ippMalloc(sizeInit);
				}
				status = ippiFFTInit_R_32f(m_orderX, m_orderY, IPP_FFT_DIV_INV_BY_N, ippAlgHintAccurate, m_spec, memBuf);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFFTInit_R_32f failed!");
				if (memBuf != nullptr)
				{
					ippFree(memBuf);
					memBuf = nullptr;
				}
				
				if (m_ipp8uBuf != nullptr) ippsFree(m_ipp8uBuf);
				m_ipp8uBuf = (Ipp8u*)ippMalloc(sizeBuf);
				ENSURE_THROW_MSG(m_ipp8uBuf != nullptr, "ippMalloc failed!");				

				int size = 0;
				status = ippiMagnitudePackGetBufferSize_32f(1, { m_fftImageSize.width, m_fftImageSize.height }, &size);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMagnitudePackGetBufferSize_32f failed!");
				if (m_ipp8uPackBuf != nullptr) ippsFree(m_ipp8uPackBuf);
				m_ipp8uPackBuf = (Ipp8u*)ippMalloc(size);
				ENSURE_THROW_MSG(m_ipp8uPackBuf != nullptr, "ippMalloc failed!");

				m_fftImageStep = m_fftImageSize.width * sizeof(Ipp32f);
				int fftBuflength = m_fftImageSize.width * m_fftImageSize.height;
				m_ipp32FftBuf = ippsMalloc_32f(fftBuflength);
				ENSURE_THROW_MSG(m_ipp32FftBuf != nullptr, "ippsMalloc_32f failed!");

				m_ippQuadSize.width = m_quadImageWidth;
				m_ippQuadSize.height = m_quadImageHeight;
				int quadBufLength = m_quadImageWidth * m_quadImageHeight;
				m_ipp32Quad1Buf = ippsMalloc_32f(quadBufLength);
				ENSURE_THROW_MSG(m_ipp32Quad1Buf != nullptr, "ippsMalloc_32f failed!");
				m_ipp32Quad2Buf = ippsMalloc_32f(quadBufLength);
				ENSURE_THROW_MSG(m_ipp32Quad2Buf != nullptr, "ippsMalloc_32f failed!");
				m_ipp32Quad3Buf = ippsMalloc_32f(quadBufLength);
				ENSURE_THROW_MSG(m_ipp32Quad3Buf != nullptr, "ippsMalloc_32f failed!");
				m_ipp32Quad4Buf = ippsMalloc_32f(quadBufLength);
				ENSURE_THROW_MSG(m_ipp32Quad4Buf != nullptr, "ippsMalloc_32f failed!");
				m_quadImageStep = m_quadImageWidth * sizeof(Ipp32f);

				m_fftImage32f1c->Initialize(m_fftImageSize.width, m_fftImageSize.height, nullptr);
				m_magImage32f1c->Initialize(m_fftImageSize.width, m_fftImageSize.height, nullptr);

				// Initialize window function's buffer
// 				int hammingBufferSize8u;
// 				ippiWinHammingGetBufferSize(IppDataType::ipp8u, { m_roiImageSize.width, m_roiImageSize.height }, &hammingBufferSize8u);
// 				m_hammingBuffer8u = (Ipp8u*)ippMalloc(hammingBufferSize8u);
				
// 				int hammingBufferSize16u;
// 				ippiWinHammingGetBufferSize(IppDataType::ipp16u, { m_roiImageSize.width, m_roiImageSize.height }, &hammingBufferSize16u);
// 				m_hammingBuffer16u = (Ipp8u*)ippMalloc(hammingBufferSize16u);
			}

			virtual bool Apply(std::any const&, std::any const&, ImageInfo &) { return true; };
		
		protected:
			void FFTShift(Ipp32f* data)
			{
				//Copy quadrant 1 data to buf
				IppStatus status = ippiCopy_32f_C1R(data + m_quadImageWidth, m_fftImageStep, m_ipp32Quad1Buf, m_quadImageStep, m_ippQuadSize);
				//Copy quadrant 2 data to buf
				status = ippiCopy_32f_C1R(data, m_fftImageStep, m_ipp32Quad2Buf, m_quadImageStep, m_ippQuadSize);
				//Copy quadrant 3 data to buf
				status = ippiCopy_32f_C1R(data + m_fftImageSize.width * m_quadImageHeight, m_fftImageStep, m_ipp32Quad3Buf, m_quadImageStep, m_ippQuadSize);
				//Copy quadrant 4 data to buf
				status = ippiCopy_32f_C1R(data + m_quadImageWidth + m_fftImageSize.width * m_quadImageHeight, m_fftImageStep, m_ipp32Quad4Buf, m_quadImageStep, m_ippQuadSize);
				//Copy Quadrant 1 to Quadrant 3(buf in data)
				status = ippiCopy_32f_C1R(m_ipp32Quad1Buf, m_quadImageStep, data + m_fftImageSize.width * m_quadImageHeight, m_fftImageStep, m_ippQuadSize);
				//Copy Quadrant 3 to Quadrant 1(buf in data)
				status = ippiCopy_32f_C1R(m_ipp32Quad3Buf, m_quadImageStep, data + m_quadImageWidth, m_fftImageStep, m_ippQuadSize);
				//Copy Quadrant 2 to Quadrant 4(buf in data)
				status = ippiCopy_32f_C1R(m_ipp32Quad2Buf, m_quadImageStep, data + m_quadImageWidth + m_fftImageSize.width * m_quadImageHeight, m_fftImageStep, m_ippQuadSize);
				//Copy Quadrant 4 to Quadrant 2(buf in data)
				status = ippiCopy_32f_C1R(m_ipp32Quad4Buf, m_quadImageStep, data, m_fftImageStep, m_ippQuadSize);
			}

		protected:
			Size m_imageSize;
			Size m_fftImageSize;
			int m_orderX;
			int m_orderY;
			int m_quadImageWidth;
			int m_quadImageHeight;
			int m_fftImageStep;
			int m_quadImageStep;			

			IppiFFTSpec_R_32f* m_spec;
			Ipp8u *m_ipp8uBuf;
			Ipp8u *m_ipp8uPackBuf;
			Ipp32f *m_ipp32FftBuf;
			IppiSize m_ippQuadSize;
			Ipp32f *m_ipp32Quad1Buf;
			Ipp32f *m_ipp32Quad2Buf;
			Ipp32f *m_ipp32Quad3Buf;
			Ipp32f *m_ipp32Quad4Buf;

			std::shared_ptr<CImage32f1cIPPI> m_fftImage32f1c;
			std::shared_ptr<CImage32f1cIPPI> m_magImage32f1c;

			std::mutex m_mutex;			
		};


		/// \brief CFFT8u1c.
		class CFFT8u1c : public CFFT
		{
		public:
			CFFT8u1c()
			{
				
			}

			~CFFT8u1c() override = default;

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

				std::lock_guard<std::mutex> lock(m_mutex);
				if ((m_fftImageSize.width != dst->Width()) || (m_fftImageSize.height != dst->Height()))
				{
					outImageInfo.size = m_fftImageSize;
					outImageInfo.bitDepth = 8;

					return false;
				}

				ELDER::OPERATOR::CImageConvertROI<ELDER::OPERATOR::CConvertROI8u1cTo32f1c>::ConvertROI(src, m_fftImage32f1c, {0, 0});
				
				auto status = ippiFFTFwd_RToPack_32f_C1R
				(
					m_fftImage32f1c->Data(),
					m_fftImage32f1c->WidthBytes(),
					m_ipp32FftBuf,
					m_fftImageStep,
					m_spec,
					m_ipp8uBuf
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT8u1c::Apply => ippiFFTFwd_RToPack_32f_C1R failed!");

				status = ippiMagnitudePack_32f_C1R
				(
					m_ipp32FftBuf,
					m_fftImageStep,
					m_magImage32f1c->Data(),
					m_fftImageStep,
					{ m_fftImageSize.width, m_fftImageSize.height },
					m_ipp8uPackBuf
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT8u1c::Apply => ippiMagnitudePack_32f_C1R failed!");

				OPERATOR::CImageAddConstant<ELDER::OPERATOR::CAddConstant32f1c>::AddConstant(m_magImage32f1c, 1.0f);
				status = ippiLn_32f_C1R
				(
					m_magImage32f1c->Data(),
					m_fftImageStep,
					m_fftImage32f1c->Data(),
					m_fftImage32f1c->WidthBytes(),
					{ m_fftImageSize.width, m_fftImageSize.height }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT8u1c::Apply => ippiLn_32f_C1R failed!");

				FFTShift(m_fftImage32f1c->Data());

 				float max = OPERATOR::CImageMax<ELDER::OPERATOR::CMax32f1c>::Max(m_fftImage32f1c);
 				float min = OPERATOR::CImageMin<ELDER::OPERATOR::CMin32f1c>::Min(m_fftImage32f1c);
				if ((max - min) > kEpsinon32)
				{
					float scale = kMaxIntensity8u / (max - min);
					OPERATOR::CImageSubConstant<ELDER::OPERATOR::CSubConstant32f1c>::SubConstant(m_fftImage32f1c, min);
					OPERATOR::CImageMulConstant<ELDER::OPERATOR::CMulConstant32f1c>::MulConstant(m_fftImage32f1c, scale);
				}
				else
				{
					OPERATOR::CImageSetConstant<ELDER::OPERATOR::CSetConstant32f1c>::SetConstant(m_fftImage32f1c, 0);
				}
 				
				OPERATOR::CImageConvert<ELDER::OPERATOR::CConvert32f1cTo8u1c>::Convert(m_fftImage32f1c, dst);

				return true;
			}
		};


		/// \brief CFFT16u1c.
		class CFFT16u1c : public CFFT
		{
		public:
			CFFT16u1c()
			{
			}

			~CFFT16u1c() override = default;

			bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
			{
				ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageIn Format");
				ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageOut Format");
				auto src = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageIn);
				ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
				ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
				ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
				auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
				ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

				std::lock_guard<std::mutex> lock(m_mutex);
				if ((m_fftImageSize.width != dst->Width()) || (m_fftImageSize.height != dst->Height()))
				{
					outImageInfo.size = m_fftImageSize;
					outImageInfo.bitDepth = 8;

					return false;
				}

				OPERATOR::CImageConvertROI<ELDER::OPERATOR::CConvertROI16u1cTo32f1c>::ConvertROI(src, m_fftImage32f1c, { 0, 0 });
				IppStatus status = ippiFFTFwd_RToPack_32f_C1R
				(
					m_fftImage32f1c->Data(),
					m_fftImage32f1c->WidthBytes(),
					m_ipp32FftBuf,
					m_fftImageStep,
					m_spec,
					m_ipp8uBuf
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT16u1c::Apply => ippiFFTFwd_RToPack_32f_C1R failed!");

				status = ippiMagnitudePack_32f_C1R
				(
					m_ipp32FftBuf,
					m_fftImageStep,
					m_magImage32f1c->Data(),
					m_fftImageStep,
					{ m_fftImageSize.width, m_fftImageSize.height },
					m_ipp8uPackBuf
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT16u1c::Apply => ippiMagnitudePack_32f_C1R failed!");

				OPERATOR::CImageAddConstant<ELDER::OPERATOR::CAddConstant32f1c>::AddConstant(m_magImage32f1c, 1.0f);
				status = ippiLn_32f_C1R
				(
					m_magImage32f1c->Data(),
					m_fftImageStep,
					m_fftImage32f1c->Data(),
					m_fftImage32f1c->WidthBytes(),
					{ m_fftImageSize.width, m_fftImageSize.height }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT16u1c::Apply => ippiLn_32f_C1R failed!");

				FFTShift(m_fftImage32f1c->Data());
 				float max = OPERATOR::CImageMax<ELDER::OPERATOR::CMax32f1c>::Max(m_fftImage32f1c);
 				float min = OPERATOR::CImageMin<ELDER::OPERATOR::CMin32f1c>::Min(m_fftImage32f1c);
				if ((max - min) > kEpsinon32)
				{
					float scale = kMaxIntensity8u / (max - min);
					OPERATOR::CImageSubConstant<ELDER::OPERATOR::CSubConstant32f1c>::SubConstant(m_fftImage32f1c, min);
					OPERATOR::CImageMulConstant<ELDER::OPERATOR::CMulConstant32f1c>::MulConstant(m_fftImage32f1c, scale);
				}
				else
				{
					OPERATOR::CImageSetConstant<ELDER::OPERATOR::CSetConstant32f1c>::SetConstant(m_fftImage32f1c, 0);
				}
				OPERATOR::CImageConvert<ELDER::OPERATOR::CConvert32f1cTo8u1c>::Convert(m_fftImage32f1c, dst);

				return true;
			}
		};


		/// \brief CFFT32f1c.
		class CFFT32f1c : public CFFT
		{
		public:
			CFFT32f1c()
			{
			}

			~CFFT32f1c() override = default;

			bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo) override
			{
				ASSERT_LOG(imageIn.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageIn Format");
				ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageOut Format");
				auto src = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageIn);
				ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
				ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
				ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
				auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
				ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

				std::lock_guard<std::mutex> lock(m_mutex);
				if ((m_fftImageSize.width != dst->Width()) || (m_fftImageSize.height != dst->Height()))
				{
					outImageInfo.size = m_fftImageSize;
					outImageInfo.bitDepth = 8;

					return false;
				}

				auto status = ippiFFTFwd_RToPack_32f_C1R
				(
					m_fftImage32f1c->Data(),
					m_fftImage32f1c->WidthBytes(),
					m_ipp32FftBuf,
					m_fftImageStep,
					m_spec,
					m_ipp8uBuf
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT32f1c::Apply => ippiFFTFwd_RToPack_32f_C1R failed!");

				status = ippiMagnitudePack_32f_C1R
				(
					m_ipp32FftBuf,
					m_fftImageStep,
					m_magImage32f1c->Data(),
					m_fftImageStep,
					{ m_fftImageSize.width, m_fftImageSize.height },
					m_ipp8uPackBuf
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT32f1c::Apply => ippiMagnitudePack_32f_C1R failed!");

				OPERATOR::CImageAddConstant<ELDER::OPERATOR::CAddConstant32f1c>::AddConstant(m_magImage32f1c, 1.0f);
				status = ippiLn_32f_C1R
				(
					m_magImage32f1c->Data(),
					m_fftImageStep,
					m_fftImage32f1c->Data(),
					m_fftImage32f1c->WidthBytes(),
					{ m_fftImageSize.width, m_fftImageSize.height }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "CFFT32f1c::Apply => ippiLn_32f_C1R failed!");

				FFTShift(m_fftImage32f1c->Data());
				FFTShift(m_fftImage32f1c->Data());
				float max = OPERATOR::CImageMax<ELDER::OPERATOR::CMax32f1c>::Max(m_fftImage32f1c);
				float min = OPERATOR::CImageMin<ELDER::OPERATOR::CMin32f1c>::Min(m_fftImage32f1c);
				if ((max - min) > kEpsinon32)
				{
					float scale = kMaxIntensity8u / (max - min);
					OPERATOR::CImageSubConstant<ELDER::OPERATOR::CSubConstant32f1c>::SubConstant(m_fftImage32f1c, min);
					OPERATOR::CImageMulConstant<ELDER::OPERATOR::CMulConstant32f1c>::MulConstant(m_fftImage32f1c, scale);
				}
				else
				{
					OPERATOR::CImageSetConstant<ELDER::OPERATOR::CSetConstant32f1c>::SetConstant(m_fftImage32f1c, 0);
				}
				OPERATOR::CImageConvert<ELDER::OPERATOR::CConvert32f1cTo8u1c>::Convert(m_fftImage32f1c, dst);

				return true;
			}
		};
	}
}


#endif