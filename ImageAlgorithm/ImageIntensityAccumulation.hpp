/**
* \file ImageAccumulation.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.07.04
*/
#ifndef _IMAGE_INTENSITY_ACCUMULATION_H
#define _IMAGE_INTENSITY_ACCUMULATION_H


// My Class Includes
#include "ImageIntensityBase.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageAdd.hpp"
#include "../ImageOperator/ImageCopy.hpp"
#include "../ImageOperator/ImageSetConstant.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			/// \brief CSum dst = (src1 + src2 + ... + srcn)
			class CAccumulation : public IIntensity
			{
			public:
				CAccumulation()
					: IIntensity()
					, m_sumImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{

				}

				virtual ~CAccumulation() override = default;

				virtual void Initialize(Size imageSize)
				{
					if (m_imageSize != imageSize)
					{
						m_imageSize = imageSize;
						m_sumImage32f1c->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
					}
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				std::shared_ptr<CImage32f1cIPPI> m_sumImage32f1c;
				Size m_imageSize;
			};


			/// \brief CAccumulation8u1c.
			class CAccumulation8u1c : public CAccumulation
			{
			public:
				CAccumulation8u1c()
					: CAccumulation()
					, m_tmpImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}


				~CAccumulation8u1c() override = default;

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						m_tmpImage32f1c->Initialize(imageSize.width, imageSize.height, nullptr);
						CAccumulation::Initialize(imageSize);
					}
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut)
				{
					ASSERT_LOG(imageIn.type() == typeid(std::list<std::any>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageOut Format");
					auto imgList = std::any_cast<std::list<std::any>>(imageIn);
					auto dst = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					OPERATOR::CImageSetConstant<OPERATOR::CSetConstant32f1c>::SetConstant(m_sumImage32f1c, 0.0f);
					for (const auto &img : imgList)
					{
						ASSERT_LOG(img.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error imageIn Format");
						auto src = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(img);
						ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
						ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
						ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
						OPERATOR::CImageConvert<OPERATOR::CConvert8u1cTo32f1c>::Convert(src, m_tmpImage32f1c);
						OPERATOR::CImageAdd<OPERATOR::CAdd32f1c>::Add(m_sumImage32f1c, m_tmpImage32f1c);
					}
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo8u1c>::Convert(m_sumImage32f1c, dst);

					return true;
				}

			protected:
				std::shared_ptr<CImage32f1cIPPI> m_tmpImage32f1c;

			};


			/// \brief CAccumulation16u1c.
			class CAccumulation16u1c : public CAccumulation
			{
			public:
				CAccumulation16u1c()
					: CAccumulation()
					, m_tmpImage32f1c(std::make_shared<CImage32f1cIPPI>())
				{}

				~CAccumulation16u1c() override = default;

				void Initialize(Size imageSize) override
				{
					if (m_imageSize != imageSize)
					{
						m_tmpImage32f1c->Initialize(imageSize.width, imageSize.height, nullptr);
						CAccumulation::Initialize(imageSize);
					}
				}

				bool Apply(std::any const& imageIn, std::any const& imageOut) override
				{
					ASSERT_LOG(imageIn.type() == typeid(std::list<std::any>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageOut Format");
					auto imgList = std::any_cast<std::list<std::any>>(imageIn);
					auto dst = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");

					OPERATOR::CImageSetConstant<OPERATOR::CSetConstant32f1c>::SetConstant(m_sumImage32f1c, 0.0f);
					for (const auto &img : imgList)
					{
						ASSERT_LOG(img.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error imageIn Format");
						auto src = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(img);
						ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
						ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
						ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
						OPERATOR::CImageConvert<OPERATOR::CConvert16u1cTo32f1c>::Convert(src, m_tmpImage32f1c);
						OPERATOR::CImageAdd<OPERATOR::CAdd32f1c>::Add(m_sumImage32f1c, m_tmpImage32f1c);
					}
					OPERATOR::CImageConvert<OPERATOR::CConvert32f1cTo16u1c>::Convert(m_sumImage32f1c, dst);

					return true;
				}


			protected:
				std::shared_ptr<CImage32f1cIPPI> m_tmpImage32f1c;
			};


			/// \brief CAccumulation32f1c.
			class CAccumulation32f1c : public CAccumulation
			{
			public:
				CAccumulation32f1c()
					: CAccumulation()
				{}

				~CAccumulation32f1c() override = default;

				bool Apply(std::any const& imageIn, std::any const& imageOut)
				{
					ASSERT_LOG(imageIn.type() == typeid(std::list<std::any>), "Error imageIn Format");
					ASSERT_LOG(imageOut.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageOut Format");
					auto imgList = std::any_cast<std::list<std::any>>(imageIn);
					auto dst = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(imageOut);
					ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");
					ASSERT_LOG(m_imageSize.width == dst->Width(), "m_imageSize.width != dst->Width()");
					ASSERT_LOG(m_imageSize.height == dst->Height(), "m_imageSize.height != dst->Height()");
					OPERATOR::CImageSetConstant<OPERATOR::CSetConstant32f1c>::SetConstant(/*m_sumImage32f1c*/dst, 0.0f);
					for (const auto &img : imgList)
					{
						ASSERT_LOG(img.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error imageIn Format");
						auto src = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(img);
						ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
						ASSERT_LOG(m_imageSize.width == src->Width(), "m_imageSize.width != src->Width()");
						ASSERT_LOG(m_imageSize.height == src->Height(), "m_imageSize.height != src->Height()");
						OPERATOR::CImageAdd<OPERATOR::CAdd32f1c>::Add(/*m_sumImage32f1c*/dst, src);
						// 					auto dstPtr = dst->Data();
						// 					auto dstStep = static_cast<int>(dst->WidthBytes() / sizeof(float));
						// 					auto srcPtr = src->Data();
						// 					auto srcStep = static_cast<int>(src->WidthBytes() / sizeof(float));
						// 					
						// #pragma omp parallel for num_threads(8)
						// 					for (int h = 0; h < m_imageSize.height; ++h)
						// 					{
						// 						for (int w = 0; w < m_imageSize.width; ++w)
						// 						{
						// 							dstPtr[w + dstStep * h] += srcPtr[w + srcStep * h];
						// 						}
						// 					}

					}
					//LOG_INFO("Break 3");
					//OPERATOR::CImageCopy<OPERATOR::CCopy32f1c>::Copy(dst, m_sumImage32f1c);

					return true;
				}
			};
		}
	}
}

#endif
