/**
* \file ImageMin.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.06
*/
#ifndef _IMAGE_MIN_H
#define _IMAGE_MIN_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CMin8u1c
		class CMin8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static IDT8U Min(T const& src)
			{
				IDT8U min = 0;
				IppStatus status = ippiMin_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()), 
					src.WidthBytes(),
					{ src.Width(), src.Height() }, 
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_8u_C1R failed!");
				return min;
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static IDT8U Min(T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT8U min = 0;
				IppStatus status = ippiMin_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(), 
					{ src->Width(), src->Height() },
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_8u_C1R failed!");
				return min;
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static IDT8U Min(std::shared_ptr<T> const &src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT8U min = 0;
				IppStatus status = ippiMin_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					{ src->Width(), src->Height() },
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_8u_C1R failed!");
				return min;
			}
		};


		/// \brief CMin16u1c
		class CMin16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static IDT16U Min(T const& src)
			{
				IDT16U min = 0;
				IppStatus status = ippiMin_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(), 
					{ src.Width(), src.Height() },
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_16u_C1R failed!");
				return min;
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static IDT16U Min(T const* const src)
			{
				IDT16U min = 0;
				IppStatus status = ippiMin_16u_C1R(reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()), src->WidthBytes(), { src->Width(), src->Height() }, &min);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_16u_C1R failed!");
				return min;
			}

			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static IDT16U Min(std::shared_ptr<T> const& src)
			{
				IDT16U min = 0;
				IppStatus status = ippiMin_16u_C1R(reinterpret_cast<Ipp16u*>(src->Data()), src->WidthBytes(), { src->Width(), src->Height() }, &min);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_16u_C1R failed!");
				return min;
			}
		};


		/// \brief CMin32f1c
		class CMin32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static IDT32F Min(T const& src)
			{
				IDT32F min = 0.0f;
				IppStatus status = ippiMin_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					{ src.Width(), src.Height() },
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_32f_C1R failed!");
				return min;
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static IDT32F Min(T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT32F min = 0.0f;
				IppStatus status = ippiMin_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(), 
					{ src->Width(), src->Height() },
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_32f_C1R failed!");
				return min;
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static IDT32F Min(std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IDT32F min = 0.0f;
				IppStatus status = ippiMin_32f_C1R
				(
					reinterpret_cast<Ipp32f *>(src->Data()), 
					src->WidthBytes(),
					{ src->Width(), src->Height() }, 
					&min
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMin_32f_C1R failed!");
				return min;
			}
		};


		template<class T>
		struct is_min_operators
		{
			static_assert((std::is_same<T, CMin8u1c>::value
				|| std::is_same<T, CMin16u1c>::value
				|| std::is_same<T, CMin32f1c>::value),
				"The template parameter is not an min operator!");
		};


		/// CsrcMin
		/// min = Min(A);
		template<class Operator>
		class CImageMin : private Operator, is_min_operators<Operator>
		{
		public:
			template<typename T>
			static typename T::Type Min(T const& src)
			{
				return Operator::Min(src);
			};


			template<typename T>
			static typename T::Type Min(T const* const src)
			{
				return Operator::Min(src);
			};


			template<typename T>
			static typename T::Type Min(std::shared_ptr<T> const& src)
			{
				return Operator::Min(src);
			};
		};
	}
}


#endif