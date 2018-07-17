/**
* \file ImagePool.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.07
*/
#ifndef _IMAGE_POOP_H
#define _IMAGE_POOP_H


// System Class Includes
#include <functional>
#include <memory>
#include <queue>
#include <any>

// My Class Includes
#include "Image.hpp"

namespace ELDER
{
	/// \brief CImagePool
	template
	<
		typename T,
		typename std::enable_if
		<
		std::is_same<T, CImage8u1cIPPI>::value ||
		std::is_same<T, CImage16u1cIPPI>::value ||
		std::is_same<T, CImage32f1cIPPI>::value, int
		>::type = 0
	>
	class CImagePool : public CNonCopyable
	{
	public:
		using Deleter = std::function<void(T*)>;

		CImagePool()
			: m_capacity(0)
			, m_isInitialized(false)
		{}

		~CImagePool()
		{
			//m_imageQueue.swap(std::queue<std::unique_ptr<T>>());
			m_capacity = 0;
		} 

		void Initialize(int count, Size imageSize)
		{
			if (!m_isInitialized)
			{
				m_imageSize = imageSize;
				for (int i = 0; i < count; ++i)
				{
					std::unique_ptr<T> image(new T());
					image->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
					m_imageQueue.emplace(std::move(image));
					++m_capacity;
				}
				m_isInitialized = true;
			}
		}

		std::shared_ptr<T> Acquire()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if(m_imageQueue.empty())
			{
				LOG_INFO("Image Pool is empty, Create one new image buffer");
				std::unique_ptr<T> image(new T());
				image->Initialize(m_imageSize.width, m_imageSize.height, nullptr);
				m_imageQueue.emplace(std::move(image));
				++m_capacity;
			}
			LOG_INFO_VALUE("Image Pool Capacity = ", m_capacity);
			LOG_INFO_VALUE("Image Pool Count = ", m_imageQueue.size());
			
			std::unique_ptr<T, Deleter> ptr
			(
				m_imageQueue.front().release(),
				[this](T *t)
				{
					std::lock_guard<std::mutex> lock2(m_mutex);
					if (t != nullptr)
					{
						m_imageQueue.push(std::move(std::unique_ptr<T>(t)));
					}
					else
					{
						LOG_ERROR("ptr is NULL");
					}
				}
			);		
			
			if (ptr == nullptr)
			{
				LOG_ERROR("NULL");
				//LOG_INFO_VALUE("Image Pool size = ", m_imageQueue.size());
			}
			m_imageQueue.pop();

			return std::shared_ptr<T>(std::move(ptr));
		}

		int Count()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return static_cast<int>(m_imageQueue.size());
		}

		int Capacity()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return m_capacity;
		}

	private:
		std::queue<std::unique_ptr<T>> m_imageQueue;
		std::mutex m_mutex;
		Size m_imageSize;
		int m_capacity;
		bool m_isInitialized;
	};


	/// \brief IImagePool.
	class IImagePool : public CNonCopyable
	{
	public:
		virtual void Initialize(int, Size) = 0;

		virtual std::any Acquire() = 0;

		virtual int Count() = 0;

		virtual int Capacity() = 0;
	};


	/// \brief CImagePool8u1c.
	class CImagePool8u1c : public IImagePool
	{
	public:
		void Initialize(int count, Size imageSize)
		{
			m_imagePool8u1c.Initialize(count, imageSize);
		}

		std::any Acquire()
		{
			std::any anyImage;
			auto image = m_imagePool8u1c.Acquire();
			if (image != nullptr)
			{
				anyImage = std::move(image);
			}
			return std::move(anyImage);
		}


		int Count()
		{
			return m_imagePool8u1c.Count();
		}

		int Capacity()
		{
			return m_imagePool8u1c.Capacity();
		}

	private:
		CImagePool<CImage8u1cIPPI> m_imagePool8u1c;
	};


	/// \brief CImagePool8u4c.
// 	class CImagePool8u4c : public IImagePool
// 	{
// 	public:
// 		void Initialize(int count, Size imageSize)
// 		{
// 			m_imagePool8u4c.Initialize(count, imageSize);
// 		}
// 
// 		std::any Acquire()
// 		{
// 
// 			return m_imagePool8u4c.Acquire();
// 		}
// 
// 
// 		int Count()
// 		{
// 			return m_imagePool8u4c.Count();
// 		}
// 
// 		int Capacity()
// 		{
// 			return m_imagePool8u4c.Capacity();
// 		}
// 
// 	private:
// 		CImagePool<CImage8u4cIPPI> m_imagePool8u4c;
// 	};


	/// \brief CImagePool16u1c
	class CImagePool16u1c : public IImagePool
	{
	public:
		void Initialize(int count, Size imageSize)
		{
			m_imagePool16u1c.Initialize(count, imageSize);
		}
	
		std::any Acquire()
		{
			std::any anyImage;
			auto image = m_imagePool16u1c.Acquire();
			if (image != nullptr)
			{
				anyImage = std::move(image);
			}
			return std::move(anyImage);
		}

		int Count()
		{
			return m_imagePool16u1c.Count();
		}

		int Capacity()
		{
			return m_imagePool16u1c.Capacity();
		}

	private:
		CImagePool<CImage16u1cIPPI> m_imagePool16u1c;
	};


	/// \brief CImage32f1cPool.
	class CImagePool32f1c : public IImagePool
	{
	public:
		void Initialize(int count, Size imageSize)
		{
			m_imagePool32f1c.Initialize(count, imageSize);
		}

		std::any Acquire()
		{
			return m_imagePool32f1c.Acquire();
		}

		int Count()
		{
			return m_imagePool32f1c.Count();
		}

		int Capacity()
		{
			return m_imagePool32f1c.Capacity();
		}

	private:
		CImagePool<CImage32f1cIPPI> m_imagePool32f1c;
	};

}

#endif



