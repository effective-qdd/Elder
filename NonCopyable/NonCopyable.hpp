/**
* \file NonCopyable.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.28
*/
#ifndef _NON_COPYABLE_H
#define _NON_COPYABLE_H


namespace ELDER
{
	/// \brief CNonCopyable
	class CNonCopyable
	{
	protected:
		CNonCopyable() = default;

		CNonCopyable(const CNonCopyable &) = delete;

		CNonCopyable &operator=(const CNonCopyable &) = delete;

		virtual ~CNonCopyable() = default;
	};
}

#endif

