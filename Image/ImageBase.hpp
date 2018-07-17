/**
* \file ImageBase.hpp
* \brief This is a base class for all image. Declare interface with
* pure virtual function.
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.07
*/
#ifndef _IMAGE_BASE_H
#define _IMAGE_BASE_H


// System Class Includes
#include <type_traits>


// My Class Includes
#include "../Logger/Logger.hpp"
#include "../Exception/Exception.hpp"
#include "../NonCopyable/NonCopyable.hpp"


namespace ELDER
{
	/// \brief CImageChannel
	class CImageChannel : public CNonCopyable
	{
	public:
		CImageChannel() = default;

		virtual ~CImageChannel() override = default;
	};


	/// \brief CICH1 class.
	class CICH1 final : public CImageChannel
	{
	public:
		CICH1() = default;

		virtual ~CICH1() override = default;

		static const int CH = 1;
	};


	/// \brief CICH3 class.
	class CICH3 final : public CImageChannel
	{
	public:
		CICH3() = default;

		virtual ~CICH3() override = default;

		static const int CH = 3;
	};


	/// \brief CICH4 class.
	class CICH4 final : public CImageChannel
	{
	public:
		CICH4() = default;

		virtual ~CICH4() override = default;

		static const int CH = 4;
	};

	template<class T>
	struct is_image_channel_types
	{
		static_assert((std::is_same<T, CICH1>::value || std::is_same<T, CICH3>::value || std::is_same<T, CICH4>::value), "The template parameter is not an image channel type!");
	};
	

	/// \brief CImageDataType class.
	class CImageDataType : public CNonCopyable
	{
	public:
		CImageDataType() = default;

		virtual ~CImageDataType() override = default;
	};


	/// \brief CIDT8U class.
	class CIDT8U final : public CImageDataType
	{
	public:
		CIDT8U() = default;

		~CIDT8U() override = default;

		static const int BitDepth = 8;
	};


	/// \brief CIDT16U class.
	class CIDT16U final : public CImageDataType
	{
	public:
		CIDT16U() = default;

		~CIDT16U() override = default;

		static const int BitDepth = 16;
	};


	/// \brief CIDT32F
	class CIDT32F final : public CImageDataType
	{
	public:
		CIDT32F() = default;

		~CIDT32F() override = default;

		static const int BitDepth = 32;
	};

	template<class T>
	struct is_image_data_types
	{
		static_assert((std::is_same<T, CIDT8U>::value || std::is_same<T, CIDT16U>::value || std::is_same<T, CIDT32F>::value), "The template parameter is not an image data type!");
	};


	/// \brief Template class CImageTratis.
	template<typename T>
	class CImageTratis : public CNonCopyable, is_image_data_types<T>
	{
	public:
		using value_type = typename T;
	};


	/// \brief Template class. Specialization template CIDT8U.
	template<>
	class CImageTratis<CIDT8U>
	{
	public:
		using value_type = typename unsigned char;
	};

	using IDT8U = CImageTratis<ELDER::CIDT8U>::value_type;


	/// \brief Template class. Specialization template CIDT16U.
	template<>
	class CImageTratis<CIDT16U>
	{
	public:
		using value_type = typename unsigned short;
	};

	using IDT16U = CImageTratis<ELDER::CIDT16U>::value_type;


	/// \brief Template class. Specialization template CIDT32F.
	template<>
	class CImageTratis<CIDT32F>
	{
	public:
		using value_type = typename float;
	};

	using IDT32F = CImageTratis<ELDER::CIDT32F>::value_type;


	/// \brief IImage interface class.
	template<typename T, typename C, typename Traits = CImageTratis<T>>
	class IImage : public CNonCopyable
	{
	public:
		IImage() : m_width(0), m_height(0), m_widthBytes(0), m_isInitialized(false) {};
		
		virtual ~IImage() override = default;

		typedef typename Traits::value_type Type;

		virtual void Initialize(int, int, Type const*) = 0;

		virtual Type* const Data(void) = 0;

		virtual int Width(void) const noexcept { return m_width; };

		virtual int Height(void) const noexcept  { return m_height; };

		virtual int WidthBytes(void) const noexcept { return m_widthBytes; };

	protected:
		int m_width;
		int m_height;
		int m_widthBytes;
		bool m_isInitialized;
	};
}


#endif
