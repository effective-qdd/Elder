/**
* \file FileBase.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.20
*/
#ifndef _FILE_BASE_H
#define _FILE_BASE_H


// System Class Includes
#include <fstream>
#include <any>

// My Class Includes
#include "../Image/Image.hpp"

namespace ELDER
{
	namespace FILE
	{	
		/// \brief File interface class.
		class IFile : public CNonCopyable
		{
		public: 
			IFile() = default;

			virtual ~IFile() = default;
		};


		/// \brief File read interface class.
		class IFileReader : public IFile
		{
		public:
			IFileReader() = default;

			virtual ~IFileReader() override = default;

			virtual FileInfo Open(const std::string &) noexcept(false) = 0;

			virtual void Close() noexcept(false) = 0;
		};


		/// \brief File write interface class.
		class IFileWriter : public IFile
		{
		public:
			IFileWriter() = default;

			virtual ~IFileWriter() override = default;

// 			virtual void Create(const FileInfo &) = 0;
// 
// 			virtual void Write(CAny &&) = 0;
// 
// 			virtual void Close() = 0;
		};				
	}
}

#endif