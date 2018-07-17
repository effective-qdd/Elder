/**
* \file ImageTransformBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.22
*/
#ifndef _ALGORITHM_TRANSFORM_BASE_H
#define _ALGORITHM_TRANSFORM_BASE_H


// My Class Includes
#include "ImageAlgorithmBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace TRANSFORM
		{
			class ITransform : IAlgorithm<std::any const&, std::any const&, ImageInfo&>
			{
			public:
				ITransform() : IAlgorithm() {};

				virtual ~ITransform() override = default;

				virtual bool Apply(std::any const&, std::any const&, ImageInfo &) noexcept(false) { return true; };
			};
		}
	}
}


#endif