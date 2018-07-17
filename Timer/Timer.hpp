/**
* \file Timer.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.03.28
*/
#ifndef _TIMER_H
#define _TIMER_H


// System Class Includes
#include <thread>


// My Class Includes
#include "../NonCopyable/NonCopyable.hpp"


namespace ELDER
{
	/// \brief CTimer
	class CTimer : public CNonCopyable
	{
	public:
		CTimer() : m_begin(std::chrono::high_resolution_clock::now()) {};

		/// Always call start before elapsed 
		void Start()
		{
			m_begin = std::chrono::high_resolution_clock::now();
		}

		/// Seconds
		long long ElapsedSecs()
		{
			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}

		/// Milliseconds
		long long ElapsedMsecs()
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}

		/// Microseconds
		long long ElapsedUsecs()
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}

		/// Nanoseconds
		long long ElapsedNsecs()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
		}


	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
	};
}

#endif
