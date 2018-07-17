/**
* \file Picture.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.20
*/
#ifndef _PICTURE_H
#define _PICTURE_H


// System Class Includes


// My Class Includes
#include "FileBase.hpp"


namespace ELDER
{
	namespace FILE
	{
		/// \brief Picture reader class.
		class CPictureReader : public IFileReader
		{
		public:
			CPictureReader() : IFileReader() {};

			virtual ~CPictureReader() override = default;

			virtual void Read(std::any) noexcept(false) {};
		};


		/// \brief Picture writer class.
		class CPictureWriter : public IFileWriter
		{
		public:
			CPictureWriter() : IFileWriter() {}

			virtual ~CPictureWriter() override = default;

			virtual void Write(const std::string &, std::any) noexcept(false) {};
		};
	}
}

#endif