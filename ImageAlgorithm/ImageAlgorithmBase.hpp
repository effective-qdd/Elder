/**
* \file ImageAlgorithmBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.05
*/
#ifndef _ALGORITHM_BASE_H
#define _ALGORITHM_BASE_H

// System Class Includes
#include <list>
#include <mutex>
#include <any>

// My Class Includes
#include "../Image/Image.hpp"

namespace ELDER
{
	/// \brief About important algorithm on image.
	namespace ALGORITHM
	{
		/// \brief Algorithm interface class.
		template<typename... Args>
		class IAlgorithm : CNonCopyable
		{
		public:
			IAlgorithm() = default;

			virtual ~IAlgorithm() override = default;

			virtual bool Apply(Args... args) noexcept(false) = 0;
		};
	}
}


#endif