/**
* \file Exception.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email dongdong.qain@bluejayimaging.com
* \version 1.0.0.0
* \date 2017.07.11
*/
#ifndef _EXCEPTION_H
#define _EXCEPTION_H


// System Class Includes
#include <exception>
#include <string>


namespace ELDER
{
	/// \class CException
	class CException : public std::exception
	{
	public:
		CException(void) :exception() {};


		explicit CException(const std::string &msg) : exception(msg.c_str()) {};


		CException &operator=(const CException &) = delete;


		virtual ~CException(void) = default;
	};

#define THROW_EC(ec)	\
	throw ec;

#define THROW_MSG(msg)	\
	throw ELDER::CException(msg);

#define ENSURE_THROW_EC(cond, ec)	\
	if(!(cond)) throw ec;

#define ENSURE_THROW_MSG(cond, msg)	\
	if(!(cond)) throw ELDER::CException(msg);
}


#endif