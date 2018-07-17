/**
* \file ImageMorphologyBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.06.28
*/
#ifndef _ALGORITHM_MORPHOLOGY_BASE_H
#define _ALGORITHM_MORPHOLOGY_BASE_H

// My Class Includes
#include "ImageAlgorithmBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace MORPHOLOGY
		{
			class IMorphology : IAlgorithm<std::any const&, std::any const&>
			{
			public:
				IMorphology() : IAlgorithm() {};

				virtual ~IMorphology() override = default;

				virtual bool Apply(std::any const&, std::any const&) noexcept(false) { return true; };
			};
		}
	}
}

#endif