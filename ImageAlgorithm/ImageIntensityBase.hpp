/**
* \file ImageIntensityBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.22
*/
#ifndef _ALGORITHM_INTENSITY_BASE_H
#define _ALGORITHM_INTENSITY_BASE_H


// My Class Includes
#include "ImageAlgorithmBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace INTENSITY
		{
			class IIntensity : IAlgorithm<std::any const&, std::any const&>
			{
			public:
				IIntensity() : IAlgorithm() {};

				virtual ~IIntensity() override = default;

				virtual bool Apply(std::any const&, std::any const&) noexcept(false) { return true; };
			};
		}
	}
}


#endif