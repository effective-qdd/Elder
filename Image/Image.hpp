/**
* \file Image.hpp
* \brief This is the host class for image implementation policy class.
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.07
*/
#ifndef _IMAGE_H
#define _IMAGE_H


// My Class Includes
#include "../Structure/Structs.h"
#include "../Enumeration/Enums.h"
#include "../Definition/Definitions.h"
#include "ImageIPPI.hpp"


namespace ELDER
{
	/// \brief Template class CImage.
	///
	/// Generate images by specify template parameters
	/// [class T] image data type
	///				- CIDT8U
	///				- CIDT16U
	///				- CIDT32F
	///	[class C] image channel (CICH1, CICH3 and CICH4)
	///				- CICH1
	///				- CICH3
	///				- CICH4
	/// [class ImageImpPolicy] the template template parameter, image implementation policy class
	///							- CImageIPPI
	/// [class Traits] image traits, use the default template parameter CImageTratis
	template
	<
		class T, 
		class C, 
		template<typename, typename, typename> class ImageImpPolicy, 
		class Traits = CImageTratis<T>
	>
	class CImage
	{
	public:
		using Type = typename Traits::value_type;

		/// constructor
		CImage() : m_image() {};

		/// copy constructor
		CImage(CImage const& image)
		{
			Initialize(image.Width(), image.Height(), const_cast<CImage &>(image).Data());
		};

		/// copy assignment operator
		CImage &operator=(CImage const& image)
		{
			if (this != &image)
			{
				Initialize(image.Width(), image.Height(), const_cast<CImage &>(image).Data());
			}
			return *this;
		};

		/// destructor
		~CImage() = default;

		/// Initialize Image
		void Initialize(int w, int h,  Type const* d = nullptr) { m_image.Initialize(w, h, d); };

		/// Image Data. Data ptr is const. Data is not const.
		Type* const Data(void) { return m_image.Data(); };

		/// Image Width. CONST
		int Width(void) const noexcept  { return m_image.Width(); };

		/// Image Height. CONST
		int Height(void) const noexcept { return m_image.Height(); };

		/// Image Bit Depth. CONST
		int BitDepth() const noexcept { return T::BitDepth; };

		/// Image Channel. CONST
		int Channel() const noexcept { return C::CH; };

		/// Image Width in bytes. CONST
		int WidthBytes(void) const noexcept  { return m_image.WidthBytes(); };

		/// Image data in bytes. CONST
		int TotalBytes(void) const noexcept { return m_image.WidthBytes() * m_image.Height(); };

	private:
		/// Define the implemented image object
		ImageImpPolicy<T, C, CImageTratis<T>> m_image;
	};

	//----------------------------------------------------------------------------
	// An Alias Template For IPPI Images
	//----------------------------------------------------------------------------
	/// Define CImage<CIDT8U, CICH1, CImageIPPI> as CImage8u1cIPPI
	using CImage8u1cIPPI = CImage<CIDT8U, CICH1, CImageIPPI>;
	
	/// Define CImage<CIDT16U, CICH1, CImageIPPI> as CImage16u1cIPPI
	using CImage16u1cIPPI = CImage<CIDT16U, CICH1, CImageIPPI>;
	
	/// Define CImage<CIDT32F, CICH1, CImageIPPI> as CImage32f1cIPPI
	using CImage32f1cIPPI = CImage<CIDT32F, CICH1, CImageIPPI>;

	//----------------------------------------------------------------------------
	// Image Types Enable IF Defines
	//----------------------------------------------------------------------------
	/// Enable if image type is CImage8u1cIPPI
	template<typename T>
	using EnableIfCImage8u1cIPPI = std::enable_if_t<std::is_same_v<T, CImage8u1cIPPI>>;

	/// Enable if image type is CImage16u1cIPPI
	template<typename T>
	using EnableIfCImage16u1cIPPI = std::enable_if_t<std::is_same_v<T, CImage16u1cIPPI>>;
	
	/// Enable if image type is CImage32f1cIPPI
	template<typename T>
	using EnableIfCImage32f1cIPPI = std::enable_if_t<std::is_same_v<T, CImage32f1cIPPI>>;

}


#endif
