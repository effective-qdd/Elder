/**
* \file ImageConvertCrop.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_CONVERT_CROP_H
#define _IMAGE_CONVERT_CROP_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CConvertCrop8u1cTo16u1c
		class CConvertCrop8u1cTo16u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()) + srcOffset,
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertCrop(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()) + srcOffset, 
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}
		};


		/// \brief CConvertCrop8u1cTo32f1c
		class CConvertCrop8u1cTo32f1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertCrop(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()) + srcOffset,
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()), 
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertCrop(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertCrop(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()) + srcOffset, 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}
		};


		/*************************************************************************
		** Class Name: CConvertCrop8u4cTo8u1cR
		*************************************************************************/
// 		class CConvertCrop8u4cTo8u1cR : public CNonCopyable
// 		{
// 		protected:
// 			template<typename T1, typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value, int>::type = 0,
// 				typename T2, typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value, int>::type = 0>
// 				static void ConvertCrop(T1 const &src, T2 &dst, const ImageROI &roi)
// 			{
// 				ENSURE_THROW_MSG(roi.width == dst.Width(), "roi width != dst width!");
// 				ENSURE_THROW_MSG(roi.height == dst.Height(), "roi height != dst height!");
// 				ENSURE_THROW_MSG((roi.x + roi.width) <= src.Width(), "roi.x + roi.width > src width!");
// 				ENSURE_THROW_MSG((roi.y + roi.height) <= src.Height(), "roi.y + roi.height > src height!");
// 				int srcOffset = roi.x + roi.y * src.Width();
// 				IppStatus status = ippiCopy_8u_C4C1R(reinterpret_cast<Ipp8u *>(const_cast<T1 &>(src).Data()) + srcOffset, src.WidthBytes(), reinterpret_cast<Ipp8u *>(dst.Data()), dst.WidthBytes(), { dst.Width(), dst.Height() });
// 				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
// 			}
// 
// 
// 			template<typename T1, typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value, int>::type = 0,
// 				typename T2, typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value, int>::type = 0>
// 				static void ConvertCrop(T1 const *src, T2 *dst, const ImageROI &roi)
// 			{
// 				ENSURE_THROW_MSG(src != nullptr, "src ptr is null!");
// 				ENSURE_THROW_MSG(dst != nullptr, "dst ptr is null!");
// 				ENSURE_THROW_MSG(roi.width == dst->Width(), "roi width != dst width!");
// 				ENSURE_THROW_MSG(roi.height == dst->Height(), "roi height != dst height!");
// 				ENSURE_THROW_MSG((roi.x + roi.width) <= src->Width(), "roi.x + roi.width > src width!");
// 				ENSURE_THROW_MSG((roi.y + roi.height) <= src->Height(), "roi.y + roi.height > src height!");
// 				int srcOffset = roi.x + roi.y * src->Width();
// 				IppStatus status = ippiCopy_8u_C4C1R(reinterpret_cast<Ipp8u *>(const_cast<T1 *>(src)->Data()) + srcOffset, src->WidthBytes(), reinterpret_cast<Ipp8u *>(dst->Data()), dst->WidthBytes(), { dst->Width(), dst->Height() });
// 				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
// 			}
// 
// 			template<typename T1, typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value, int>::type = 0,
// 				typename T2, typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value, int>::type = 0>
// 				static void ConvertCrop(std::shared_ptr<T1> const &src, std::shared_ptr<T2> const &dst, const ImageROI &roi)
// 			{
// 				ENSURE_THROW_MSG(src != nullptr, "src ptr is null!");
// 				ENSURE_THROW_MSG(dst != nullptr, "dst ptr is null!");
// 				ENSURE_THROW_MSG(roi.width == dst->Width(), "roi width != dst width!");
// 				ENSURE_THROW_MSG(roi.height == dst->Height(), "roi height != dst height!");
// 				ENSURE_THROW_MSG((roi.x + roi.width) <= src->Width(), "roi.x + roi.width > src width!");
// 				ENSURE_THROW_MSG((roi.y + roi.height) <= src->Height(), "roi.y + roi.height > src height!");
// 				int srcOffset = roi.x + roi.y * src->Width();
// 				IppStatus status = ippiCopy_8u_C4C1R(reinterpret_cast<Ipp8u *>(src->Data()) + srcOffset, src->WidthBytes(), reinterpret_cast<Ipp8u *>(dst->Data()), dst->WidthBytes(), { dst->Width(), dst->Height() });
// 				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
// 			}
// 		};


		/// \brief CConvertCrop16u1cTo32f1c
		class CConvertCrop16u1cTo32f1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertCrop(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()) + srcOffset,
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertCrop(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()) + srcOffset,
					src->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}

			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void ConvertCrop(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()) + srcOffset, 
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}
		};


		/// \brief CConvertCrop16u1cTo8u1c
		class CConvertCrop16u1cTo8u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()) + srcOffset,
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()) + srcOffset,
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertCrop(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}
		};


		/*************************************************************************
		** Class Name: CConvertCrop16u4cTo16u1cR
		*************************************************************************/
