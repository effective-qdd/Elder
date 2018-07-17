/**
* \file File.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.20
*/
#ifndef _FILE_H
#define _FILE_H


// System Class Includes


// My Class Includes
#include "FileBase.hpp"
#include "Tif.hpp"

namespace ELDER
{
	namespace FILE
	{
		/// \brief Template class.
		
		class CFile
		{
		public:
			CFile() = default;

			~CFile() = default;

			template<typename T>
			static void Write(const std::string &filePath, std::any anyImage) noexcept(false)
			{
				T m_file;
				m_file.Write(filePath, anyImage);
			}
		};

	}
}

#endif