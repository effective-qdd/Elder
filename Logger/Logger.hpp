/**
* \file Logger.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.03.28
*/
#ifndef _LOGGER_H
#define _LOGGER_H


// System Class Includes
#include <string>
#include <mutex>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <shlobj.h>

// My Class Includes
#include "../Singleton/Singleton.hpp"


namespace ELDER
{
	/// \brief CLogger
	class CLogger : public CNonCopyable
	{
	public:
		const char *kLogFileBasePath = "D:\\Elder\\";

		CLogger(void)
		{
			//SHCreateDirectoryExA(NULL, "D:\\Elder\\", NULL);
			//auto ret = SHCreateDirectoryExA(NULL, "D:\\Elder\\Logs\\", NULL);
			if (!FolderExist(kLogFileBasePath))
			{
				CreateFolder(kLogFileBasePath);
			}
			std::stringstream fileName;
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);
			fileName
				<< kLogFileBasePath
				<< sysTime.wYear
				<< '-'
				<< sysTime.wMonth
				<< '-'
				<< sysTime.wDay
				<< '-'
				<< sysTime.wHour
				<< '-'
				<< sysTime.wMinute
				<< '-'
				<< sysTime.wSecond
				<< ".log";
			if (m_logFileStream.is_open())
			{
				m_logFileStream.close();
			}
			m_logFileStream.open(fileName.str());
		}


		~CLogger(void)
		{
			m_logFileStream.close();
		}

		
		std::ofstream &GetLogFileStream()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			std::stringstream time;
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);
			time
				<< sysTime.wYear
				<< '-'
				<< sysTime.wMonth
				<< '-'
				<< sysTime.wDay
				<< ' '
				<< std::setw(2)
				<< sysTime.wHour
				<< ':'
				<< std::setw(2)
				<< sysTime.wMinute
				<< ':'
				<< std::setw(2)
				<< sysTime.wSecond
				<< '.'
				<< std::setw(3)
				<< sysTime.wMilliseconds;
			m_logFileStream << '[' << time.str() << ']' << '\t';

			return m_logFileStream;
		}
	
	private:
		bool FolderExist(std::string strPath)
		{
			WIN32_FIND_DATAA wfd;
			BOOL bValue = FALSE;
			HANDLE hFind = FindFirstFileA(strPath.c_str(), &wfd);
			if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				bValue = TRUE;
			}
			FindClose(hFind);
			return bValue;
		}

		bool CreateFolder(std::string strPath)
		{
			SECURITY_ATTRIBUTES attrib;
			attrib.bInheritHandle = FALSE;
			attrib.lpSecurityDescriptor = NULL;
			attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
			return CreateDirectoryA(strPath.c_str(), &attrib);
			//	return ::CreateDirectory(strPath,NULL);
		}
	private:
		//static CLogger *m_instance;
		std::ofstream m_logFileStream;
		std::mutex m_mutex;
	};


	// Global Defines
#define LOG ELDER::CSingleton<ELDER::CLogger>::GetInstance()->GetLogFileStream()


#define LOG_INFO(info) ELDER::CSingleton<ELDER::CLogger>::GetInstance()->GetLogFileStream() \
		<< "[INFO]" << '\t' \
		<< "[TID:" << ' ' << std::this_thread::get_id() << ']' << '\t' \
		<< '[' << __FUNCTION__ << ' ' << '@' << ' ' << __FILE__ << ' '	<< __LINE__ << ']' << '\t' \
		<< info \
		<< std::endl;


#define LOG_INFO_VALUE(info, value) ELDER::CSingleton<ELDER::CLogger>::GetInstance()->GetLogFileStream() \
		<< "[INFO]" << '\t' \
		<< "[TID:" << ' ' << std::this_thread::get_id() << ']' << '\t' \
		<< '[' << __FUNCTION__ << ' ' << '@' << ' ' << __FILE__ << ' '	<< __LINE__ << ']' << '\t' \
		<< info \
		<< ' ' \
		<< value \
		<< std::endl;


#define LOG_WARNING(warning) ELDER::CSingleton<ELDER::CLogger>::GetInstance()->GetLogFileStream() \
		<< "[WARNING]" << '\t' \
		<< "[TID:" << ' ' << std::this_thread::get_id() << ']' << '\t' \
		<< '[' << __FUNCTION__ << ' ' << '@' << ' ' << __FILE__ << ' '	<< __LINE__ << ']' << '\t' \
		<< warning \
		<< std::endl;


#define LOG_ERROR(error) ELDER::CSingleton<ELDER::CLogger>::GetInstance()->GetLogFileStream() \
		<< "[ERROR]" << '\t' \
		<< "[TID:" << ' ' << std::this_thread::get_id() << ']' << '\t' \
		<< '[' << __FUNCTION__ << ' ' << '@' << ' ' << __FILE__ << ' '	<< __LINE__ << ']' << '\t' \
		<< error \
		<< std::endl;


#define LOG_ERROR_VALUE(error, value) ELDER::CSingleton<ELDER::CLogger>::GetInstance()->GetLogFileStream() \
		<< "[ERROR]" << '\t' \
		<< "[TID:" << ' ' << std::this_thread::get_id() << ']' << '\t' \
		<< '[' << __FUNCTION__ << ' ' << '@' << ' ' << __FILE__ << ' '	<< __LINE__ << ']' << '\t' \
		<< error \
		<< ' ' \
		<< value \
		<< std::endl;


#ifdef _DEBUG
#define ASSERT_LOG(cond, log) if(!(cond)) { LOG_ERROR(log); std::abort(); }
#else
#define ASSERT_LOG(cond, log) ((void)0)
#endif
}


#endif