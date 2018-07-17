/**
* \file ImageConvert.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_CONVERT_H
#define _IMAGE_CONVERT_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CConvert8u1cTo16u1c
		class CConvert8u1cTo16u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()), 
					dst.WidthBytes(), { dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}

			
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()), 
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
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_8u16u_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u16u_C1R failed!");
			}
		};


		/// \brief CConvert8u1cTo32f1c
		class CConvert8u1cTo32f1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage8u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()),
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
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()),
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
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_8u32f_C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_8u32f_C1R failed!");
			}
		};


		/// \brief CConvert8u4cTo8u1cR
		class CConvert8u4cTo8u1cR : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiCopy_8u_C4C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1&>(src).Data()),
					src.WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst.Data()), 
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
			}


			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type
			>
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_8u_C4C1R
				(
					reinterpret_cast<Ipp8u*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
			}


			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT8U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT8U, CICH1, CImageIPPI>>::value>::type
			>
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_8u_C4C1R
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C4C1R failed!");
			}
		};


		/// \brief CConvert16u1cTo32f1c
		class CConvert16u1cTo32f1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage32f1cIPPI<T2>
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()),
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
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()),
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
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_16u32f_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u32f_C1R failed!");
			}
		};


		/// \brief CConvert16u1cTo8u1c
		class CConvert16u1cTo8u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage16u1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()),
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
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()), 
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
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_16u8u_C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_16u8u_C1R failed!");
			}
		};


		/// \brief CConvert16u4cTo16u1cR
		class CConvert16u4cTo16u1cR : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT16U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT16U, CICH1, CImageIPPI>>::value>::type
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiCopy_16u_C4C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C4C1R failed!");
			}


			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT16U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT16U, CICH1, CImageIPPI>>::value>::type
			>
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_16u_C4C1R
				(
					reinterpret_cast<Ipp16u*>(const_cast<T1*>(src)->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C4C1R failed!");
			}


			template
			<
				class T1, class = typename std::enable_if<std::is_same<T1, CImage<CIDT16U, CICH4, CImageIPPI>>::value>::type,
				class T2, class = typename std::enable_if<std::is_same<T2, CImage<CIDT16U, CICH1, CImageIPPI>>::value>::type
			>
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiCopy_16u_C4C1R
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C4C1R failed!");
			}
		};


		/// \brief CConvert32f1cTo8u1c
		class CConvert32f1cTo8u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage8u1cIPPI<T2>
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1&>(src).Data()), 
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
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1*>(src)->Data()),
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
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_32f8u_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }, 
					ippRndFinancial
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiConvert_32f8u_C1R failed!");
			}
		};


		/// \brief CConvert32f1cTo16u1c
		class CConvert32f1cTo16u1c : public CNonCopyable
		{
		protected:
			template
			<
				class T1, class = EnableIfCImage32f1cIPPI<T1>,
				class T2, class = EnableIfCImage16u1cIPPI<T2>
			>
			static void Convert(T1 const& src, T2& dst)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1&>(src).Data()),
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
			static void Convert(T1 const* const src, T2* const dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T1*>(src)->Data()),
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
			static void Convert(std::shared_ptr<T1> const& src, std::shared_ptr<T2> const& dst)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiConvert_32f16u_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
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
		struct is_convert_operators
		{
			static_assert((std::is_same<T, CConvert8u1cTo16u1c>::value
				|| std::is_same<T, CConvert8u1cTo32f1c>::value
				|| std::is_same<T, CConvert16u1cTo32f1c>::value
				|| std::is_same<T, CConvert16u1cTo8u1c>::value
				|| std::is_same<T, CConvert32f1cTo8u1c>::value
				|| std::is_same<T, CConvert32f1cTo16u1c>::value),
				"The template parameter is not an convert operator!");
		};

		/// CDEImageConvert
		/// Operator:
		/// Convert(A, B) => A -> B
		///
		/// Support image format:
		/// CImage8u1cIPPI to CImage16u1cIPPI
		/// CImage8u1cIPPI to CImage32f1cIPPI
		/// CImage16u1cIPPI to CImage32f1cIPPI
		/// CImage16u1cIPPI to CImage8u1cIPPI
		/// CImage32f1cIPPI to CImage8u1cIPPI
		/// CImage32f1cIPPI to CImage16u1cIPPI
		template<class Operator>
		class CImageConvert : private Operator, is_convert_operators<Operator>
		{
		public:
			/// 
			template<typename T1, typename T2>
			static void Convert(T1&& src, T2&& dst)
			{
				Operator::Convert(std::forward<T1>(src), std::forward<T2>(dst));
			};
		};
	}
}

#endif

