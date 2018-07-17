/**
* \file ImageAddConstant.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.09
*/
#ifndef _IMAGE_ADD_CONSTANT_H
#define _IMAGE_ADD_CONSTANT_H


// My Class Includes
#include "../Image/Image.hpp"


namespace ELDER
{
	namespace OPERATOR
	{
		/// \brief CAddConstant8u1c
		class CAddConstant8u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void AddConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiAddC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst.Data()),
					srcdst.WidthBytes(), 
					{ srcdst.Width(), srcdst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void AddConstant(T* const srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				IppStatus status = ippiAddC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_8u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void AddConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				IppStatus status = ippiAddC_8u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp8u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_8u_C1IRSfs failed!");
			}

			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void AddConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiAddC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T&>(src).Data()), 
					src.WidthBytes(), 
					value, 
					reinterpret_cast<Ipp8u*>(dst.Data()),
					dst.WidthBytes(),
					{ dst.Width(), dst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void AddConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiAddC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_8u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage8u1cIPPI<T>>
			static void AddConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiAddC_8u_C1RSfs
				(
					reinterpret_cast<Ipp8u*>(src->Data()),
					src->WidthBytes(),
					value,
					reinterpret_cast<Ipp8u*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_8u_C1RSfs failed!");
			}
		};


		/// \brief CAddConstant16u1c
		class CAddConstant16u1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void AddConstant(T &srcdst, typename T::Type value)
			{
				IppStatus status = ippiAddC_16u_C1IRSfs
				(
					value, 
					reinterpret_cast<Ipp16u *>(srcdst.Data()),
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void AddConstant(T* const srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				IppStatus status = ippiAddC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void AddConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				IppStatus status = ippiAddC_16u_C1IRSfs
				(
					value,
					reinterpret_cast<Ipp16u*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_16u_C1IRSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void AddConstant(T& dst, T const& src, typename T::Type value)
			{				
				IppStatus status = ippiAddC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T&>(src).Data()),
					src.WidthBytes(), 
					value,
					reinterpret_cast<Ipp16u*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void AddConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiAddC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(const_cast<T *>(src)->Data()),
					src->WidthBytes(),
					value, 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }, 
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_16u_C1RSfs failed!");
			}


			template<class T, class = EnableIfCImage16u1cIPPI<T>>
			static void AddConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiAddC_16u_C1RSfs
				(
					reinterpret_cast<Ipp16u*>(src->Data()),
					src->WidthBytes(), 
					value, 
					reinterpret_cast<Ipp16u*>(dst->Data()), 
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() },
					0
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_16u_C1RSfs failed!");
			}
		};


		/// \brief CAddConstant32f1c
		class CAddConstant32f1c : public CNonCopyable
		{
		protected:
			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void AddConstant(T& srcdst, typename T::Type value)
			{
				IppStatus status = ippiAddC_32f_C1IR
				(
					value, 
					reinterpret_cast<Ipp32f*>(srcdst.Data()), 
					srcdst.WidthBytes(),
					{ srcdst.Width(), srcdst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void AddConstant(T* const srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				IppStatus status = ippiAddC_32f_C1IR
				(
					value, 
					reinterpret_cast<Ipp32f*>(srcdst->Data()),
					srcdst->WidthBytes(), 
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_32f_C1IR failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void AddConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ASSERT_LOG(srcdst != nullptr, "srcdst ptr is null!");
				IppStatus status = ippiAddC_32f_C1IR
				(
					value,
					reinterpret_cast<Ipp32f*>(srcdst->Data()),
					srcdst->WidthBytes(),
					{ srcdst->Width(), srcdst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void AddConstant(T& dst, T const& src, typename T::Type value)
			{
				IppStatus status = ippiAddC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T&>(src).Data()),
					src.WidthBytes(),
					value,
					reinterpret_cast<Ipp32f*>(dst.Data()),
					dst.WidthBytes(), 
					{ dst.Width(), dst.Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_32f_C1R failed!");
			}


			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void AddConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiAddC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(const_cast<T*>(src)->Data()), 
					src->WidthBytes(),
					value, 
					reinterpret_cast<Ipp32f*>(dst->Data()), 
					dst->WidthBytes(), 
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_32f_C1R failed!");
			}

			template<class T, class = EnableIfCImage32f1cIPPI<T>>
			static void AddConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ASSERT_LOG(dst != nullptr, "dst ptr is null!");
				ASSERT_LOG(src != nullptr, "src ptr is null!");
				IppStatus status = ippiAddC_32f_C1R
				(
					reinterpret_cast<Ipp32f*>(src->Data()),
					src->WidthBytes(), 
					value,
					reinterpret_cast<Ipp32f*>(dst->Data()),
					dst->WidthBytes(),
					{ dst->Width(), dst->Height() }
				);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiAddC_32f_C1R failed!");
			}
		};

		template<class T>
		struct is_add_constant_operators
		{
			static_assert((std::is_same<T, CAddConstant8u1c>::value
				|| std::is_same<T, CAddConstant16u1c>::value
				|| std::is_same<T, CAddConstant32f1c>::value),
				"The template parameter is not an add constant operator!");
		};

		/// CImageAddConstant
		/// Operator:
		/// AddConstant(A, v) => A = A + v;
		/// AddConstant(A, B, v) => A = B + v;
		///
		/// Support image format:
		/// CImage8u1cIPPI
		/// CImage16u1cIPPI
		/// CImage32f1cIPPI
		template<class Operator>
		class CImageAddConstant : private Operator, is_add_constant_operators<Operator>
		{
		public:
			template<typename T>
			static void AddConstant(T& srcdst, typename T::Type value)
			{
				Operator::AddConstant(srcdst, value);
			};


			template<typename T>
			static void AddConstant(T* const srcdst, typename T::Type value)
			{
				ENSURE_THROW_MSG(srcdst != nullptr, "image ptr is null!");
				Operator::AddConstant(srcdst, value);
			};


			template<typename T>
			static void AddConstant(std::shared_ptr<T> const& srcdst, typename T::Type value)
			{
				ENSURE_THROW_MSG(srcdst != nullptr, "image ptr is null!");
				Operator::AddConstant(srcdst, value);
			};


			template<typename T>
			static void AddConstant(T& dst, T const& src, typename T::Type value)
			{
				ENSURE_THROW_MSG(dst.Width() == src.Width(), "dst width != src width!");
				ENSURE_THROW_MSG(dst.Height() == src.Height(), "dst height != src height!");
				Operator::AddConstant(dst, src, value);
			};


			template<typename T>
			static void AddConstant(T* const dst, T const* const src, typename T::Type value)
			{
				ENSURE_THROW_MSG(dst != nullptr, "image ptr is null!");
				ENSURE_THROW_MSG(src != nullptr, "image ptr is null!");
				ENSURE_THROW_MSG(dst->Width() == src->Width(), "dst width != src width!");
				ENSURE_THROW_MSG(dst->Height() == src->Height(), "dst height != src height!");
				Operator::AddConstant(dst, src, value);
			};


			template<typename T>
			static void AddConstant(std::shared_ptr<T> const& dst, std::shared_ptr<T> const& src, typename T::Type value)
			{
				ENSURE_THROW_MSG(dst != nullptr, "image ptr is null!");
				ENSURE_THROW_MSG(src != nullptr, "image ptr is null!");
				ENSURE_THROW_MSG(dst->Width() == src->Width(), "dst width != src width!");
				ENSURE_THROW_MSG(dst->Height() == src->Height(), "dst height != src height!");
				Operator::AddConstant(dst, src, value);
			};
		};
	}
}


#endif