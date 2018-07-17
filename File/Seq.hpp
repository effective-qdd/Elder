/**
* \file Seq.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.02.07
*/
#ifndef _SEQ_H
#define _SEQ_H


// System Class Includes
#include <omp.h>


// My Class Includes
#include "Stack.hpp"


namespace ELDER
{
	namespace FILE
	{
		/// Defines
		const char SEQ_TAG[] =
			"\xED\xFE\x00\x00"
			"\x4E\x00\x6F\x00"
			"\x72\x00\x70\x00"
			"\x69\x00\x78\x00"
			"\x20\x00\x73\x00"
			"\x65\x00\x71\x00";
		
		/// 
		class CSeq : public CNonCopyable
		{
		public:
			static const int SEQ_TAG_SIZE = sizeof(SEQ_TAG);

			const int SEQ_HEADER_SIZE = 0x400;

			/// \brief SeqInfo struct.
			struct SeqInfo
			{
				int imageWidth = 0;
				int imageHeight = 0;
				int imageBitDepth = 0;
				int imageBitDepthReal = 0;
				int imageSizeBytes = 0;
				int imageFormat = 0;
				int imageCounts = 0;
			};

			CSeq() = default;

			~CSeq() = default;
		};

		/// \brief CSeqReader Class
		class CSeqReader : public CStackReader, public CSeq
		{
		public:
			CSeqReader() : CStackReader(), m_trueImageOffset(0), m_alignedSizeBytes(0) {};
			
			virtual ~CSeqReader() override
			{
				Close();
			}

			static DataFormats PreOpen(const std::string & filePath)
			{
				auto dataFormat = DataFormats::kNoneGraySacle;

				std::ifstream m_fileReader;
				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open seq file failed!");

				char tag[SEQ_TAG_SIZE] = "";
				m_fileReader.read(tag, SEQ_TAG_SIZE);
				ENSURE_THROW_MSG(strcmp(tag, SEQ_TAG) == 0, "Input file format error.");

				m_fileReader.seekg(0x224, m_fileReader.beg);
				SeqInfo seqInfo;
				m_fileReader.read(reinterpret_cast<char *>(&seqInfo), sizeof(SeqInfo));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(SeqInfo), "Read file error.");
				if (seqInfo.imageBitDepth == 8)
				{
					dataFormat = DataFormats::k8BitGrayScale;
				}
				else if (seqInfo.imageBitDepth == 16)
				{
					dataFormat = DataFormats::k16BitGrayScale;
				}
				else if (seqInfo.imageBitDepth == 32)
				{
					dataFormat = DataFormats::k32BitGrayScale;
				}

				return dataFormat;
			}


			FileInfo Open(const std::string &) override { return FileInfo(); };

			void Read(std::any, unsigned long) override {};

			void Close() override
			{
				if (m_fileReader.is_open())
				{
					m_fileReader.close();
				}
			}

		protected:
			std::ifstream m_fileReader;

			long long m_trueImageOffset;

			int m_alignedSizeBytes;		
		};


		/// \brief CSeqReader8u1c
		class CSeqReader8u1c final : public CSeqReader
		{
		public:
			CSeqReader8u1c() : CSeqReader() {};


			~CSeqReader8u1c() = default;


			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open seq file failed!");

				char tag[SEQ_TAG_SIZE] = "";
				m_fileReader.read(tag, SEQ_TAG_SIZE);
				ENSURE_THROW_MSG(strcmp(tag, SEQ_TAG) == 0, "Input file format error.");

				m_fileReader.seekg(28, m_fileReader.beg);
				int version = 0;
				m_fileReader.read(reinterpret_cast<char *>(&version), 4);
				if (version == 4)
				{
					m_alignedSizeBytes = 1024;
				}
				else if (version == 5)
				{
					m_alignedSizeBytes = 8192;
				}

				FileInfo fileInfo;
				//fileInfo.tag = FT_STACK;
				
				m_fileReader.seekg(0x224, m_fileReader.beg);
				SeqInfo seqInfo;
				m_fileReader.read(reinterpret_cast<char *>(&seqInfo), sizeof(SeqInfo));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(SeqInfo), "Read file error.");

