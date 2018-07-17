/**
* \file ImageCorrectionBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.22
*/
#ifndef _ALGORITHM_CORRECTION_BASE_H
#define _ALGORITHM_CORRECTION_BASE_H


// My Class Includes
#include "ImageAlgorithmBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace CORRECTION
		{
			class ICorrection : IAlgorithm<std::any const&, std::any const&>
			{
			public:
				ICorrection() : IAlgorithm() {};

				virtual ~ICorrection() override = default;

				virtual bool Apply(std::any const&, std::any const&) noexcept(false) { return true; };
			};
		}
	}
}


#endif