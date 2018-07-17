/**
* \file ImageMul.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_MUL_H
#define _IMAGE_MUL_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CMul8u1c
		class CMul8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Mul(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiMul_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Mul(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiMul_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Mul(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiMul_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Mul(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src1).Data()), 
					src1.WidthBytes(),
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src2).Data()), 
					src2.WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Mul(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src1)->Data()), 
					src1->WidthBytes(),
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src2)->Data()),
					src2->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Mul(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(src1->Data()),
					src1->WidthBytes(), 
					reinterpret_cast<Ipp8u*>(src2->Data()),
					src2->WidthBytes(),
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_8u_C1RSfs failed!");
			}
		};


		/// \brief CMul16u1c
		class CMul16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Mul(T &dst, T const &src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiMul_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst.Data()), 
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Mul(T * const dst, T const * const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiMul_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Mul(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiMul_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()), 
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Mul(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src1).Data()),
					src1.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src2).Data()),
					src2.WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Mul(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src1)->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src2)->Data()), 
					src2->WidthBytes(),
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Mul(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src1->Data()),
					src1->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(src2->Data()), 
					src2->WidthBytes(), 
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_16u_C1RSfs failed!");
			}
		};


		/// \brief CMul32f1c
		class CMul32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Mul(T& dst, T const& src)
			{
				ASSERT_LOG(src.Width() == dst.Width(), "src width != dst width!");
				ASSERT_LOG(src.Height() == dst.Height(), "src height != dst height!");
				IppStatus status = ippiMul_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Mul(T* const dst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiMul_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Mul(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src->Width() == dst->Width(), "src width != dst width!");
				ASSERT_LOG(src->Height() == dst->Height(), "src height != dst height!");
				IppStatus status = ippiMul_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Mul(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src1).Data()), 
					src1.WidthBytes(), 
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src2).Data()),
					src2.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Mul(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src1)->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src2)->Data()), 
					src2->WidthBytes(), 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Mul(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiMul_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src1->Data()), 
					src1->WidthBytes(),
					reinterpret_cast<Ipp32f*>(src2->Data()), 
					src2->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMul_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_mul_operators
		{
			static_assert((std::is_same<T, CMul8u1c>::value
				|| std::is_same<T, CMul16u1c>::value
				|| std::is_same<T, CMul32f1c>::value),
				"The template parameter is not an mul operator!");
		};


		/// CImageMul
		/// Mul(A, B) => A = A * B;
		/// Mul(A, B, C) => A = B * C;
		/// Mul(A, B, C) = Mul(A, C, B)
		template<class Operator>
		class CImageMul : private Operator, is_mul_operators<Operator>
		{
		public:
			template<typename T>
			static void Mul(T&& dst, T&& src)
			{
				Operator::Mul(std::forward<T>(dst), std::forward<T>(src));
			};


			template<typename T>
			static void Mul(T&& dst, T&& src1, T&& src2)
			{
				Operator::Mul(std::forward<T>(dst), std::forward<T>(src1), std::forward<T>(src2));
			};
		};
	}
}





#endif


