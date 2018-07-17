/**
* \file Mrc.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.28
*/
#ifndef _MRC_H
#define _MRC_H


// My Class Includes
#include "Picture.hpp"


namespace ELDER
{
	namespace FILE
	{
		constexpr int kMrc8u = 0;
		constexpr int kMrc16u = 6;
		constexpr int kMrc32f = 2;
		constexpr int kMecHeaderSize = 1024;

		/// \brief CMrc class.
		class CMrc : public CNonCopyable
		{
		public:
			
			

			CMrc() = default;

			virtual ~CMrc() = default;
		
		};


		/// \brief MRC reader class.
		class CMrcReader : public CPictureReader, public CMrc
		{
		public:
			CMrcReader()
				: CPictureReader()
				, CMrc()
			{}

			virtual ~CMrcReader() override {};

			static DataFormats PreOpen(const std::string &filePath)
			{
				auto dataFormat = DataFormats::kNoneGraySacle;
				std::ifstream fileReader;
				fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(fileReader.is_open(), "Open mrc file failed!");

				FileInfo fileInfo;
				fileInfo.imageInfo.channel = 1;
				fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.width), sizeof(int));
				fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.height), sizeof(int));
				fileReader.read(reinterpret_cast<char *>(&fileInfo.imageCounts), sizeof(int));
				int bitDepth = -1;
				fileReader.read(reinterpret_cast<char *>(&bitDepth), sizeof(int));
				if (bitDepth == kMrc8u)
				{
					dataFormat = DataFormats::k8BitGrayScale;
				}
				else if (bitDepth == kMrc16u)
				{
					dataFormat = DataFormats::k16BitGrayScale;
				}
				else if (bitDepth == kMrc32f)
				{
					dataFormat = DataFormats::k32BitGrayScale;
				}
				fileReader.close();

				return dataFormat;
			}

			FileInfo Open(const std::string &) override { return FileInfo(); };

			void Read(std::any) override {};

		protected:
			void Close()
			{
				if (m_fileReader.is_open())
				{
					m_fileReader.close();
				}
			}

		protected:
			std::ifstream m_fileReader;
		};


		/// \brief MRC reader class for 8 bit unsigned 1 channel.
		class CMrcReader8u1c final : public CMrcReader
		{
		public:
			CMrcReader8u1c() 
				: CMrcReader()
			{};


			~CMrcReader8u1c() override
			{ 
				Close(); 
			};


			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open mrc file failed!");

				FileInfo fileInfo;
				fileInfo.imageInfo.channel = 1;
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.width), sizeof(int));
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.height), sizeof(int));
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageCounts), sizeof(int));
				int bitDepth = -1;
				m_fileReader.read(reinterpret_cast<char *>(&bitDepth), sizeof(int));
				ASSERT_LOG(bitDepth == kMrc8u, "Error MRC Type");
				fileInfo.imageInfo.bitDepth = 8;

				return fileInfo;
			}


			void Read(std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error Image Format");
				long long int  offset = kMecHeaderSize;
				m_fileReader.seekg(offset, m_fileReader.beg);
				auto image = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(anyImage);
				m_fileReader.read(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height()/*m_imageSizeBytes*/);
				ENSURE_THROW_MSG(m_fileReader.good(), "Read file error.");
			}
		};


		/// \brief MRC reader class for 16 bit unsigned 1 channel.
		class CMrcReader16u1c final : public CMrcReader
		{
		public:
			CMrcReader16u1c() : CMrcReader() {};


			~CMrcReader16u1c() override
			{ 
				Close(); 
			};


			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open mrc file failed!");

				FileInfo fileInfo;
				fileInfo.imageInfo.channel = 1;
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.width), sizeof(int));
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.height), sizeof(int));
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageCounts), sizeof(int));
				int bitDepth = -1;
				m_fileReader.read(reinterpret_cast<char *>(&bitDepth), sizeof(int));
				ASSERT_LOG(bitDepth == kMrc16u, "Error MRC Type");
				fileInfo.imageInfo.bitDepth = 16;
				
				return fileInfo;
			}


			void Read(std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error Image Format");
				long long int  offset = kMecHeaderSize;
				m_fileReader.seekg(offset, m_fileReader.beg);
				auto image = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(anyImage);
				m_fileReader.read(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height()/*m_imageSizeBytes*/);
				ENSURE_THROW_MSG(m_fileReader.good(), "Read file error.");
			}
		};


		/// \brief MRC read class for 32 float 1 channel.
		class CMrcReader32f1c final : public CMrcReader
		{
		public:
			CMrcReader32f1c() : CMrcReader() {};


			~CMrcReader32f1c() override
			{ 
				Close(); 
			};


			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open mrc file failed!");

				FileInfo fileInfo;
				fileInfo.imageInfo.channel = 1;
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.width), sizeof(int));
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageInfo.size.height), sizeof(int));
				m_fileReader.read(reinterpret_cast<char *>(&fileInfo.imageCounts), sizeof(int));
				int bitDepth = -1;
				m_fileReader.read(reinterpret_cast<char *>(&bitDepth), sizeof(int));
				ASSERT_LOG(bitDepth == kMrc32f, "Error MRC Type");
				fileInfo.imageInfo.bitDepth = 32;
				
				return fileInfo;
			}


			void Read(std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error Image Format");
				long long int  offset = kMecHeaderSize;
				m_fileReader.seekg(offset, m_fileReader.beg);
				auto image = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(anyImage);
				m_fileReader.read(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height()/*m_imageSizeBytes*/);
				ENSURE_THROW_MSG(m_fileReader.good(), "Read file error.");
			}
		};


		/// \brief MRC writer class.
		class CMrcWriter : public CPictureWriter, public CMrc
		{
		public:
			CMrcWriter()
				: CPictureWriter()
				, CMrc()
			{}

			virtual ~CMrcWriter() override {};

			void Write(const std::string &, std::any) override {};

		protected:
			void Close()
			{
				if (m_fileWriter.is_open())
				{
					m_fileWriter.close();
				}
			}

		protected:
			std::ofstream m_fileWriter;
		};


		/// \brief MRC writer class for 8 bit unsigned 1 channel.
		class CMrcWriter8u1c final : public CMrcWriter
		{
		public:
			CMrcWriter8u1c() 
				: CMrcWriter()
			{};


			~CMrcWriter8u1c() override {};


			void Write(const std::string &filePath, std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error Image Format");
				m_fileWriter.open(filePath, std::ios::binary | std::ios::trunc);
				ENSURE_THROW_MSG(m_fileWriter.is_open(), "Create mrc file failed!");
				char header[kMecHeaderSize] = { 0 };
				m_fileWriter.write(header, kMecHeaderSize);

				m_fileWriter.seekp(0, m_fileWriter.beg);
				auto image = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(anyImage);
				auto width = image->Width();
				m_fileWriter.write((char *)(&width), sizeof(int));
				auto height = image->Height();
				m_fileWriter.write((char *)(&height), sizeof(int));
				auto frames = 1;
				m_fileWriter.write((char *)(&frames), sizeof(int));
				auto bitDepth = image->BitDepth();
				ASSERT_LOG(bitDepth == 8, "Error image bit depth");
				m_fileWriter.write((char *)(&kMrc8u), sizeof(int));

				m_fileWriter.seekp(28, m_fileWriter.beg);

				m_fileWriter.write((char *)(&width), sizeof(int));
				m_fileWriter.write((char *)(&height), sizeof(int));
				int tag1 = 1;
				m_fileWriter.write((char *)(&tag1), sizeof(int));

				m_fileWriter.write((char *)(&width), sizeof(int));
				m_fileWriter.write((char *)(&height), sizeof(int));
				int tag2 = 1;
				m_fileWriter.write((char *)(&tag2), sizeof(int));
				int tag3 = 90;
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				int mapc = 1;
				int mapr = 2;
				int maps = 3;
				m_fileWriter.write((char *)(&mapc), sizeof(int));
				m_fileWriter.write((char *)(&mapr), sizeof(int));
				m_fileWriter.write((char *)(&maps), sizeof(int));
				int amin = 0;
				int amax = 0;
				int	amean = 0;
				int ispg = 0;
				m_fileWriter.write((char *)(&amin), sizeof(int));
				m_fileWriter.write((char *)(&amax), sizeof(int));
				m_fileWriter.write((char *)(&amean), sizeof(int));
				m_fileWriter.write((char *)(&ispg), sizeof(int));
// 				m_fileWriter.seekp(150, m_fileWriter.beg);
// 				m_fileWriter.write((char *)(&fileInfo.imageInfo.bitDepthReal), sizeof(int));
				m_fileWriter.seekp(208, m_fileWriter.beg);
				char map[4] = { 'M', 'A', 'P', ' ' };
				m_fileWriter.write(map, sizeof(int));
				char stamp[4] = { 68, 65, 0, 0 };
				m_fileWriter.write(stamp, sizeof(int));
				ENSURE_THROW_MSG(m_fileWriter.good(), "Write file error.");

				m_fileWriter.seekp(kMecHeaderSize, m_fileWriter.beg);
				m_fileWriter.write(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height());
				ENSURE_THROW_MSG(m_fileWriter.good(), "Write file error.");

				Close();
			}
		};


		/// \brief MRC writer class for 16 bit unsigned 1 channel.
		class CMrcWriter16u1c final : public CMrcWriter
		{
		public:
			CMrcWriter16u1c() : CMrcWriter() {};


			~CMrcWriter16u1c() override
			{
				Close();
			}


			void Write(const std::string &filePath, std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error image type");
				m_fileWriter.open(filePath, std::ios::binary | std::ios::trunc);
				ENSURE_THROW_MSG(m_fileWriter.is_open(), "Create mrc file failed!");
				char header[kMecHeaderSize] = { 0 };
				m_fileWriter.write(header, kMecHeaderSize);

				m_fileWriter.seekp(0, m_fileWriter.beg);
				auto image = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(anyImage);
				auto width = image->Width();
				m_fileWriter.write((char *)(&width), sizeof(int));
				auto height = image->Height();
				m_fileWriter.write((char *)(&height), sizeof(int));
				auto frames = 1;
				m_fileWriter.write((char *)(&frames), sizeof(int));
				auto bitDepth = image->BitDepth();
				ASSERT_LOG(bitDepth == 16, "Error image bit depth");
				m_fileWriter.write((char *)(&kMrc16u), sizeof(int));

				m_fileWriter.seekp(28, m_fileWriter.beg);

				m_fileWriter.write((char *)(&width), sizeof(int));
				m_fileWriter.write((char *)(&height), sizeof(int));
				int tag1 = 1;
				m_fileWriter.write((char *)(&tag1), sizeof(int));

				m_fileWriter.write((char *)(&width), sizeof(int));
				m_fileWriter.write((char *)(&height), sizeof(int));
				int tag2 = 1;
				m_fileWriter.write((char *)(&tag2), sizeof(int));
				int tag3 = 90;
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				int mapc = 1;
				int mapr = 2;
				int maps = 3;
				m_fileWriter.write((char *)(&mapc), sizeof(int));
				m_fileWriter.write((char *)(&mapr), sizeof(int));
				m_fileWriter.write((char *)(&maps), sizeof(int));
				int amin = 0;
				int amax = 0;
				int	amean = 0;
				int ispg = 0;
				m_fileWriter.write((char *)(&amin), sizeof(int));
				m_fileWriter.write((char *)(&amax), sizeof(int));
				m_fileWriter.write((char *)(&amean), sizeof(int));
				m_fileWriter.write((char *)(&ispg), sizeof(int));
				m_fileWriter.seekp(208, m_fileWriter.beg);
				char map[4] = { 'M', 'A', 'P', ' ' };
				m_fileWriter.write(map, sizeof(int));
				char stamp[4] = { 68, 65, 0, 0 };
				m_fileWriter.write(stamp, sizeof(int));
				ENSURE_THROW_MSG(m_fileWriter.good(), "Write file error.");

				m_fileWriter.seekp(kMecHeaderSize, m_fileWriter.beg);
				m_fileWriter.write(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height());
				ENSURE_THROW_MSG(m_fileWriter.good(), "Write file error.");

				Close();
			}
		};

		
		/// \brief MRC writer class for 32 float 1 channel.
		class CMrcWriter32f1c final : public CMrcWriter
		{
		public:
			CMrcWriter32f1c() : CMrcWriter() {};


			~CMrcWriter32f1c() override
			{
				Close();
			}


			void Write(const std::string &filePath, std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error image type");
				m_fileWriter.open(filePath, std::ios::binary | std::ios::trunc);
				ENSURE_THROW_MSG(m_fileWriter.is_open(), "Create mrc file failed!");
				char header[kMecHeaderSize] = { 0 };
				m_fileWriter.write(header, kMecHeaderSize);

				m_fileWriter.seekp(0, m_fileWriter.beg);
				auto image = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(anyImage);
				auto width = image->Width();
				m_fileWriter.write((char *)(&width), sizeof(int));
				auto height = image->Height();
				m_fileWriter.write((char *)(&height), sizeof(int));
				auto frames = 1;
				m_fileWriter.write((char *)(&frames), sizeof(int));
				auto bitDepth = image->BitDepth();
				ASSERT_LOG(bitDepth == 32, "Error image bit depth");
				m_fileWriter.write((char *)(&kMrc32f), sizeof(int));

				m_fileWriter.seekp(28, m_fileWriter.beg);

				m_fileWriter.write((char *)(&width), sizeof(int));
				m_fileWriter.write((char *)(&height), sizeof(int));
				int tag1 = 1;
				m_fileWriter.write((char *)(&tag1), sizeof(int));

				m_fileWriter.write((char *)(&width), sizeof(int));
				m_fileWriter.write((char *)(&height), sizeof(int));
				int tag2 = 1;
				m_fileWriter.write((char *)(&tag2), sizeof(int));
				int tag3 = 90;
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				m_fileWriter.write((char *)(&tag3), sizeof(int));
				int mapc = 1;
				int mapr = 2;
				int maps = 3;
				m_fileWriter.write((char *)(&mapc), sizeof(int));
				m_fileWriter.write((char *)(&mapr), sizeof(int));
				m_fileWriter.write((char *)(&maps), sizeof(int));
				int amin = 0;
				int amax = 0;
				int	amean = 0;
				int ispg = 0;
				m_fileWriter.write((char *)(&amin), sizeof(int));
				m_fileWriter.write((char *)(&amax), sizeof(int));
				m_fileWriter.write((char *)(&amean), sizeof(int));
				m_fileWriter.write((char *)(&ispg), sizeof(int));
				m_fileWriter.seekp(208, m_fileWriter.beg);
				char map[4] = { 'M', 'A', 'P', ' ' };
				m_fileWriter.write(map, sizeof(int));
				char stamp[4] = { 68, 65, 0, 0 };
				m_fileWriter.write(stamp, sizeof(int));
				ENSURE_THROW_MSG(m_fileWriter.good(), "Write file error.");

				m_fileWriter.seekp(kMecHeaderSize, m_fileWriter.beg);
				m_fileWriter.write(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height());
				ENSURE_THROW_MSG(m_fileWriter.good(), "Write file error.");

				Close();
			}
		};
	}
}

#endif













