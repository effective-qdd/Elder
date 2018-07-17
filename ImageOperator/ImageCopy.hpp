/**
* \file ImageCopy.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_COPY_H
#define _IMAGE_COPY_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CCopy8u1c.
		class CCopy8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Copy(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T &>(src).Data()), 
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Copy(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}

			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Copy(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}
		};


		/// \brief CCopy16u1c.
		class CCopy16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Copy(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Copy(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Copy(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}
		};


		/// \brief CAdd32f1c.
		class CCopy32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Copy(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f *>(const_cast<T &>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp32f *>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}

			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Copy(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f *>(const_cast<T *>(src)->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f *>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}

			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Copy(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}
		};
		

		template<class T>
		struct is_copy_operators
		{
			static_assert((std::is_same<T, CCopy8u1c>::value
				|| std::is_same<T, CCopy16u1c>::value
				|| std::is_same<T, CCopy32f1c>::value),
				"The template parameter is not an copy operator!");
		};


		/// CImageCopy
		/// Copy(A, B) => A = B;
		template<class Operator>
		class CImageCopy : private Operator, is_copy_operators<Operator>
		{
		public:
			template<typename T>
			static void Copy(T&& dst, T&& src)
			{
				Operator::Copy(std::forward<T>(dst), std::forward<T>(src));
			};
		};
	}
}


#endif