/**
* \file ImageFilterMean.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.22
*/
#ifndef _IMAGE_FILTER_MEAN_H
#define _IMAGE_FILTER_MEAN_H

// My Class Includes
#include "ImageFilterBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			/// \brief CMedian.
			class CMean : public IFilter
			{
			public:
				CMean()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_maskSize{ 0, 0 }
					, m_buf(nullptr)
					, m_spec(nullptr)
				{

				}

				/// \brief Free buffer for all subclass.
				virtual ~CMean()
				{
					if (m_buf != nullptr)
					{
						ippsFree(m_buf);
						m_buf = nullptr;
					}

					if (m_spec != nullptr)
					{
						ippsFree(m_spec);
						m_spec = nullptr;
					}
				}

				/// \brief Initialize CMedian params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, Size maskSize)
				{
					
				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size					m_imageSize;
				Size					m_maskSize;
				Ipp8u*					m_buf;
				IppiFilterBorderSpec*	m_spec;
				std::mutex				m_mutex;
			};


			/// \brief CMean8u1c.
			class CMean8u1c : public CMean
			{
			public:
				CMean8u1c()
					: CMean()
				{}

				~CMean8u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto bufferSize = 0;
						auto specSize = 0;
						auto status = ippiFilterBorderGetSize
						(
							{ m_maskSize.width, m_maskSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp8u,
							ipp16s,
							1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorderGetSize failed!");

						if (m_spec != nullptr) ippsFree(m_spec);
						m_spec = (IppiFilterBorderSpec *)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippsMalloc_8u failed!");
						if (m_buf != nullptr) ippsFree(m_buf);
						m_buf = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf != nullptr, "ippsMalloc_8u failed!");

						Ipp16s* kernel = new Ipp16s[m_maskSize.width * m_maskSize.height];
						for (auto i = 0; i < m_maskSize.width * m_maskSize.height; ++i)
						{
							kernel[i] = 1;
						}
						status = ippiFilterBorderInit_16s
						(
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_maskSize.width * m_maskSize.height,
							ipp8u,
							1,
							ippRndNear,
							m_spec
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorderInit_16s failed!");
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
					auto status = ippiFilterBorder_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						ippBorderRepl,
						&borderValue,
						m_spec,
						m_buf
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CMean16u1c.
			class CMean16u1c : public CMean
			{
			public:
				CMean16u1c()
					: CMean()
				{}

				~CMean16u1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto bufferSize = 0;
						auto specSize = 0;
						auto status = ippiFilterBorderGetSize
						(
							{ m_maskSize.width, m_maskSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp16u,
							ipp16s,
							1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorderGetSize failed!");

						if (m_spec != nullptr) ippsFree(m_spec);
						m_spec = (IppiFilterBorderSpec *)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippsMalloc_8u failed!");
						if (m_buf != nullptr) ippsFree(m_buf);
						m_buf = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf != nullptr, "ippsMalloc_8u failed!");

						Ipp16s* kernel = new Ipp16s[m_maskSize.width * m_maskSize.height];
						for (auto i = 0; i < m_maskSize.width * m_maskSize.height; ++i)
						{
							kernel[i] = 1;
						}
						status = ippiFilterBorderInit_16s
						(
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							m_maskSize.width * m_maskSize.height,
							ipp16u,
							1,
							ippRndNear,
							m_spec
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorderInit_16s failed!");
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
					auto status = ippiFilterBorder_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						ippBorderRepl,
						&borderValue,
						m_spec,
						m_buf
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorder_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CMean32f1c.
			class CMean32f1c : public CMean
			{
			public:
				CMean32f1c()
					: CMean()
				{}

				~CMean32f1c() = default;

				void Initialize(Size imageSize, Size maskSize)
				{
					if (m_imageSize != imageSize || m_maskSize != maskSize)
					{
						m_imageSize = imageSize;
						m_maskSize = maskSize;
						auto bufferSize = 0;
						auto specSize = 0;
						auto status = ippiFilterBorderGetSize
						(
							{ m_maskSize.width, m_maskSize.height },
							{ m_imageSize.width, m_imageSize.height },
							ipp32f,
							ipp32f,
							1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorderGetSize failed!");

						if (m_spec != nullptr) ippsFree(m_spec);
						m_spec = (IppiFilterBorderSpec *)ippsMalloc_8u(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippsMalloc_8u failed!");
						if (m_buf != nullptr) ippsFree(m_buf);
						m_buf = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf != nullptr, "ippsMalloc_8u failed!");

						Ipp32f* kernel = new Ipp32f[m_maskSize.width * m_maskSize.height];
						for (auto i = 0; i < m_maskSize.width * m_maskSize.height; ++i)
						{
							kernel[i] = 1.0f;
						}
						status = ippiFilterBorderInit_32f
						(
							kernel,
							{ m_maskSize.width, m_maskSize.height },
							ipp32f,
							1,
							ippRndNear,
							m_spec
						);
						delete[] kernel;
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorderInit_32f failed!");
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
					auto status = ippiFilterBorder_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						ippBorderRepl,
						&borderValue,
						m_spec,
						m_buf
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterBorder_32f_C1R failed!");

					return true;
				}
			};
		}

		
	}
}
#endif
