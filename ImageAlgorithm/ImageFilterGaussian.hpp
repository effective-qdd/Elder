/**
* \file ImageFilterGaussian.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.05
*/
#ifndef _IMAGE_FILTER_GAUSSIAN_H
#define _IMAGE_FILTER_GAUSSIAN_H


// My Class Includes
#include "ImageFilterBase.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			/// \brief CGaussian.
			class CGaussian : public IFilter
			{
			public:
				CGaussian()
					: IFilter()
					, m_imageSize{ 0, 0 }
					, m_kernelSize(0)
					, m_sigma(0.0f)
					, m_spec(nullptr)
					, m_buf8u(nullptr)
				{}

				/// \brief Free buffer for all subclass.
				virtual ~CGaussian()
				{
					if (m_spec != nullptr)
					{
						ippFree(m_spec);
						m_spec = nullptr;
					}
					if (m_buf8u != nullptr)
					{
						ippsFree(m_buf8u);
						m_buf8u = nullptr;
					}
				}

				/// \brief Initialize CGaussian params.
				/// \warning Border value is applicable only to the kConst border type.
				virtual void Initialize(Size imageSize, int kernelSize, float sigma)
				{

				}

				/// \brief Set CGaussian sigma.
				/// \note Change the sigma. The CGaussian need to do Initialize if the sigma is different with current value. 
				virtual void SetSigma(float sigma)
				{

				}

				virtual bool Apply(std::any const&, std::any const&) { return true; };

			protected:
				Size					m_imageSize;
				int						m_kernelSize;
				float					m_sigma;
				IppFilterGaussianSpec	*m_spec;
				Ipp8u					*m_buf8u;
				std::mutex				m_mutex;
			};


			/// \brief CGaussian8u1c.
			class CGaussian8u1c : public CGaussian
			{
			public:
				CGaussian8u1c()
					: CGaussian()
				{}

				~CGaussian8u1c() = default;

				void Initialize(Size imageSize, int kernelSize, float sigma = 0.5f)
				{
					if (m_imageSize != imageSize || m_kernelSize != kernelSize)
					{
						m_imageSize = imageSize;
						m_kernelSize = kernelSize;
						int specSize = 0;
						int bufferSize = 0;
						auto status = ippiFilterGaussianGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							m_kernelSize,
							ipp8u,
							1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianGetBufferSize failed!");

						if (m_spec != nullptr) ippFree(m_spec);
						m_spec = (IppFilterGaussianSpec*)ippMalloc(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");
					}

					SetSigma(sigma);					
				}

				void SetSigma(float sigma)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (m_sigma != sigma)
					{
						m_sigma = sigma;
						auto status = ippiFilterGaussianInit
						(
							{ m_imageSize.width, m_imageSize.height },
							m_kernelSize,
							m_sigma,
							ippBorderRepl,
							ipp8u,
							1,
							m_spec,
							m_buf8u
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianInit failed!");
					}
				}

				bool  Apply(std::any const& imageIn, std::any const& imageOut) override
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
					auto status = ippiFilterGaussianBorder_8u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						0,
						m_spec,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianBorder_8u_C1R failed!");

					return true;
				}
			};


			/// \brief CGaussian16u1c.
			class CGaussian16u1c : public CGaussian
			{
			public:
				CGaussian16u1c()
					: CGaussian()
				{}

				~CGaussian16u1c() = default;

				void Initialize(Size imageSize, int kernelSize, float sigma = 0.5f)
				{
					if (m_imageSize != imageSize || m_kernelSize != kernelSize)
					{
						m_imageSize = imageSize;
						m_kernelSize = kernelSize;
						int specSize = 0;
						int bufferSize = 0;
						auto status = ippiFilterGaussianGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							m_kernelSize,
							ipp16u,
							1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianGetBufferSize failed!");

						if (m_spec != nullptr) ippFree(m_spec);
						m_spec = (IppFilterGaussianSpec*)ippMalloc(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");
					}

					SetSigma(sigma);
				}

				void SetSigma(float sigma)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (m_sigma != sigma)
					{
						m_sigma = sigma;
						auto status = ippiFilterGaussianInit
						(
							{ m_imageSize.width, m_imageSize.height },
							m_kernelSize,
							m_sigma,
							ippBorderRepl,
							ipp16u,
							1,
							m_spec,
							m_buf8u
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianInit failed!");
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
					auto status = ippiFilterGaussianBorder_16u_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						0,
						m_spec,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianBorder_16u_C1R failed!");

					return true;
				}
			};


			/// \brief CGaussian32f1c.
			class CGaussian32f1c : public CGaussian
			{
			public:
				CGaussian32f1c()
					: CGaussian()
				{}

				~CGaussian32f1c() = default;

				void Initialize(Size imageSize, int kernelSize, float sigma = 0.5f)
				{
					if (m_imageSize != imageSize || m_kernelSize != kernelSize)
					{
						m_imageSize = imageSize;
						m_kernelSize = kernelSize;
						int specSize = 0;
						int bufferSize = 0;
						auto status = ippiFilterGaussianGetBufferSize
						(
							{ m_imageSize.width, m_imageSize.height },
							m_kernelSize,
							ipp32f,
							1,
							&specSize,
							&bufferSize
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianGetBufferSize failed!");

						if (m_spec != nullptr) ippFree(m_spec);
						m_spec = (IppFilterGaussianSpec*)ippMalloc(specSize);
						ENSURE_THROW_MSG(m_spec != nullptr, "ippMalloc failed!");

						if (m_buf8u != nullptr) ippsFree(m_buf8u);
						m_buf8u = ippsMalloc_8u(bufferSize);
						ENSURE_THROW_MSG(m_buf8u != nullptr, "ippsMalloc_8u failed!");
					}
					SetSigma(sigma);
				}

				void SetSigma(float sigma)
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (m_sigma != sigma)
					{
						m_sigma = sigma;
						auto status = ippiFilterGaussianInit
						(
							{ m_imageSize.width, m_imageSize.height },
							m_kernelSize,
							m_sigma,
							ippBorderRepl,
							ipp32f,
							1,
							m_spec,
							m_buf8u
						);
						ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianInit failed!");
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
					auto status = ippiFilterGaussianBorder_32f_C1R
					(
						src->Data(),
						src->WidthBytes(),
						dst->Data(),
						dst->WidthBytes(),
						{ m_imageSize.width, m_imageSize.height },
						0.0f,
						m_spec,
						m_buf8u
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiFilterGaussianBorder_32f_C1R failed!");

					return true;
				}
			};
		}
	}
}
#endif
