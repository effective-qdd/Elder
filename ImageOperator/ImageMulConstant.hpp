/**
* \file ImageMulConstant.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_MUL_CONSTANT_H
#define _IMAGE_MUL_CONSTANT_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CMulConstant8u1c
		class CMulConstant8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MulConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_8u_C1IRSfs
				(
					value, 
					reinterpret_cast<Ipp8u*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MulConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MulConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_8u_C1IRSfs
				(
					value, 
					reinterpret_cast<Ipp8u*>(srcdst->Data()), 
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MulConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiMulC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()), 
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MulConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiMulC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void MulConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiMulC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_8u_C1RSfs failed!");
			}
		};


		/// \brief CMulConstant16u1c
		class CMulConstant16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MulConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_16u_C1IRSfs
				(
					value, 
					reinterpret_cast<Ipp16u*>(srcdst.Data()), 
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MulConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()), 
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MulConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MulConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiMulC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()), 
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MulConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiMulC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void MulConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiMulC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(), 
					value,
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_16u_C1RSfs failed!");
			}
		};


		/// \brief CMulConstant32f1c
		class CMulConstant32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MulConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MulConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MulConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiMulC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst->Data()), 
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MulConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiMulC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MulConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiMulC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void MulConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiMulC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()), 
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiMulC_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_mul_constant_operators
		{
			static_assert((std::is_same<T, CMulConstant8u1c>::value
				|| std::is_same<T, CMulConstant16u1c>::value
				|| std::is_same<T, CMulConstant32f1c>::value),
				"The template parameter is not an mul constant operator!");
		};


		/// CImageMulConstant
		/// Mul(A, V) => A = A * V;
		/// Mul(A, B, V) => A = B * V;
		template<class Operator>
		class CImageMulConstant : private Operator, is_mul_constant_operators<Operator>
		{
		public:
			template<typename T>
			static void MulConstant(T& srcdst, typename T::Type value)
			{
				Operator::MulConstant(std::forward<T>(srcdst), value);
			};


			template<typename T>
			static void MulConstant(T* const srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "image ptr is null!");
				Operator::MulConstant(srcdst, value);
			};


			template<typename T>
			static void MulConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "image ptr is null!");
				Operator::MulConstant(srcdst, value);
			};


			template<typename T>
			static void MulConstant(T& dst, T const& src, typename T::Type value)
			{
				ASSERT_LOG(dst.Width() == src.Width(), "dst width != src width!");
				ASSERT_LOG(dst.Height() == src.Height(), "dst height != src height!");
				Operator::MulConstant(dst, src, value);
			};


			template<typename T>
			static void MulConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "image ptr is null!");
				ASSERT_LOG(src != nullptr, "image ptr is null!");
				ASSERT_LOG(dst->Width() == src->Width(), "dst width != src width!");
				ASSERT_LOG(dst->Height() == src->Height(), "dst height != src height!");
				Operator::MulConstant(dst, src, value);
			};


			template<typename T>
			static void MulConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "image ptr is null!");
				ASSERT_LOG(src != nullptr, "image ptr is null!");
				ASSERT_LOG(dst->Width() == src->Width(), "dst width != src width!");
				ASSERT_LOG(dst->Height() == src->Height(), "dst height != src height!");
				Operator::MulConstant(dst, src, value);
			};
		};
	}
}


#endif
