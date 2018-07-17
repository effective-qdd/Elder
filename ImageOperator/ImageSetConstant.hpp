/**
* \file ImageSetConstant.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_SET_CONSTANT_H
#define _IMAGE_SET_CONSTANT_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CSetConstant8u1c
		class CSetConstant8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
				static void SetConstant(T& image, typename T::Type value)
			{
				IppStatus status = ippiSet_8u_C1R
				(
					value, 
					reinterpret_cast<Ipp8u*>(image.Data()), 
					image.WidthBytes(), 
					{ image.Width(), image.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
				static void SetConstant(T* const image, typename T::Type value)
			{
				IppStatus status = ippiSet_8u_C1R
				(
					value, 
					reinterpret_cast<Ipp8u*>(image->Data()), 
					image->WidthBytes(), 
					{ image->Width(), image->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SetConstant(std::shared_ptr<T> const& image, typename T::Type value)
			{
				IppStatus status = ippiSet_8u_C1R
				(
					value, 
					reinterpret_cast<Ipp8u*>(image->Data()), 
					image->WidthBytes(), 
					{ image->Width(), image->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_8u_C1R failed!");
			}
		};


		/// \brief CSetConstant16u1c
		class CSetConstant16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SetConstant(T& image, typename T::Type value)
			{
				IppStatus status = ippiSet_16u_C1R
				(
					value, 
					reinterpret_cast<Ipp16u*>(image.Data()),
					image.WidthBytes(), 
					{ image.Width(), image.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SetConstant(T* const image, typename T::Type value)
			{
				IppStatus status = ippiSet_16u_C1R
				(
					value,
					reinterpret_cast<Ipp16u*>(image->Data()),
					image->WidthBytes(),
					{ image->Width(), image->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SetConstant(std::shared_ptr<T> const& image, typename T::Type value)
			{
				IppStatus status = ippiSet_16u_C1R
				(
					value,
					reinterpret_cast<Ipp16u*>(image->Data()), 
					image->WidthBytes(), 
					{ image->Width(), image->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_16u_C1R failed!");
			}
		};


		/// \brief CSetConstant32f1c
		class CSetConstant32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SetConstant(T& image, typename T::Type value)
			{
				IppStatus status = ippiSet_32f_C1R
				(
					value,
					reinterpret_cast<Ipp32f*>(image.Data()),
					image.WidthBytes(), 
					{ image.Width(), image.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SetConstant(T* const image, typename T::Type value)
			{
				IppStatus status = ippiSet_32f_C1R
				(
					value,
					reinterpret_cast<Ipp32f*>(image->Data()),
					image->WidthBytes(), 
					{ image->Width(), image->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SetConstant(std::shared_ptr<T> const& image, typename T::Type value)
			{
				IppStatus status = ippiSet_32f_C1R
				(
					value,
					reinterpret_cast<Ipp32f*>(image->Data()),
					image->WidthBytes(),
					{ image->Width(), image->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSet_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_set_constant_operators
		{
			static_assert((std::is_same<T, CSetConstant8u1c>::value
				|| std::is_same<T, CSetConstant16u1c>::value
				|| std::is_same<T, CSetConstant32f1c>::value),
				"The template parameter is not an set constant operator!");
		};


		/// CImageSetConstant
		/// SetConstant(A, V)
		template<class Operator>
		class CImageSetConstant : private Operator, is_set_constant_operators<Operator>
		{
		public:
			template<typename T>
			static void SetConstant(T& image, typename T::Type value)
			{
				Operator::SetConstant(image, value);
			};

			template<typename T>
			static void SetConstant(T* const image, typename T::Type value)
			{
				ASSERT_LOG(image != nullptr, "image ptr is null!");
				Operator::SetConstant(image, value);
			};

			template<typename T>
			static void SetConstant(std::shared_ptr<T> const& image, typename T::Type value)
			{
				ASSERT_LOG(image != nullptr, "image ptr is null!");
				Operator::SetConstant(image, value);
			};
		};
	}
}


#endif

