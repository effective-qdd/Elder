/**
* \file ImageMenaStdDev.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.15
*/
#ifndef _IMAGE_MEAN_STD_DEV_H
#define _IMAGE_MEAN_STD_DEV_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	/// \brief About basic operator on image.
	namespace OPERATOR
	{
		/// \brief CMeanStdDev8u1c.
		class CMeanStdDev8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MeanStdDev(T const& src, double& mean, double& stdDev)
			{
				IppStatus status = ippiMean_StdDev_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T &>(src).Data()),
					src.WidthBytes(),
					{ src.Width(), src.Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MeanStdDev(T const* const src, double& mean, double& stdDev)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiMean_StdDev_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T *>(src)->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MeanStdDev(std::shared_ptr<T> const& src, double& mean, double& stdDev)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiMean_StdDev_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_8u_C1R failed!");
			}
		};

		/// \brief CMeanStdDev16u1c.
		class CMeanStdDev16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MeanStdDev(T const& src, double& mean, double& stdDev)
			{
				IppStatus status = ippiMean_StdDev_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					{ src.Width(), src.Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MeanStdDev(T const* const src, double& mean, double& stdDev)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiMean_StdDev_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MeanStdDev(std::shared_ptr<T> const& src, double& mean, double& stdDev)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiMean_StdDev_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_16u_C1R failed!");
			}
		};

		/// \brief CMeanStdDev32f1c.
		class CMeanStdDev32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MeanStdDev(T const& src, double& mean, double& stdDev)
			{
				IppStatus status = ippiMean_StdDev_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					{ src.Width(), src.Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MeanStdDev(T const* const src, double& mean, double& stdDev)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiMean_StdDev_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MeanStdDev(std::shared_ptr<T> const& src, double& mean, double& stdDev)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiMean_StdDev_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&mean,
					&stdDev
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMean_StdDev_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_mean_dev_operators
		{
			static_assert((std::is_same<T, CMeanStdDev8u1c>::value
				|| std::is_same<T, CMeanStdDev16u1c>::value
				|| std::is_same<T, CMeanStdDev32f1c>::value),
				"The template parameter is not an mean dev operator!");
		};


		/// CImageMeanStdDev
		/// Operator:
		///
		/// Support image format :
		/// CImage8u1cIPPI
	    /// CImage16u1cIPPI
	    /// CImage32f1cIPPI
		template<class Operator>
		class CImageMeanStdDev : private Operator, is_mean_dev_operators<Operator>
		{
		public:
			template<typename T>
			static void MeanStdDev(T&& src, double& mean, double& stdDev)
			{
				Operator::MeanStdDev(std::forward<T>(src), mean, stdDev);
			};
		};
	}
}

#endif