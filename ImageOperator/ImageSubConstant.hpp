/**
* \file ImageSubConstant.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_SUB_CONSTANT_H
#define _IMAGE_SUB_CONSTANT_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CSubConstant8u1c
		class CSubConstant8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SubConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SubConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_8u_C1IRSfs
				(
					value, 
					reinterpret_cast<Ipp8u*>(srcdst->Data()), 
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SubConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_8u_C1IRSfs
				(
					value, 
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SubConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiSubC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T &>(src).Data()),
					src.WidthBytes(), 
					value, 
					reinterpret_cast<Ipp8u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SubConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiSubC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(), 
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void SubConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiSubC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					value, 
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_8u_C1RSfs failed!");
			}
		};


		/// \brief CSubConstant16u1c
		class CSubConstant16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SubConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst.Data()), 
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SubConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()), 
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SubConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()), 
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SubConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiSubC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T &>(src).Data()),
					src.WidthBytes(), 
					value,
					reinterpret_cast<Ipp16u*>(dst.Data()), 
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SubConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiSubC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(),
					value, 
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void SubConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiSubC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(), 
					value,
					reinterpret_cast<Ipp16u*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_16u_C1RSfs failed!");
			}
		};


		/// \brief CSubConstant32f1c
		class CSubConstant32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SubConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst.Data()), 
					srcdst.WidthBytes(), 
					{ srcdst.Width(), srcdst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SubConstant(T* const srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst->Data()), 
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SubConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				IppStatus status = ippiSubC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst->Data()), 
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SubConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiSubC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SubConstant(T* const dst, T const* const src, typename T::Type value)
			{
				IppStatus status = ippiSubC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()),
					src->WidthBytes(), 
					value, 
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void SubConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				IppStatus status = ippiSubC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()), 
					src->WidthBytes(),
					value, 
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiSubC_32f_C1R failed!");
			}
		};


		template<class T>
		struct is_sub_constant_operators
		{
			static_assert((std::is_same<T, CSubConstant8u1c>::value
				|| std::is_same<T, CSubConstant16u1c>::value
				|| std::is_same<T, CSubConstant32f1c>::value),
				"The template parameter is not an sub constant operator!");
		};


		/// CImageSubConstant
		/// SubConstant(A, V) => A = A - V;
		template<class Operator>
		class CImageSubConstant : private Operator, is_sub_constant_operators<Operator>
		{
		public:
			template<typename T>
			static void SubConstant(T& srcdst, typename T::Type value)
			{
				Operator::SubConstant(srcdst, value);
			};


			template<typename T>
			static void SubConstant(T* const srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "image ptr is null!");
				Operator::SubConstant(srcdst, value);
			};


			template<typename T>
			static void SubConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "image ptr is null!");
				Operator::SubConstant(srcdst, value);
			};


			template<typename T>
			static void SubConstant(T& dst, T const &src, typename T::Type value)
			{
				ASSERT_LOG(dst.Width() == src.Width(), "dst width != src width!");
				ASSERT_LOG(dst.Height() == src.Height(), "dst height != src height!");
				Operator::SubConstant(dst, src, value);
			};


			template<typename T>
			static void SubConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "image ptr is null!");
				ASSERT_LOG(src != nullptr, "image ptr is null!");
				ASSERT_LOG(dst->Width() == src->Width(), "dst width != src width!");
				ASSERT_LOG(dst->Height() == src->Height(), "dst height != src height!");
				Operator::SubConstant(dst, src, value);
			};


			template<typename T>
			static void SubConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "image ptr is null!");
				ASSERT_LOG(src != nullptr, "image ptr is null!");
				ASSERT_LOG(dst->Width() == src->Width(), "dst width != src width!");
				ASSERT_LOG(dst->Height() == src->Height(), "dst height != src height!");
				Operator::SubConstant(dst, src, value);
			};
		};
	}
}


#endif
 