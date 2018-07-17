/**
* \file ImageFilterBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.05.22
*/
#ifndef _ALGORITHM_FILTER_BASE_H
#define _ALGORITHM_FILTER_BASE_H


// My Class Includes
#include "ImageAlgorithmBase.hpp"

namespace ELDER
{
	namespace ALGORITHM
	{
		namespace FILTER
		{
			class IFilter : IAlgorithm<std::any const&, std::any const&>
			{
			public:
				IFilter() : IAlgorithm() {};

				virtual ~IFilter() override = default;

				virtual bool Apply(std::any const&, std::any const&) noexcept(false) { return true; };
			};
		}
	}
}


#endif