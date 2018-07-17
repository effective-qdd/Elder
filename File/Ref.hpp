/**
* \file Ref.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.05.18
*/
#ifndef _REF_H
#define _REF_H


// My Class Includes
#include "Mrc.hpp"


namespace ELDER
{
	namespace FILE
	{
		/// \brief CRefReader class.
		class CRefReader : public CPictureReader
		{
		public:
			CRefReader() 
				: CPictureReader() {};


			~CRefReader() override {};

			FileInfo Open(const std::string &) override {};

			void Read(CAny) override {};
		
		};


		/// \brief CRefReader8u1c class.
		class CRefReader8u1c final : public CRefReader
		{
		public:
			CRefReader8u1c() : CRefReader() {};


			~CRefReader8u1c() override {};

			FileInfo Open(const std::string &filePath) override
			{
				return m_mrcReader8u1c.Open(filePath);
			}


			void Read(CAny anyImage) override
			{
				m_mrcReader8u1c.Read(anyImage);
			}


		private:
			CMrcReader8u1c m_mrcReader8u1c;
		};


		/// \brief CRefReader16u1c class.
		class CRefReader16u1c final : public CRefReader
		{
		public:
			CRefReader16u1c() 
				: CRefReader() {};


			~CRefReader16u1c() override {};

			FileInfo Open(const std::string &filePath) override
			{
				return m_mrcReader16u1c.Open(filePath);
			}


			void Read(CAny anyImage) override
			{
				m_mrcReader16u1c.Read(anyImage);
			}

		private:
			CMrcReader16u1c m_mrcReader16u1c;
		};


		/// \brief CRefReader32f1c class.
		class CRefReader32f1c final : public CRefReader
		{
		public:
			CRefReader32f1c() 
				: CRefReader() {};


			~CRefReader32f1c() override {}

			FileInfo Open(const std::string &filePath) override
			{
				return m_mrcReader32f1c.Open(filePath);
			}


			void Read(CAny anyImage) override
			{
				m_mrcReader32f1c.Read(anyImage);
			}


		private:
			CMrcReader32f1c m_mrcReader32f1c;
		};
	}
}


#endif