/**
* \file ImageAdd.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_ADD_H
#define _IMAGE_ADD_H

#include <type_traits>

// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	/// \brief About basic operator on image.
	namespace OPERATOR
	{
		/// \brief CAdd8u1c.
		class CAdd8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Add(T& srcdst, T const& src)
			{
				ASSERT_LOG(src.Width() == srcdst.Width(), "src width != srcdst width!");
				ASSERT_LOG(src.Height() == srcdst.Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp8u*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Add(T* const srcdst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src->Width() == srcdst->Width(), "src width != srcdst width!");
				ASSERT_LOG(src->Height() == srcdst->Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Add(std::shared_ptr<T> const& srcdst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src->Width() == srcdst->Width(), "src width != srcdst width!");
				ASSERT_LOG(src->Height() == srcdst->Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_8u_C1IRSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Add(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_8u_C1RSfs
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
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Add(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_8u_C1RSfs
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
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_8u_C1RSfs failed!");
			}			


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void Add(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_8u_C1RSfs
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
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_8u_C1RSfs failed!");
			}
		};


		/// \brief CAdd16u1c.
		class CAdd16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Add(T& srcdst, T const& src)
			{
				ASSERT_LOG(src.Width() == srcdst.Width(), "src width != srcdst width!");
				ASSERT_LOG(src.Height() == srcdst.Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					reinterpret_cast<Ipp16u*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Add(T* const srcdst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src->Width() == srcdst->Width(), "src width != srcdst width!");
				ASSERT_LOG(src->Height() == srcdst->Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Add(std::shared_ptr<T> const& srcdst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src->Width() == srcdst->Width(), "src width != srcdst width!");
				ASSERT_LOG(src->Height() == srcdst->Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_16u_C1IRSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Add(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_16u_C1RSfs
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
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Add(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_16u_C1RSfs
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
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void Add(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src1->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp16u*>(src2->Data()),
					src2->WidthBytes(), reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_16u_C1RSfs failed!");
			}
		};


		/// \brief CAdd32f1c.
		class CAdd32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Add(T& srcdst, T const& src)
			{
				ASSERT_LOG(src.Width() == srcdst.Width(), "src width != srcdst width!");
				ASSERT_LOG(src.Height() == srcdst.Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(const_cast<T &>(src).Data()),
					src.WidthBytes(), reinterpret_cast<Ipp32f*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Add(T* const srcdst, T const* const src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src->Width() == srcdst->Width(), "src width != srcdst width!");
				ASSERT_LOG(src->Height() == srcdst->Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Add(std::shared_ptr<T> const& srcdst, std::shared_ptr<T> const& src)
			{
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src->Width() == srcdst->Width(), "src width != srcdst width!");
				ASSERT_LOG(src->Height() == srcdst->Height(), "src height != srcdst height!");
				IppStatus status = ippiAdd_32f_C1IR
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(),
					reinterpret_cast<Ipp32f*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Add(T& dst, T const& src1, T const& src2)
			{
				ASSERT_LOG(src1.Width() == src2.Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1.Height() == src2.Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst.Width() == src1.Width(), "dst width != src1 width!");
				ASSERT_LOG(dst.Height() == src1.Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T &>(src1).Data()),
					src1.WidthBytes(),
					reinterpret_cast<Ipp32f*>(const_cast<T &>(src2).Data()),
					src2.WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Add(T* const dst, T const* const src1, T const* const src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src1)->Data()),
					src1->WidthBytes(),
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src2)->Data()),
					src2->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void Add(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src1, std::shared_ptr<T> const& src2)
			{
				ASSERT_LOG(src1 != nullptr, "src1 ptr is null!");
				ASSERT_LOG(src2 != nullptr, "src2 ptr is null!");
				ASSERT_LOG(dst != nullptr, "srcdst ptr is null!");
				ASSERT_LOG(src1->Width() == src2->Width(), "src1 width != src2 width!");
				ASSERT_LOG(src1->Height() == src2->Height(), "src1 height != src2 height!");
				ASSERT_LOG(dst->Width() == src1->Width(), "dst width != src1 width!");
				ASSERT_LOG(dst->Height() == src1->Height(), "dst height != src1 height!");
				IppStatus status = ippiAdd_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src1->Data()), 
					src1->WidthBytes(),
					reinterpret_cast<Ipp32f*>(src2->Data()),
					src2->WidthBytes(),
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAdd_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_add_operators
		{
			static_assert((std::is_same<T, CAdd8u1c>::value 
				|| std::is_same<T, CAdd16u1c>::value 
				|| std::is_same<T, CAdd32f1c>::value), 
				"The template parameter is not an add operator!");
		};

		/// CImageAdd
		/// Operator:
		/// Add(A, B) = > A = A + B;
		/// Add(A, B, C) = > A = B + C;
		///
		/// Support image format :
		/// CImage8u1cIPPI
	    /// CImage16u1cIPPI
	    /// CImage32f1cIPPI
		template<class Operator>
		class CImageAdd : private Operator, is_add_operators<Operator>
		{
		public:
// 			template<typename T>
// 			static void Add(T &srcdst, T const &src)
// 			{
// 				Operator::Add(srcdst, src);
// 			};

			template<typename T>
			static void Add(T&& srcdst, T&& src)
			{
				Operator::Add(std::forward<T>(srcdst), std::forward<T>(src));
			};

			template<typename T>
			static void Add(T&& dst, T&& src1, T&& src2)
			{				
				Operator::Add(std::forward<T>(dst), std::forward<T>(src1), std::forward<T>(src2));
			};
		};		
	}
}


#endif

