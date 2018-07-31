/**
* \file ImageIPPI.hpp
* \brief This is a image implementation policy class with Intel IPPI.
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.07
*/
#ifndef _IMAGE_IPP_H
#define _IMAGE_IPP_H

// Links
#pragma comment(lib, "ippsmt.lib")
#pragma comment(lib, "ippvmmt.lib")
#pragma comment(lib, "ippcoremt.lib")
#pragma comment(lib, "ippimt.lib")
#pragma comment(lib, "ippcvmt.lib")

// System Class Includes
#include <ipp.h>

// My Class Includes
#include "ImageBase.hpp"

namespace ELDER
{
	/// \brief CImageIPPI primary template.
	template<typename T, typename C, typename Traits = CImageTratis<T>>
	class CImageIPPI final : public IImage<T, C>, is_image_data_types<T>, is_image_channel_types<C>
	{
	public:
		typedef typename Traits::value_type Type;

		CImageIPPI() : IImage<T, C>() {};
		
		~CImageIPPI() = default;

		void Initialize(int, int, Type const*) {};

		Type* const Data(void) {};

		int Width(void) const {};

		int Height(void) const {};

		int WidthBytes(void) const {};
	};


	/// \brief CImageIPPI full specialization template. 8 bit channel=1.
	template<>
	class CImageIPPI<CIDT8U, CICH1> : public IImage<CIDT8U, CICH1>
	{
	public:
		using Type = typename CImageTratis<CIDT8U>::value_type;


		CImageIPPI() :IImage<CIDT8U, CICH1>(), m_rawData(nullptr) {};
		

		~CImageIPPI()
		{
			Clear();
		};


		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");

			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_8u_C1(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_8u_C1 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(m_rawData, m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_8u_C1R(d, w * sizeof(Type), m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}


	private:
		Ipp8u* m_rawData;
	};


	/// \brief CImageIPPI full specialization template. 8 bit channel=3.
	template<>
	class CImageIPPI<CIDT8U, CICH3> : public IImage<CIDT8U, CICH3>
	{
	public:
		using Type = typename CImageTratis<CIDT8U>::value_type;


		CImageIPPI() :IImage<CIDT8U, CICH3>(), m_rawData(nullptr) {};


		~CImageIPPI()
		{
			Clear();
		};

		
		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");

			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_8u_C3(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_8u_C3 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(m_rawData, m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_8u_C1R(d, w * sizeof(Type) * 3, m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}

	private:
		Ipp8u* m_rawData;
	};


	/// \brief CImageIPPI full specialization template. 8 bit channel=4.
	template<>
	class CImageIPPI<CIDT8U, CICH4> : public IImage<CIDT8U, CICH4>
	{
	public:
		using Type = typename CImageTratis<CIDT8U>::value_type;


		CImageIPPI() :IImage<CIDT8U, CICH4>(), m_rawData(nullptr) {};


		~CImageIPPI()
		{
			Clear();
		};
		

		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");

			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_8u_AC4(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_8u_AC4 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(m_rawData, m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_8u_C1R(d, w * sizeof(Type) * 4, m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}


	private:
		Ipp8u* m_rawData;
	};


	/// \brief CImageIPPI full specialization template. 16 bit channel=1.
	template<>
	class CImageIPPI<CIDT16U, CICH1> : public IImage<CIDT16U, CICH1>
	{
	public:
		using Type = typename CImageTratis<CIDT16U>::value_type;


		CImageIPPI() :IImage<CIDT16U, CICH1>(), m_rawData(nullptr) {};
		

		~CImageIPPI()
		{
			Clear();
		};

		
		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");

			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_16u_C1(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_16u_C1 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(reinterpret_cast<Ipp8u *>(m_rawData), m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_16u_C1R(d, w * sizeof(Type), m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}

	private:
		Ipp16u* m_rawData;
	};


	/// \brief CImageIPPI full specialization template. 16 bit channel=3.
	template<>
	class CImageIPPI<CIDT16U, CICH3> : public IImage<CIDT16U, CICH3>
	{
	public:
		using Type = typename CImageTratis<CIDT16U>::value_type;


		CImageIPPI() :IImage<CIDT16U, CICH3>(), m_rawData(nullptr) {};


		~CImageIPPI()
		{
			Clear();
		};

		
		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");
		
			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_16u_C3(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_16u_C3 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(reinterpret_cast<Ipp8u *>(m_rawData), m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_16u_C1R(d, w * sizeof(Type) * 3, m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}

	private:
		Ipp16u* m_rawData;
	};


	/// \brief CImageIPPI full specialization template. 16 bit channel=4.
	template<>
	class CImageIPPI<CIDT16U, CICH4> : public IImage<CIDT16U, CICH4>
	{
	public:
		using Type = typename CImageTratis<CIDT16U>::value_type;


		CImageIPPI() :IImage<CIDT16U, CICH4>(), m_rawData(nullptr) {};


		~CImageIPPI()
		{
			Clear();
		};

		
		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");
		
			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_16u_C4(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_16u_C4 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(reinterpret_cast<Ipp8u *>(m_rawData), m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_16u_C1R(d, w * sizeof(Type) * 4, m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}

	private:
		Ipp16u* m_rawData;
	};


	/// \brief CImageIPPI full specialization template. 32 bit float channel=1.
	template<>
	class CImageIPPI<CIDT32F, CICH1> : public IImage<CIDT32F, CICH1>
	{
	public:
		using Type = typename CImageTratis<CIDT32F>::value_type;


		CImageIPPI() :IImage<CIDT32F, CICH1>(), m_rawData(nullptr) {};
		

		~CImageIPPI()
		{
			Clear();
		};


		void Initialize(int w, int h, Type const* d)
		{
			ASSERT_LOG(w >= 64, "Image width must > 64");
			
			if (!m_isInitialized || (w != m_width) || (h != m_height))
			{
				Clear();
				m_rawData = ippiMalloc_32f_C1(w, h, &m_widthBytes);
				ENSURE_THROW_MSG(m_rawData != nullptr, "ippiMalloc_32f_C1 failed!");
				m_width = w;
				m_height = h;
			}
			
			if (d == nullptr)
			{
				IppStatus status = ippsZero_8u(reinterpret_cast<Ipp8u *>(m_rawData), m_widthBytes * h);
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippsZero_8u failed!");
			}
			else
			{
				IppStatus status = ippiCopy_32f_C1R(d, w * sizeof(Type), m_rawData, m_widthBytes, IppiSize{ w, h });
				ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
			}
			m_isInitialized = true;
		};


		Type* const Data(void)
		{
			ASSERT_LOG(m_rawData != nullptr, "m_rawData ptr is null!");
			return m_rawData;
		}


	private:
		void Clear()
		{
			if (m_rawData != nullptr)
			{
				ippFree(m_rawData);
				m_rawData = nullptr;
			}
		}

	private:
		Ipp32f* m_rawData;
	};
}

#endif
