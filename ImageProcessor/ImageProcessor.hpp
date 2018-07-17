/**
* \file ImageProcessor.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.03.03
*/
#ifndef _IMAGE_PROCESSOR_H
#define _IMAGE_PROCESSOR_H

#include <any>

// My Class Includes
#include "../Image/Image.hpp"

namespace ELDER
{
	/// \brief CImageProcessor
	class CImageProcessor : public CNonCopyable
	{
	public:
		CImageProcessor(std::function<bool(std::any const&, std::any const&, ImageInfo& outImageInfo)>&& processor)
			: m_processor(std::forward<decltype(processor)>(processor)) {};

		~CImageProcessor() = default;

		/// outImageInfo is ref. not const ref!
		bool Apply(std::any const& imageIn, std::any const& imageOut, ImageInfo& outImageInfo)
		{
			return m_processor(std::move(imageIn), std::move(imageOut), outImageInfo);
		}

	private:
		std::function<bool(std::any const&, std::any const&, ImageInfo&)> m_processor;
	};
}


#endif