				m_fileReader.seekg(0x244, m_fileReader.beg);
				m_fileReader.read(reinterpret_cast<char *>(&m_trueImageOffset), sizeof(int));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(int), "Read file error.");

				fileInfo.imageInfo.size.width = seqInfo.imageWidth;
				fileInfo.imageInfo.size.height = seqInfo.imageHeight;
				fileInfo.imageInfo.bitDepth = seqInfo.imageBitDepth;
				fileInfo.imageInfo.channel = 1;
				fileInfo.imageCounts = seqInfo.imageCounts;

				return fileInfo;
			};

			
			void Read(std::any anyImage, unsigned long i)
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error Image Format");
				long long offset = m_trueImageOffset * i + /*SEQ_HEADER_SIZE*/m_alignedSizeBytes;
				m_fileReader.seekg(offset, m_fileReader.beg);
				auto image = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(anyImage);
				m_fileReader.read(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height()/*m_imageSizeBytes*/);
				ENSURE_THROW_MSG(m_fileReader.good(), "Read file error.");
			};						
		};


		/// \brief CFRSeq10u1c class.
		class CSeqReader10u1c final : public CSeqReader
		{
		public:
			CSeqReader10u1c() 
				: CSeqReader()
				, m_rawImage(nullptr) 
			{};

			~CSeqReader10u1c() = default;

			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open seq file failed!");

				char tag[SEQ_TAG_SIZE] = "";
				m_fileReader.read(tag, SEQ_TAG_SIZE);
				ENSURE_THROW_MSG(strcmp(tag, SEQ_TAG) == 0, "Input file format error.");

				m_fileReader.seekg(28, m_fileReader.beg);
				int version = 0;
				m_fileReader.read(reinterpret_cast<char *>(&version), 4);
				if (version == 4)
				{
					m_alignedSizeBytes = 1024;
				}
				else if (version == 5)
				{
					m_alignedSizeBytes = 8192;
				}

				FileInfo fileInfo;
				//fileInfo.tag = FT_STACK;

				m_fileReader.seekg(0x224, m_fileReader.beg);
				SeqInfo seqInfo;
				m_fileReader.read(reinterpret_cast<char *>(&seqInfo), sizeof(SeqInfo));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(SeqInfo), "Read file error.");

				m_fileReader.seekg(0x244, m_fileReader.beg);
				m_fileReader.read(reinterpret_cast<char *>(&m_trueImageOffset), sizeof(int));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(int), "Read file error.");

				fileInfo.imageInfo.size.width = seqInfo.imageWidth;
				fileInfo.imageInfo.size.height = seqInfo.imageHeight;
				fileInfo.imageInfo.bitDepth = seqInfo.imageBitDepth;
				fileInfo.imageInfo.channel = 1;
				fileInfo.imageCounts = seqInfo.imageCounts;

				m_rawImage = std::make_shared<CImage8u1cIPPI>();
				m_rawImage->Initialize(static_cast<int>(fileInfo.imageInfo.size.width * 1.25), fileInfo.imageInfo.size.height);
			
				return fileInfo;
			};


			void Read(std::any anyImage, unsigned long i)
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error Image Format");
				long long offset = m_trueImageOffset * i + /*SEQ_HEADER_SIZE*/m_alignedSizeBytes;
				m_fileReader.seekg(offset, m_fileReader.beg);
				auto image = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(anyImage);
				m_fileReader.read(reinterpret_cast<char *>(m_rawImage->Data()), m_rawImage->WidthBytes() * m_rawImage->Height());
				Mono8064LSB16MSBToFloat32(image->Width(), image->Height(), m_rawImage->Data(), image->Data());
				ENSURE_THROW_MSG(m_fileReader.good(), "Read file error.");
			};

		private:
			void Mono8064LSB16MSBToFloat32(int width, int height, unsigned char *srcImage, unsigned short *destImage)
			{
				//omp_set_num_threads(4);
// #pragma omp parallel for private(h, w)\
// 	shared(height, width, srcImage, destImage)
				int widthPitch = int(width * 1.25);
#pragma omp parallel for schedule(static)
				for (int h = 0; h < height; ++h)
				{
					int srcImageBufIndex = widthPitch * h;
					int destImageBufIndex = width * h;
					for (int w = 0; w < width; w += 8, srcImageBufIndex += 10)
					{
						destImage[destImageBufIndex + w + 0] = srcImage[srcImageBufIndex + 0];
						destImage[destImageBufIndex + w + 1] = srcImage[srcImageBufIndex + 1];
						destImage[destImageBufIndex + w + 2] = srcImage[srcImageBufIndex + 2];
						destImage[destImageBufIndex + w + 3] = srcImage[srcImageBufIndex + 3];
						destImage[destImageBufIndex + w + 4] = srcImage[srcImageBufIndex + 4];
						destImage[destImageBufIndex + w + 5] = srcImage[srcImageBufIndex + 5];
						destImage[destImageBufIndex + w + 6] = srcImage[srcImageBufIndex + 6];
						destImage[destImageBufIndex + w + 7] = srcImage[srcImageBufIndex + 7];
						unsigned char value0 = (unsigned char)(srcImage[srcImageBufIndex + 8] << 0);
						value0 = (unsigned char)(value0 >> 6);
						unsigned char value1 = (unsigned char)(srcImage[srcImageBufIndex + 8] << 2);
						value1 = (unsigned char)(value1 >> 6);
						unsigned char value2 = (unsigned char)(srcImage[srcImageBufIndex + 8] << 4);
						value2 = (unsigned char)(value2 >> 6);
						unsigned char value3 = (unsigned char)(srcImage[srcImageBufIndex + 8] << 6);
						value3 = (unsigned char)(value3 >> 6);
						unsigned char value4 = (unsigned char)(srcImage[srcImageBufIndex + 9] << 0);
						value4 = (unsigned char)(value4 >> 6);
						unsigned char value5 = (unsigned char)(srcImage[srcImageBufIndex + 9] << 2);
						value5 = (unsigned char)(value5 >> 6);
						unsigned char value6 = (unsigned char)(srcImage[srcImageBufIndex + 9] << 4);
						value6 = (unsigned char)(value6 >> 6);
						unsigned char value7 = (unsigned char)(srcImage[srcImageBufIndex + 9] << 6);
						value7 = (unsigned char)(value7 >> 6);
						destImage[destImageBufIndex + w + 0] += value3 << 8;
						destImage[destImageBufIndex + w + 1] += value2 << 8;
						destImage[destImageBufIndex + w + 2] += value1 << 8;
						destImage[destImageBufIndex + w + 3] += value0 << 8;
						destImage[destImageBufIndex + w + 4] += value7 << 8;
						destImage[destImageBufIndex + w + 5] += value6 << 8;
						destImage[destImageBufIndex + w + 6] += value5 << 8;
						destImage[destImageBufIndex + w + 7] += value4 << 8;
					}
				}
			}

			std::shared_ptr<CImage8u1cIPPI> m_rawImage;
		};


		/// \brief CSeqReader16u1c.
		class CSeqReader16u1c final : public CSeqReader
		{
		public:
			CSeqReader16u1c() 
				: CSeqReader() {};
			

			~CSeqReader16u1c() = default;

			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_fileReader.open(filePath, std::ios::binary);
				ENSURE_THROW_MSG(m_fileReader.is_open(), "Open seq file failed!");

				char tag[SEQ_TAG_SIZE] = "";
				m_fileReader.read(tag, SEQ_TAG_SIZE);
				ENSURE_THROW_MSG(strcmp(tag, SEQ_TAG) == 0, "Input file format error.");

				m_fileReader.seekg(28, m_fileReader.beg);
				int version = 0;
				m_fileReader.read(reinterpret_cast<char *>(&version), 4);
				if (version == 4)
				{
					m_alignedSizeBytes = 1024;
				}
				else if (version == 5)
				{
					m_alignedSizeBytes = 8192;
				}

				FileInfo fileInfo;
				//fileInfo.tag = FT_STACK;

				m_fileReader.seekg(0x224, m_fileReader.beg);
				SeqInfo seqInfo;
				m_fileReader.read(reinterpret_cast<char *>(&seqInfo), sizeof(SeqInfo));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(SeqInfo), "Read file error.");

				m_fileReader.seekg(0x244, m_fileReader.beg);
				m_fileReader.read(reinterpret_cast<char *>(&m_trueImageOffset), sizeof(int));
				ENSURE_THROW_MSG(m_fileReader.gcount() == sizeof(int), "Read file error.");

				fileInfo.imageInfo.size.width = seqInfo.imageWidth;
				fileInfo.imageInfo.size.height = seqInfo.imageHeight;
				fileInfo.imageInfo.bitDepth = seqInfo.imageBitDepth;
				fileInfo.imageInfo.channel = 1;
				fileInfo.imageCounts = seqInfo.imageCounts;

				return fileInfo;
			};


			void Read(std::any anyImage, unsigned long i)
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error Image Format");
				long long offset = m_trueImageOffset * i + m_alignedSizeBytes;
				m_fileReader.seekg(offset, m_fileReader.beg);
				auto image = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(anyImage);
				m_fileReader.read(reinterpret_cast<char *>(image->Data()), image->WidthBytes() * image->Height()/*m_imageSizeBytes*/);
				ENSURE_THROW_MSG(m_fileReader.good(), "Read file error.");
			};
		};
	}
}

#endif