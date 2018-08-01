/**
* \file ImageFilterBilateral.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.05
*/
#ifndef _IMAGE_FILTER_BILATERAL_H
#define _IMAGE_FILTER_BILATERAL_H

// My Class Includes
#include "ImageFilterBase.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageSubConstant.hpp"
#include "../ImageOperator/ImageMulConstant.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			/// \brief CBilateral.
			class CBilateral : public IFilter
			{
			public:
				CBilateral()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_radius(0)
					, m_sigmaColor(0)
					, m_sigmaSpace(0)
				{}

				/// \brief Free buffer for all subclass.
				virtual ~CBilateral()
				{
					
				}

				/// \brief Initialize CBilateral params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
					}
				}

				virtual void SetRadius(int radius)
				{
					m_radius = radius;
				}

				virtual void SetSigmaColor(double sigmaColor)
				{
					m_sigmaColor = sigmaColor;
				}

				virtual void SetSigmaSpace(double sigmaSpace)
				{
					m_sigmaSpace = sigmaSpace;
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size						m_imageSize;
				int							m_radius;
				double						m_sigmaColor;
				double						m_sigmaSpace;
				std::mutex					m_mutex;
			};


			/// \brief CBilateral8u1c.
			class CBilateral8u1c : public CBilateral
			{
			public:
				CBilateral8u1c()
					: CBilateral()
				{}

				~CBilateral8u1c() = default;

				void Initialize(Size imageSize)
				{
					CBilateral::Initialize(imageSize);
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
					try
					{
						cv::Mat srcMat(src->Height(), src->Width(), CV_8UC1, src->Data(), src->WidthBytes());
						cv::Mat dstMat(dst->Height(), dst->Width(), CV_8UC1, dst->Data(), dst->WidthBytes());
						cv::bilateralFilter
						(
							srcMat,
							dstMat,
							m_radius,
							m_sigmaColor,
							m_sigmaSpace
						);
					}
					catch (std::exception)
					{
						THROW_MSG("bilateralFilter failed!")
					}

					return true;
				}
			};


			/// \brief CBilateral16u1c.
			class CBilateral16u1c : public CBilateral
			{
			public:
				CBilateral16u1c()
					: CBilateral()
					, m_srcImage32f1c(std::make_shared<CImage32f1cIPPI>())
					, m_dstImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CBilateral16u1c() = default;

				void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;

						m_srcImage32f1c->Initialize(m_imageSize.width, m_imageSize.height);
						m_dstImage32f1c->Initialize(m_imageSize.width, m_imageSize.height);
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
					OPERATOR::CImageConvert<OPERATOR::CConvert16u1cTo32f1c>::Convert(src, m_srcImage32f1c);
					try
					{
						cv::Mat srcMat(m_srcImage32f1c->Height(), m_srcImage32f1c->Width(), CV_32FC1, m_srcImage32f1c->Data(), m_srcImage32f1c->WidthBytes());
						cv::Mat dstMat(m_dstImage32f1c->Height(), m_dstImage32f1c->Width(), CV_32FC1, m_dstImage32f1c->Data(), m_dstImage32f1c->WidthBytes());
						cv::bilateralFilter
						(
							srcMat,
							dstMat,
							m_radius,
							m_sigmaColor,
							m_sigmaSpace
						);
					}
					catch (std::exception)
					{
						THROW_MSG("bilateralFilter failed!")
					}
					
					float min = 0.0f;
					float max = 0.0f;
					auto status = ippiMinMax_32f_C1R
					(
						m_dstImage32f1c->Data(),
						m_dstImage32f1c->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						&min,
						&max
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMinMax_32f_C1R failed!");

					if (abs(max - min) > kEpsinon32)
					{
						auto k = (65535.0f - 0.0f) / (max - min);
						OPERATOR::CImageSubConstant<OPERATOR::CSubConstant32f1c>::SubConstant(m_dstImage32f1c, min);
						OPERATOR::CImageMulConstant<OPERATOR::CMulConstant32f1c>::MulConstant(m_dstImage32f1c, k);
					}
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_dstImage32f1c, dst);

					return true;
				}

			private:
				std::shared_ptr<CImage32f1cIPPI> m_srcImage32f1c;
				std::shared_ptr<CImage32f1cIPPI> m_dstImage32f1c;
			};


			/// \brief CBilateral32f1c.
			class CBilateral32f1c : public CBilateral
			{
			public:
				CBilateral32f1c()
					: CBilateral()
				{}

				~CBilateral32f1c() = default;

				void Initialize(Size imageSize)
				{
					CBilateral::Initialize(imageSize);
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
					try
					{
						cv::Mat srcMat(src->Height(), src->Width(), CV_32FC1, src->Data(), src->WidthBytes());
						cv::Mat dstMat(dst->Height(), dst->Width(), CV_32FC1, dst->Data(), dst->WidthBytes());
						cv::bilateralFilter
						(
							srcMat,
							dstMat,
							m_radius,
							m_sigmaColor,
							m_sigmaSpace
						);
					}
					catch (std::exception)
					{
						THROW_MSG("bilateralFilter failed!")
					}

					return true;
				}
			};
		}
	}
}
#endif
