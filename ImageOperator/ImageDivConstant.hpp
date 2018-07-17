/**
* \file ImageDivConstant.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_DIV_CONSTANT_H
#define _IMAGE_DIV_CONSTANT_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CDivConstant8u1c
		class CDivConstant8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void DivConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void DivConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void DivConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void DivConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiDivC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T &>(src).Data()),
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void DivConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiDivC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T *>(src)->Data()), 
					src->WidthBytes(), 
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_8u_C1RSfs failed!");
			}

			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void DivConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiDivC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()), 
					src->WidthBytes(), 
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_8u_C1RSfs failed!");
			}
		};


		/// \brief CDivConstant16u1c
		class CDivConstant16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void DivConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void DivConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void DivConstant(std::shared_ptr<T> const &srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void DivConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiDivC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp16u*>(dst.Data()), 
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void DivConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiDivC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T *>(src)->Data()), 
					src->WidthBytes(), 
					value, 
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void DivConstant(std::shared_ptr<T> const &dst, std::shared_ptr<T> const &src, typename T::Type value)
			{
				IppStatus status = ippiDivC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()), 
					src->WidthBytes(),
					value, 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_16u_C1RSfs failed!");
			}
		};


		/// \brief CDivConstant32f1c
		class CDivConstant32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void DivConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_32f_C1IR
				(
					value, 
					reinterpret_cast<Ipp32f*>(srcdst.Data()), 
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void DivConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_32f_C1IR
				(
					value, 
					reinterpret_cast<Ipp32f*>(srcdst->Data()), 
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void DivConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiDivC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst->Data()), 
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void DivConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiDivC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T &>(src).Data()),
					src.WidthBytes(), 
					value,
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void DivConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiDivC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T *>(src)->Data()),
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void DivConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiDivC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()), 
					src->WidthBytes(), 
					value, 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiDivC_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_div_constant_operators
		{
			static_assert((std::is_same<T, CDivConstant8u1c>::value
				|| std::is_same<T, CDivConstant16u1c>::value
				|| std::is_same<T, CDivConstant32f1c>::value),
				"The template parameter is not an div constant operator!");
		};


		/// CImageDivConstant
		/// DivConstant(A, V) => A = A / V;
		/// DivConstant(A, B, V) => A = B / V;
		template<class Operator>
		class CImageDivConstant : private Operator, is_div_constant_operators<Operator>
		{
		public:
			template<typename T>
			static void DivConstant(T& srcdst, typename T::Type value)
			{
				ASSERT_LOG(value != 0, "value is 0");
				Operator::DivConstant(srcdst, value);
			};


			template<typename T>
			static void DivConstant(T* const srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "image ptr is null!");
				ASSERT_LOG(value != 0, "value is 0");
				Operator::DivConstant(srcdst, value);
			};


			template<typename T>
			static void DivConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "image ptr is null!");
				ASSERT_LOG(value != 0, "value is 0");
				Operator::DivConstant(srcdst, value);
			};


			template<typename T>
			static void DivConstant(T& dst, T const& src, typename T::Type value)
			{
				ASSERT_LOG(dst.Width() == src.Width(), "dst width != src width!");
				ASSERT_LOG(dst.Height() == src.Height(), "dst height != src height!");
				ASSERT_LOG(value != 0, "value is 0");
				Operator::DivConstant(dst, src, value);
			};


			template<typename T>
			static void DivConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "image ptr is null!");
				ASSERT_LOG(src != nullptr, "image ptr is null!");
				ASSERT_LOG(dst->Width() == src->Width(), "dst width != src width!");
				ASSERT_LOG(dst->Height() == src->Height(), "dst height != src height!");
				ASSERT_LOG(value != 0, "value is 0");
				Operator::DivConstant(dst, src, value);
			};


			template<typename T>
			static void DivConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ENSURE_THROW_MSG(dst != nullptr, "image ptr is null!");
				ENSURE_THROW_MSG(src != nullptr, "image ptr is null!");
				ENSURE_THROW_MSG(dst->Width() == src->Width(), "dst width != src width!");
				ENSURE_THROW_MSG(dst->Height() == src->Height(), "dst height != src height!");
				ASSERT_LOG(value != 0, "value is 0");
				Operator::DivConstant(dst, src, value);
			};
		};
	}
}


#endif
