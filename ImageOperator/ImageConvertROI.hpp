/**
* \file ImageConvertROI.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_CONVERT_ROI_H
#define _IMAGE_CONVERT_ROI_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CConvertROI8u1cTo16u1c
		class CConvertROI8u1cTo16u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertROI(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()), 
					src.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst.Data()) + dstOffset, 
					dst.WidthBytes(), 
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}
		};


		/// \brief CConvertROI8u1cTo32f1c
		class CConvertROI8u1cTo32f1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertROI(T1 const &src, T2 &dst, const Point &offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()), 
					src.WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst.Data()) + dstOffset, 
					dst.WidthBytes(), 
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}

			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}
		};


		/// \brief CConvertROI8u4cTo8u1cR
		class CConvertROI8u4cTo8u1cR : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type
			>
			static void ConvertROI(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiCopy_8u_C4C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()) + dstOffset,
					dst.WidthBytes(),
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
			}


			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_8u_C4C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
			}


			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiCopy_8u_C4C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
			}
		};


		/// \brief CConvertROI16u1cTo32f1c
		class CConvertROI16u1cTo32f1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertROI(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()) + dstOffset,
					dst.WidthBytes(),
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}
		};


		/// \brief CConvertROI16u1cTo8u1c
		class CConvertROI16u1cTo8u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertROI(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()), 
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()) + dstOffset, 
					dst.WidthBytes(), 
					{ src.Width(), src.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), { src->Width(), src->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}
		};


		/// \brief CConvertROI32f1cTo8u1c
		class CConvertROI32f1cTo8u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertROI(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1&>(src).Data()), 
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()) + dstOffset,
					dst.WidthBytes(), 
					{ src.Width(), src.Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset, 
					dst->WidthBytes(), 
					{ src->Width(), src->Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}
		};


		/// \brief CConvertROI32f1cTo16u1c
		class CConvertROI32f1cTo16u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertROI(T1 const &src, T2 &dst, const Point &offset)
			{
				ASSERT_LOG((offset.x + src.Width()) <= dst.Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src.Height()) <= dst.Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst.Width();
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1&>(src).Data()),
					src.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst.Data()) + dstOffset,
					dst.WidthBytes(),
					{ src.Width(), src.Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertROI(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(),
					{ src->Width(), src->Height() }, 
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertROI(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + src->Width()) <= dst->Width(), "offset x + src width > dst width!");
				ASSERT_LOG((offset.y + src->Height()) <= dst->Height(), "offset y + src height > dst height!");
				int dstOffset = offset.x + offset.y * dst->Width();
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()) + dstOffset,
					dst->WidthBytes(), 
					{ src->Width(), src->Height() }, 
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f16u_C1R failed!");
			}
		};


		template<class T>
		struct is_convert_roi_operators
		{
			static_assert((std::is_same<T, CConvertROI8u1cTo16u1c>::value
				|| std::is_same<T, CConvertROI8u1cTo32f1c>::value
				|| std::is_same<T, CConvertROI16u1cTo32f1c>::value
				|| std::is_same<T, CConvertROI16u1cTo8u1c>::value
				|| std::is_same<T, CConvertROI32f1cTo8u1c>::value
				|| std::is_same<T, CConvertROI32f1cTo16u1c>::value),
				"The template parameter is not an convert offset operator!");
		};


		/// CImageConvertROI
		/// ConvertROI(A, B, offset) => B = B.offset(A)
		template<class Operator>
		class CImageConvertROI : private Operator, is_convert_roi_operators<Operator>
		{
		public:
			template<typename T1, typename T2>
			static void ConvertROI(T1&& src, T2&& dst, Point const& offset)
			{
				Operator::ConvertROI(std::forward<T1>(src), std::forward<T2>(dst), offset);
			};
		};
	}
}

#endif