// 		class CConvertCrop16u4cTo16u1cR : public CNonCopyable
// 		{
// 		protected:
// 			template<typename T1, typename std::enable_if<std::is_same<T1, CImage<CIDT16U, CICH4, CImageIPPI>>::value, int>::type = 0,
// 				typename T2, typename std::enable_if<std::is_same<T2, CImage<CIDT16U, CICH1, CImageIPPI>>::value, int>::type = 0>
// 				static void ConvertCrop(T1 const &src, T2 &dst, const ImageROI &roi)
// 			{
// 				ENSURE_THROW_MSG(roi.width == dst.Width(), "roi width != dst width!");
// 				ENSURE_THROW_MSG(roi.height == dst.Height(), "roi height != dst height!");
// 				ENSURE_THROW_MSG((roi.x + roi.width) <= src.Width(), "roi.x + roi.width > src width!");
// 				ENSURE_THROW_MSG((roi.y + roi.height) <= src.Height(), "roi.y + roi.height > src height!");
// 				int srcOffset = roi.x + roi.y * src.Width();
// 				IppStatus status = ippiCopy_16u_C4C1R(reinterpret_cast<Ipp16u *>(const_cast<T1 &>(src).Data()) + srcOffset, src.WidthBytes(), reinterpret_cast<Ipp16u *>(dst.Data()), dst.WidthBytes(), { dst.Width(), dst.Height() });
// 				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C4C1R failed!");
// 			}
// 
// 
// 			template<typename T1, typename std::enable_if<std::is_same<T1, CImage<CIDT16U, CICH4, CImageIPPI>>::value, int>::type = 0,
// 				typename T2, typename std::enable_if<std::is_same<T2, CImage<CIDT16U, CICH1, CImageIPPI>>::value, int>::type = 0>
// 				static void ConvertCrop(T1 const *src, T2 *dst, const ImageROI &roi)
// 			{
// 				ENSURE_THROW_MSG(src != nullptr, "src ptr is null!");
// 				ENSURE_THROW_MSG(dst != nullptr, "dst ptr is null!");
// 				ENSURE_THROW_MSG(roi.width == dst->Width(), "roi width != dst width!");
// 				ENSURE_THROW_MSG(roi.height == dst->Height(), "roi height != dst height!");
// 				ENSURE_THROW_MSG((roi.x + roi.width) <= src->Width(), "roi.x + roi.width > src width!");
// 				ENSURE_THROW_MSG((roi.y + roi.height) <= src->Height(), "roi.y + roi.height > src height!");
// 				int srcOffset = roi.x + roi.y * src->Width();
// 				IppStatus status = ippiCopy_16u_C4C1R(reinterpret_cast<Ipp16u *>(const_cast<T1 *>(src)->Data()) + srcOffset, src->WidthBytes(), reinterpret_cast<Ipp16u *>(dst->Data()), dst->WidthBytes(), { dst->Width(), dst->Height() });
// 				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C4C1R failed!");
// 			}
// 
// 			template<typename T1, typename std::enable_if<std::is_same<T1, CImage<CIDT16U, CICH4, CImageIPPI>>::value, int>::type = 0,
// 				typename T2, typename std::enable_if<std::is_same<T2, CImage<CIDT16U, CICH1, CImageIPPI>>::value, int>::type = 0>
// 				static void ConvertCrop(std::shared_ptr<T1> const &src, std::shared_ptr<T2> const &dst, const ImageROI &roi)
// 			{
// 				ENSURE_THROW_MSG(src != nullptr, "src ptr is null!");
// 				ENSURE_THROW_MSG(dst != nullptr, "dst ptr is null!");
// 				ENSURE_THROW_MSG(roi.width == dst->Width(), "roi width != dst width!");
// 				ENSURE_THROW_MSG(roi.height == dst->Height(), "roi height != dst height!");
// 				ENSURE_THROW_MSG((roi.x + roi.width) <= src->Width(), "roi.x + roi.width > src width!");
// 				ENSURE_THROW_MSG((roi.y + roi.height) <= src->Height(), "roi.y + roi.height > src height!");
// 				int srcOffset = roi.x + roi.y * src->Width();
// 				IppStatus status = ippiCopy_16u_C4C1R(reinterpret_cast<Ipp16u *>(src->Data()) + srcOffset, src->WidthBytes(), reinterpret_cast<Ipp16u *>(dst->Data()), dst->WidthBytes(), { dst->Width(), dst->Height() });
// 				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C4C1R failed!");
// 			}
// 		};


		/// \brief CConvertCrop32f1cTo8u1c
		class CConvertCrop32f1cTo8u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1&>(src).Data()) + srcOffset, 
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1*>(src)->Data()) + srcOffset, 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void ConvertCrop(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()) + srcOffset, 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}
		};


		/// \brief CConvertCrop32f1cTo16u1c
		class CConvertCrop32f1cTo16u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const& src, T2& dst, Point const& offset)
			{
				ASSERT_LOG((offset.x + dst.Width()) <= src.Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst.Height()) <= src.Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src.Width();
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1&>(src).Data()) + srcOffset,
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertCrop(T1 const* const src, T2* const dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1*>(src)->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f16u_C1R failed!");
			}


			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void ConvertCrop(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst, Point const& offset)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG((offset.x + dst->Width()) <= src->Width(), "offset x + dst width > src width!");
				ASSERT_LOG((offset.y + dst->Height()) <= src->Height(), "offset y + dst height > src height!");
				int srcOffset = offset.x + offset.y * src->Width();
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()) + srcOffset,
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f16u_C1R failed!");
			}
		};


		template<class T>
		struct is_convert_crop_operators
		{
			static_assert((std::is_same<T, CConvertCrop8u1cTo16u1c>::value
				|| std::is_same<T, CConvertCrop8u1cTo32f1c>::value
				|| std::is_same<T, CConvertCrop16u1cTo32f1c>::value
				|| std::is_same<T, CConvertCrop16u1cTo8u1c>::value
				|| std::is_same<T, CConvertCrop32f1cTo8u1c>::value
				|| std::is_same<T, CConvertCrop32f1cTo16u1c>::value),
				"The template parameter is not an convert crop operator!");
		};


		/// CImageConvertCrop
		/// Operator
		/// ConvertCrop(A, B, offset) => B = A.offset
		template<class Operator>
		class CImageConvertCrop : private Operator, is_convert_crop_operators<Operator>
		{
		public:
			template<typename T1, typename T2>
			static void ConvertCrop(T1&& src, T2&& dst, Point const& offset)
			{
				Operator::ConvertCrop(std::forward<T1>(src), std::forward<T2>(dst), offset);
			};
		};
	}
}

#endif


