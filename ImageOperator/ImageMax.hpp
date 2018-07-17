/**
* \file ImageMax.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.06
*/
#ifndef _IMAGE_MAX_H
#define _IMAGE_MAX_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CMax8u1c
		class CMax8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type>
			static IDT8U Max(T const &src)
			{
				IDT8U max = 0;
				IppStatus status = ippiMax_8u_C1R
				(
					reinterpret_cast<Ipp8u *>(const_cast<T &>(src).Data()),
					src.WidthBytes(),
					{ src.Width(), src.Height() }, 
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_8u_C1R failed!");
				return max;
			}


			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type>
			static IDT8U Max(T const * const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT8U max = 0;
				IppStatus status = ippiMax_8u_C1R
				(
					reinterpret_cast<Ipp8u *>(const_cast<T *>(src)->Data()),
					src->WidthBytes(), 
					{ src->Width(), src->Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_8u_C1R failed!");
				return max;
			}


			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type>
			static IDT8U Max(std::shared_ptr<T> const &src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT8U max = 0;
				IppStatus status = ippiMax_8u_C1R
				(
					reinterpret_cast<Ipp8u *>(src->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_8u_C1R failed!");
				return max;
			}
		};


		/// \brief CMax16u1c
		class CMax16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT16U, CICH1, CImageIPPI>>::value>::type>
			static IDT16U Max(T const &src)
			{
				IDT16U max = 0;
				IppStatus status = ippiMax_16u_C1R
				(
					reinterpret_cast<Ipp16u *>(const_cast<T &>(src).Data()),
					src.WidthBytes(),
					{ src.Width(), src.Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_16u_C1R failed!");
				return max;
			}


			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT16U, CICH1, CImageIPPI>>::value>::type>
			static IDT16U Max(T const * const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT16U max = 0;
				IppStatus status = ippiMax_16u_C1R				
				(
					reinterpret_cast<Ipp16u *>(const_cast<T *>(src)->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_16u_C1R failed!");
				return max;
			}


			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT16U, CICH1, CImageIPPI>>::value>::type>
			static IDT16U Max(std::shared_ptr<T> const &src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT16U max = 0;
				IppStatus status = ippiMax_16u_C1R
				(
					reinterpret_cast<Ipp16u *>(src->Data()), 
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_16u_C1R failed!");
				return max;
			}
		};


		/// \brief CMax32f1c
		class CMax32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT32F, CICH1, CImageIPPI>>::value>::type>
			static IDT32F Max(T const &src)
			{
				IDT32F max = 0;
				IppStatus status = ippiMax_32f_C1R
				(
					reinterpret_cast<Ipp32f *>(const_cast<T &>(src).Data()), 
					src.WidthBytes(),
					{ src.Width(), src.Height() }, 
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_32f_C1R failed!");
				return max;
			}


			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT32F, CICH1, CImageIPPI>>::value>::type>
			static IDT32F Max(T const * const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT32F max = 0;
				IppStatus status = ippiMax_32f_C1R
				(
					reinterpret_cast<Ipp32f *>(const_cast<T *>(src)->Data()), 
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_32f_C1R failed!");
				return max;
			}


			template<class T, class = typename std::enable_if<std::is_same<T, CImage<CIDT32F, CICH1, CImageIPPI>>::value>::type>
			static IDT32F Max(std::shared_ptr<T> const &src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT32F max = 0;
				IppStatus status = ippiMax_32f_C1R
				(
					reinterpret_cast<Ipp32f *>(src->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&max
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMax_32f_C1R failed!");
				return max;
			}
		};


		template<class T>
		struct is_max_operators
		{
			static_assert((std::is_same<T, CMax8u1c>::value
				|| std::is_same<T, CMax16u1c>::value
				|| std::is_same<T, CMax32f1c>::value),
				"The template parameter is not an max operator!");
		};


		/// CImageMax
		/// max = Max(A);
		template<class Operator>
		class CImageMax : private Operator, is_max_operators<Operator>
		{
		public:
			template<typename T>
			static typename T::Type Max(T const &src)
			{
				return Operator::Max(src);
			};


			template<typename T>
			static typename T::Type Max(T const * const src)
			{
				return Operator::Max(src);
			};


			template<typename T>
			static typename T::Type Max(std::shared_ptr<T> const &src)
			{
				return Operator::Max(src);
			};
		};
	}
}


#endif
