/**
* \file ImageMorphologyErode.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.06.28
*/
#ifndef _IMAGE_MORPHOLOGY_ERODE_H
#define _IMAGE_MORPHOLOGY_ERODE_H

// My Class Includes
#include "ImageMorphologyBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace MORPHOLOGY
		{
			/// \brief CErode.
			class CErode : public IMorphology
			{
			public:
				CErode()
					: IMorphology()
					, m_imageSize{ 0, 0 }
					, m_maskSize{ 0, 0 }
					, m_buf(nullptr)
					, m_morphSpec(nullptr)
				{

				}

				/// \brief Free buffer for all subclass.
				virtual ~CErode()
				{
					if (m_buf != nullptr)
					{
						ippsFree(m_buf);
						m_buf = nullptr;
					}

					if (m_morphSpec != nullptr)
					{
						ippsFree(m_morphSpec);
						m_morphSpec = nullptr;
					}
				}

				/// \brief Initialize CErode params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, Size maskSize)
				{
					
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size					m_imageSize;
				Size					m_maskSize;
				Ipp8u*					m_buf;
				IppiMorphState*			m_morphSpec;
				std::mutex				m_mutex;
			};


			/// \brief CErode8u1c.
			class CErode8u1c : public CErode
			{
			public:
				CErode8u1c()
					: CErode()
				{}

				~CErode8u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto morphSpecSize = 0;
						auto bufferSize = 0;						
						auto status = ippiMorphologyBorderGetSize_8u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							&morphSpecSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphologyBorderGetSize_8u_C1R failed!");

						if (m_morphSpec != nullptr) ippsFree(m_morphSpec);
						m_morphSpec = (IppiMorphState*)ippsMalloc_8u(morphSpecSize);
						ENSURE_THROW_MSG(m_morphSpec != nullptr, "ippsMalloc_8u failed!");
						if (m_buf != nullptr) ippsFree(m_buf);
						m_buf = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf != nullptr, "ippsMalloc_8u failed!");

						Ipp8u* kernel = new Ipp8u[m_maskSize.width * m_maskSize.height];
						for (auto i = 0; i < m_maskSize.width * m_maskSize.height; ++i)
						{
							kernel[i] = 1;
						}
						kernel[(m_maskSize.width * m_maskSize.height + 1) / 2] = 0;

						status = ippiMorphologyBorderInit_8u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_morphSpec,
							m_buf
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphologyBorderInit_8u_C1R failed!");
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

					std::lock_guard<std::mutex> lock(m_mutex);
					Ipp8u borderValue = 0;
					auto status = ippiErodeBorder_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						ippBorderRepl,
						borderValue,
						m_morphSpec,
						m_buf
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiErodeBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CErode16u1c.
			class CErode16u1c : public CErode
			{
			public:
				CErode16u1c()
					: CErode()
				{}

				~CErode16u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto morphSpecSize = 0;
						auto bufferSize = 0;						
						auto status = ippiMorphologyBorderGetSize_16u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							&morphSpecSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphologyBorderGetSize_16u_C1R failed!");

						if (m_morphSpec != nullptr) ippsFree(m_morphSpec);
						m_morphSpec = (IppiMorphState*)ippsMalloc_8u(morphSpecSize);
						ENSURE_THROW_MSG(m_morphSpec != nullptr, "ippsMalloc_8u failed!");
						if (m_buf != nullptr) ippsFree(m_buf);
						m_buf = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf != nullptr, "ippsMalloc_8u failed!");

						Ipp8u* kernel = new Ipp8u[m_maskSize.width * m_maskSize.height];
						for (auto i = 0; i < m_maskSize.width * m_maskSize.height; ++i)
						{
							kernel[i] = 1;
						}
						kernel[(m_maskSize.width * m_maskSize.height + 1) / 2] = 0;

						status = ippiMorphologyBorderInit_16u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_morphSpec,
							m_buf
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphologyBorderInit_16u_C1R failed!");
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
					Ipp16u borderValue = 0;
					auto status = ippiErodeBorder_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						ippBorderRepl,
						borderValue,
						m_morphSpec,
						m_buf
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiErodeBorder_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CErode32f1c.
			class CErode32f1c : public CErode
			{
			public:
				CErode32f1c()
					: CErode()
				{}

				~CErode32f1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto morphSpecSize = 0;
						auto bufferSize = 0;						
						auto status = ippiMorphologyBorderGetSize_32f_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							&morphSpecSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphologyBorderGetSize_32f_C1R failed!");

						if (m_morphSpec != nullptr) ippsFree(m_morphSpec);
						m_morphSpec = (IppiMorphState*)ippsMalloc_8u(morphSpecSize);
						ENSURE_THROW_MSG(m_morphSpec != nullptr, "ippsMalloc_8u failed!");
						if (m_buf != nullptr) ippsFree(m_buf);
						m_buf = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf != nullptr, "ippsMalloc_8u failed!");

						Ipp8u* kernel = new Ipp8u[m_maskSize.width * m_maskSize.height];
						for (auto i = 0; i < m_maskSize.width * m_maskSize.height; ++i)
						{
							kernel[i] = 1;
						}
						kernel[(m_maskSize.width * m_maskSize.height + 1) / 2] = 0;

						status = ippiMorphologyBorderInit_32f_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_morphSpec,
							m_buf
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphologyBorderInit_32f_C1R failed!");
					}
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
					Ipp32f borderValue = 0;
					auto status = ippiErodeBorder_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						ippBorderRepl,
						borderValue,
						m_morphSpec,
						m_buf
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiErodeBorder_32f_C1R failed!");

					return true;
				}
			};
		}		
	}
}
#endif
