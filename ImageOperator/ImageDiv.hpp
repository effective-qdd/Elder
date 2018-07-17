/**
* \file ImageDiv.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_DIV_H
#define _IMAGE_DIV_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CDiv8u1c
		class CDiv8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Div(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiDiv_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Div(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiDiv_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Div(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiDiv_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Div(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src2).Data()),
					src2.WidthBytes(), 
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src1).Data()), 
					src1.WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst.Data()), 
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Div(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src2)->Data()), 
					src2->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src1)->Data()), 
					src1->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Div(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(src2->Data()), 
					src2->WidthBytes(),
					reinterpret_cast<Ipp8u*>(src1->Data()),
					src1->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_8u_C1RSfs failed!");
			}
		};


		/// \brief CDiv16u1c
		class CDiv16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Div(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiDiv_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Div(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiDiv_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Div(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiDiv_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Div(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src2).Data()),
					src2.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src1).Data()),
					src1.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Div(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src2)->Data()),
					src2->WidthBytes(),
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src1)->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Div(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src2->Data()), 
					src2->WidthBytes(),
					reinterpret_cast<Ipp16u*>(src1->Data()), 
					src1->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_16u_C1RSfs failed!");
			}
		};


		/// \brief CDiv32f1c
		class CDiv32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Div(T &dst, T const &src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiDiv_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Div(T * const dst, T const * const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiDiv_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(const_cast<T *>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Div(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiDiv_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Div(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src2).Data()), 
					src2.WidthBytes(), 
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src1).Data()), 
					src1.WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Div(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src2)->Data()),
					src2->WidthBytes(),
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src1)->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Div(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiDiv_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src2->Data()),
					src2->WidthBytes(),
					reinterpret_cast<Ipp32f*>(src1->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDiv_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_div_operators
		{
			static_assert((std::is_same<T, CDiv8u1c>::value
				|| std::is_same<T, CDiv16u1c>::value
				|| std::is_same<T, CDiv32f1c>::value),
				"The template parameter is not an div operator!");
		};


		/// CImageDiv
		/// Div(A, B) => A = A / B;
		/// Div(A, B, C) => A = B / C;
		template<class Operator>
		class CImageDiv : private Operator, is_div_operators<Operator>
		{
		public:
			template<typename T>
			static void Div(T&& dst, T&& src)
			{
				Operator::Div(std::forward<T>(dst), std::forward<T>(src));
			};

			template<typename T>
			static void Div(T&& dst, T&& src1, T&& src2)
			{
				Operator::Div(std::forward<T>(dst), std::forward<T>(src1), std::forward<T>(src2));
			};
		};
	}
}


#endif


