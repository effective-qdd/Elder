/**
* \file Singleton.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.04.19
*/
#ifndef _SINGLETON_H
#define _SINGLETON_H


// System Class Includes
#include <mutex>


// My Class Includes
#include "../NonCopyable/NonCopyable.hpp"


namespace ELDER
{
	/// \brief CSingleton
	template<typename T> class CSingleton : public CNonCopyable
	{
	public:
		static std::shared_ptr<T> GetInstance();

		template<typename... Args> static std::shared_ptr<T> GetInstance(Args... args);

	private:
		static std::shared_ptr<T> m_instance;

		static std::mutex m_mutex;
	};


	// Global Defines
	template<typename T> std::shared_ptr<T> CSingleton<T>::m_instance = nullptr;

	template<typename T> std::mutex CSingleton<T>::m_mutex;


	/// Public Interface
	template<typename T> std::shared_ptr<T> CSingleton<T>::GetInstance()
	{
		if (m_instance == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_instance == nullptr)
			{
				m_instance = std::make_shared<T>();
			}
		}
		return m_instance;
	}


	template<typename T> 
	template<typename... Args>
	std::shared_ptr<T> CSingleton<T>::GetInstance(Args... args)
	{
		if (m_instance == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_instance == nullptr)
			{
				m_instance = std::make_shared<T>(std::forward<Args>(args)...);
			}
		}
		return m_instance;
	}
}

#endif

