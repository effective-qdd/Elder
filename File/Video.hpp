/**
* \file CameraGS2020.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.20
*/
#ifndef _VIDEO_H
#define _VIDEO_H


// System Class Includes


// My Class Includes
#include "FileBase.hpp"


namespace ELDER
{
	namespace FILE
	{
		/// \brief CVideoReader class.
// 		class CVideoReader : public IFileReader
// 		{
// 		public:
// 			CVideoReader() = default;
// 
// 			virtual ~CVideoReader() override = default;
// 
// 			virtual void Open(FileInfo &) override {};
// 
// 			virtual void Read(CAny &&, unsigned long) override {};
// 
// 			virtual void Close() override {};
// 
// 		private:
// 			virtual void Read(CAny &&) override {};
// 		};


		/// \brief CVideoWriter class.
		class CVideoWriter : public IFileWriter
		{
		public:
			CVideoWriter() = default;

			virtual ~CVideoWriter() override = default;

			virtual void Create(const std::string &, const VideoInfo &) {};

			virtual void Write(CAny) {};

			virtual void Close() {};
		};
	}
}

#endif