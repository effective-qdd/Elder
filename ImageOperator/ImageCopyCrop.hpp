/**
* \file ImageCopyCrop.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_COPY_CROP_H
#define _IMAGE_COPY_CROP_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{	
		/// \brief CCopyCrop8u1c
		class CCopyCrop8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void CopyCrop(T& dst, T const& src, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()) + srcOffset,
					src.WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void CopyCrop(T* const dst, T const* const src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()) + srcOffset, 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void CopyCrop(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()) + srcOffset, 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}
		};


		/// \brief CCopyCrop16u1c
		class CCopyCrop16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void CopyCrop(T& dst, T const& src, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()) + srcOffset, 
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void CopyCrop(T* const dst, T const* const src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void CopyCrop(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}
		};


		/// \brief CCopyCrop32f1c
		class CCopyCrop32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void CopyCrop(T& dst, T const& src, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T &>(src).Data()) + srcOffset,
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void CopyCrop(T* const dst, T const* const src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()) + srcOffset, 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void CopyCrop(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_copy_crop_operators
		{
			static_assert((std::is_same<T, CCopyCrop8u1c>::value
				|| std::is_same<T, CCopyCrop16u1c>::value
				|| std::is_same<T, CCopyCrop32f1c>::value),
				"The template parameter is not an copy crop operator!");
		};


		/// CImageCopyCrop
		/// CopyCrop(A, B, offset) => A = B.offset
		template<class Operator>
		class CImageCopyCrop : private Operator, is_copy_crop_operators<Operator>
		{
		public:
			template<typename T>
			static void CopyCrop(T && dst, T && src, const Point &offset)
			{
				Operator::CopyCrop(std::forward<T>(dst), std::forward<T>(src), offset);
			};
		};
	}
}


#endif