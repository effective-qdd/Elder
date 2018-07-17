/**
* \file ImageCopyROI.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_COPY_ROI_H
#define _IMAGE_COPY_ROI_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{	
		/// \brief CCopyROI8u1c
		class CCopyROI8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void CopyROI(T& dst, T const& src, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()) + dstOffset,
					dst.WidthBytes(),
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void CopyROI(T* const dst, T const* const src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void CopyROI(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_8u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}
		};


		/// \brief CCopyROI16u1c
		class CCopyROI16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void CopyROI(T& dst, T const& src, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()), 
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()) + dstOffset,
					dst.WidthBytes(),
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void CopyROI(T* const dst, T const* const src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void CopyROI(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_16u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}
		};


		/// \brief CCopyROI32f1c
		class CCopyROI32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void CopyROI(T& dst, T const& src, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()) + dstOffset,
					dst.WidthBytes(),
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void CopyROI(T* const dst, T const* const src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void CopyROI(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_copy_roi_operators
		{
			static_assert((std::is_same<T, CCopyROI8u1c>::value
				|| std::is_same<T, CCopyROI16u1c>::value
				|| std::is_same<T, CCopyROI32f1c>::value),
				"The template parameter is not an copy roi operator!");
		};


		/// CImageCopyROI
		/// CImageCopyROI(A, B, offset) => A = A.offset(B)
		template<class Operator>
		class CImageCopyROI : private Operator, is_copy_roi_operators<Operator>
		{
		public:
			template<typename T>
			static void CopyROI(T&& dst, T&& src, Point const& offset)
			{
				Operator::CopyROI(std::forward<T>(dst), std::forward<T>(src), offset);
			};
		};
	}
}


#endif