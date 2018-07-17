/**
* \file Stack.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.20
*/
#ifndef _STACK_H
#define _STACK_H


// System Class Includes


// My Class Includes
#include "FileBase.hpp"


namespace ELDER
{
	namespace FILE
	{
		/// \brief CStackReader class.
		class CStackReader : public IFileReader
		{
		public:
			CStackReader() = default;

			virtual ~CStackReader() override = default;

			//virtual FileInfo Open(const std::string &) {};

			virtual void Read(std::any, unsigned long) {};

			//virtual void Close() {};
		};


		/// \brief CStackWriter class.
		class CStackWriter : public IFileWriter
		{
		public:
			CStackWriter() = default;

			virtual ~CStackWriter() override = default;

			virtual void Create(const FileInfo &) {};

			virtual void Write(std::any, unsigned long) {};

			virtual void Close() {};
		};
	}
}

#endif