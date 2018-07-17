/**
* \file ImageMorphologyClose.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.06.28
*/
#ifndef _IMAGE_MORPHOLOGY_CLOSE_H
#define _IMAGE_MORPHOLOGY_CLOSE_H

// My Class Includes
#include "ImageMorphologyBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace MORPHOLOGY
		{
			/// \brief CClose.
			class CClose : public IMorphology
			{
			public:
				CClose()
					: IMorphology()
					, m_imageSize{ 0, 0 }
					, m_maskSize{ 0, 0 }
					, m_buf(nullptr)
					, m_morphSpec(nullptr)
				{

				}

				/// \brief Free buffer for all subclass.
				virtual ~CClose()
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

				/// \brief Initialize COpen params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, Size maskSize)
				{
					
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size					m_imageSize;
				Size					m_maskSize;
				Ipp8u*					m_buf;
				IppiMorphAdvState*		m_morphSpec;
				std::mutex				m_mutex;
			};


			/// \brief CClose8u1c.
			class CClose8u1c : public CClose
			{
			public:
				CClose8u1c()
					: CClose()
				{}

				~CClose8u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto morphSpecSize = 0;
						auto bufferSize = 0;					
						auto status = ippiMorphAdvGetSize_8u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							&morphSpecSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphAdvGetSize_8u_C1R failed!");

						if (m_morphSpec != nullptr) ippsFree(m_morphSpec);
						m_morphSpec = (IppiMorphAdvState*)ippsMalloc_8u(morphSpecSize);
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

						status = ippiMorphAdvInit_8u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_morphSpec,
							m_buf
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphAdvInit_8u_C1R failed!");
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
					auto status = ippiMorphCloseBorder_8u_C1R
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
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphCloseBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CClose16u1c.
			class CClose16u1c : public CClose
			{
			public:
				CClose16u1c()
					: CClose()
				{}

				~CClose16u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto morphSpecSize = 0;
						auto bufferSize = 0;
						auto status = ippiMorphAdvGetSize_16u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							&morphSpecSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphAdvGetSize_16u_C1R failed!");

						if (m_morphSpec != nullptr) ippsFree(m_morphSpec);
						m_morphSpec = (IppiMorphAdvState*)ippsMalloc_8u(morphSpecSize);
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

						status = ippiMorphAdvInit_16u_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_morphSpec,
							m_buf
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphAdvInit_16u_C1R failed!");
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
					auto status = ippiMorphCloseBorder_16u_C1R
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
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphCloseBorder_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CClose32f1c.
			class CClose32f1c : public CClose
			{
			public:
				CClose32f1c()
					: CClose()
				{}

				~CClose32f1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto morphSpecSize = 0;
						auto bufferSize = 0;						
						auto status = ippiMorphAdvGetSize_32f_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							{ m_maskSize.width, m_maskSize.height },
							&morphSpecSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphAdvGetSize_32f_C1R failed!");

						if (m_morphSpec != nullptr) ippsFree(m_morphSpec);
						m_morphSpec = (IppiMorphAdvState*)ippsMalloc_8u(morphSpecSize);
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

						status = ippiMorphAdvInit_32f_C1R
						(
							{ m_imageSize.width, m_imageSize.height },
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_morphSpec,
							m_buf
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphAdvInit_32f_C1R failed!");
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
					auto status = ippiMorphCloseBorder_32f_C1R
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
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMorphCloseBorder_32f_C1R failed!");

					return true;
				}
			};
		}

		
	}
}
#endif
