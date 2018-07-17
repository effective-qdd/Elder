/**
* \file Tif.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.10.10
*/
#ifndef _TIF_H
#define _TIF_H


// Links
#pragma comment(lib, "LibTiff/lib/libtiff.lib")


// My Class Includes
#include "Picture.hpp"
#include "LibTiff/include/tiffio.h"


namespace ELDER
{
	namespace FILE
	{		
		/// \brief CTif class.
		class CTif : public CNonCopyable
		{
		public:
			CTif() 
				: m_tiff(nullptr)
				, m_stripSize(0)
				, m_numberOfStrips(0)
			{}

			virtual ~CTif() {};			

		protected:
			TIFF *m_tiff;
			tmsize_t m_stripSize;
			tmsize_t m_numberOfStrips;
		};


		/// \brief CTifReader class.
		class CTifReader : public CPictureReader, public CTif
		{
		public:

			CTifReader() 
				: CPictureReader()
				, CTif() 
			{};

			virtual ~CTifReader() = default;


			static DataFormats PreOpen(const std::string & filePath)
			{
				auto dataFormat = DataFormats::kNoneGraySacle;
				TIFF *tiff = nullptr;
				
				tiff = TIFFOpen(filePath.c_str(), "r");
				ENSURE_THROW_MSG(tiff != nullptr, "Open tiff file failed!");
				int spp = 0;
				TIFFGetField(tiff, TIFFTAG_SAMPLESPERPIXEL, &spp);
				int bps = 0;
				TIFFGetField(tiff, TIFFTAG_BITSPERSAMPLE, &bps);
				if (bps == 8)
				{
					dataFormat = DataFormats::k8BitGrayScale;
				}
				else if (bps == 16)
				{
					dataFormat = DataFormats::k16BitGrayScale;
				}
				else if (bps == 32)
				{
					dataFormat = DataFormats::k32BitGrayScale;
				}
				TIFFClose(tiff);
				tiff = nullptr;

				return dataFormat;
			}

			FileInfo Open(const std::string &) override { return FileInfo(); };

			void Read(std::any) override {};

			void Close()
			{
				if (m_tiff != nullptr)
				{
					TIFFClose(m_tiff);
					m_tiff = nullptr;
				}
			}
		};


		/// \brief CTifReader8u1c class.
		class CTifReader8u1c final : public CTifReader
		{
		public:
			CTifReader8u1c()
				: CTifReader()
				, m_data(nullptr)
			{};

			~CTifReader8u1c()
			{
				Close();
			}

			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_tiff = TIFFOpen(filePath.c_str(), "r");
				ENSURE_THROW_MSG(m_tiff != nullptr, "Open tiff file failed!");

				uint16 compression;
				TIFFGetField(m_tiff, TIFFTAG_COMPRESSION, &compression);
				ENSURE_THROW_MSG(compression == COMPRESSION_NONE, "Unsupported tiff format!");

				uint16 photoMetric;
				TIFFGetField(m_tiff, TIFFTAG_PHOTOMETRIC, &photoMetric);
				ENSURE_THROW_MSG(photoMetric == PHOTOMETRIC_MINISBLACK, "Unsupported tiff format!");

// 				uint16 orientation;
// 				TIFFGetField(m_tiff, TIFFTAG_ORIENTATION, &orientation);
// 				ENSURE_THROW_MSG(orientation == ORIENTATION_TOPLEFT, "Unsupported tiff format!");

// 				uint16 fillOrder;
// 				TIFFGetField(m_tiff, TIFFTAG_FILLORDER, &fillOrder);
// 				ENSURE_THROW_MSG(fillOrder == FILLORDER_MSB2LSB, "Unsupported tiff format!");

				m_stripSize = TIFFStripSize(m_tiff);
				m_numberOfStrips = TIFFNumberOfStrips(m_tiff);

				FileInfo fileInfo;
				TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &fileInfo.imageInfo.channel);
				ENSURE_THROW_MSG(fileInfo.imageInfo.channel == 1, "Unsupported tiff format!");

				TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &fileInfo.imageInfo.bitDepth);
				ENSURE_THROW_MSG(fileInfo.imageInfo.bitDepth == 8, "Unsupported tiff format!");

// 				TIFFGetField(m_tiff, TIFFTAG_IMAGEDEPTH, &imageInfo.bitDepthReal);
// 				if (imageInfo.bitDepthReal == 0)
// 				{
// 					imageInfo.bitDepthReal = 8;
// 				}
// 				else
// 				{
// 					ENSURE_THROW_MSG(imageInfo.bitDepthReal == 8, "Unsupported tiff format!");
// 				}

				TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &fileInfo.imageInfo.size.width);
				TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &fileInfo.imageInfo.size.height);
				if (fileInfo.imageInfo.size.width % 64 != 0)
				{
					m_data = ippsMalloc_8u(fileInfo.imageInfo.size.width * fileInfo.imageInfo.size.height);
				}

				//fileInfo.tag = FT_PICTURE;
				fileInfo.imageCounts;

				return fileInfo;
			}


			void Read(std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error Image Format");
				auto image = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(anyImage);
				auto data = image->Data();
				tsize_t offset = 0;
				tsize_t result = 0;
				if (image->Width() == image->WidthBytes())
				{
					for (int i = 0; i < m_numberOfStrips; ++i)
					{
						result = TIFFReadEncodedStrip(m_tiff, i, data + offset, m_stripSize);
						offset += result;
					}
				}
				else
				{
					for (int i = 0; i < m_numberOfStrips; ++i)
					{
						result = TIFFReadEncodedStrip(m_tiff, i, m_data + offset, m_stripSize);
						offset += result;
					}
					IppStatus status = ippiCopy_8u_C1R
					(
						m_data,
						image->Width(),
						image->Data(),
						image->WidthBytes(),
						{ image->Width(), image->Height() }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_8u_C1R failed!");
				}

			}

			void Close()
			{
				if (m_tiff != nullptr)
				{
					TIFFClose(m_tiff);
					m_tiff = nullptr;
				}
				if (m_data != nullptr)
				{
					ippsFree(m_data);
					m_data = nullptr;
				}
			}

		private:
			Ipp8u *m_data;
		};


		/// \brief CTifReader16u1c class.
		class CTifReader16u1c final : public CTifReader
		{
		public:
			CTifReader16u1c() 
				: CTifReader()
				, m_data(nullptr)
			{}


			~CTifReader16u1c()
			{
				Close();
			}


			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_tiff = TIFFOpen(filePath.c_str(), "r");
				ENSURE_THROW_MSG(m_tiff != nullptr, "Open tiff file failed!");

// 				uint16 compression;
// 				TIFFGetField(m_tiff, TIFFTAG_COMPRESSION, &compression);
// 				ENSURE_THROW_MSG(compression == COMPRESSION_NONE, "Unsupported tiff format!");

				uint16 photoMetric;
				TIFFGetField(m_tiff, TIFFTAG_PHOTOMETRIC, &photoMetric);
				ENSURE_THROW_MSG(photoMetric == PHOTOMETRIC_MINISBLACK, "Unsupported tiff format!");

// 				uint16 fillOrder;
// 				TIFFGetField(m_tiff, TIFFTAG_FILLORDER, &fillOrder);
// 				ENSURE_THROW_MSG(fillOrder == FILLORDER_MSB2LSB, "Unsupported tiff format!");

				m_stripSize = TIFFStripSize(m_tiff);
				m_numberOfStrips = TIFFNumberOfStrips(m_tiff);

				FileInfo fileInfo;
				TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &fileInfo.imageInfo.channel);
				ENSURE_THROW_MSG(fileInfo.imageInfo.channel == 1, "Unsupported tiff format!");

				TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &fileInfo.imageInfo.bitDepth);
				ENSURE_THROW_MSG(fileInfo.imageInfo.bitDepth == 16, "Unsupported tiff format!");

// 				TIFFGetField(m_tiff, TIFFTAG_IMAGEDEPTH, &imageInfo.bitDepthReal);
// 				if (imageInfo.bitDepthReal == 0)
// 				{
// 					imageInfo.bitDepthReal = 16;
// 				}
// 				else
// 				{
// 					ENSURE_THROW_MSG((imageInfo.bitDepthReal == 10) || (imageInfo.bitDepthReal == 12) || (imageInfo.bitDepthReal == 16), "Unsupported tiff format!");
// 				}

				TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &fileInfo.imageInfo.size.width);
				TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &fileInfo.imageInfo.size.height);
				if (fileInfo.imageInfo.size.width % 64 != 0)
				{
					m_data = ippsMalloc_16u(fileInfo.imageInfo.size.width * fileInfo.imageInfo.size.height);
				}
				//fileInfo.tag = FT_PICTURE;
				fileInfo.imageCounts = 1;

				return fileInfo;
			}


			void Read(std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error Image Format");
				auto image = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(anyImage);
				auto data = reinterpret_cast<unsigned char *>(image->Data());
				tsize_t offset = 0;
				tsize_t result = 0;
				if (image->Width() * sizeof(unsigned short) == image->WidthBytes())
				{
					for (int i = 0; i < m_numberOfStrips; ++i)
					{
						result = TIFFReadEncodedStrip(m_tiff, i, data + offset, m_stripSize);
						offset += result;
					}
				}
				else
				{
					for (int i = 0; i < m_numberOfStrips; ++i)
					{
						result = TIFFReadEncodedStrip(m_tiff, i, m_data + offset, m_stripSize);
						offset += result;
					}
					IppStatus status = ippiCopy_16u_C1R
					(
						m_data,
						image->Width() * sizeof(Ipp16u),
						image->Data(),
						image->WidthBytes(),
						{ image->Width(), image->Height() }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_16u_C1R failed!");
				}				
			}

			void Close()
			{
				if (m_tiff != nullptr)
				{
					TIFFClose(m_tiff);
					m_tiff = nullptr;
				}
				if (m_data != nullptr)
				{
					ippsFree(m_data);
					m_data = nullptr;
				}
			}

		private:
			Ipp16u * m_data;
		};


		/// \brief CTifReader16u1c class.
		class CTiffReader32f1c final : public CTifReader
		{
		public:
			CTiffReader32f1c() 
				: CTifReader() 
				, m_data(nullptr)
			{};


			~CTiffReader32f1c()
			{
				Close();
			}


			FileInfo Open(const std::string &filePath) override
			{
				Close();

				m_tiff = TIFFOpen(filePath.c_str(), "r");
				ENSURE_THROW_MSG(m_tiff != nullptr, "Open tiff file failed!");

				uint16 compression;
				TIFFGetField(m_tiff, TIFFTAG_COMPRESSION, &compression);
				ENSURE_THROW_MSG(compression == COMPRESSION_NONE, "Unsupported tiff format!");

				uint16 photoMetric;
				TIFFGetField(m_tiff, TIFFTAG_PHOTOMETRIC, &photoMetric);
				ENSURE_THROW_MSG(photoMetric == PHOTOMETRIC_MINISBLACK, "Unsupported tiff format!");

// 				uint16 orientation;
// 				TIFFGetField(m_tiff, TIFFTAG_ORIENTATION, &orientation);
// 				ENSURE_THROW_MSG(orientation == ORIENTATION_TOPLEFT, "Unsupported tiff format!");

// 				uint16 fillOrder;
// 				TIFFGetField(m_tiff, TIFFTAG_FILLORDER, &fillOrder);
// 				ENSURE_THROW_MSG(fillOrder == FILLORDER_MSB2LSB, "Unsupported tiff format!");

				m_stripSize = TIFFStripSize(m_tiff);
				m_numberOfStrips = TIFFNumberOfStrips(m_tiff);

				FileInfo fileInfo;
				TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &fileInfo.imageInfo.channel);
				ENSURE_THROW_MSG(fileInfo.imageInfo.channel == 1, "Unsupported tiff format!");

				TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &fileInfo.imageInfo.bitDepth);
				ENSURE_THROW_MSG(fileInfo.imageInfo.bitDepth == 32, "Unsupported tiff format!");

// 				TIFFGetField(m_tiff, TIFFTAG_IMAGEDEPTH, &imageInfo.bitDepthReal);
// 				if (imageInfo.bitDepthReal == 0)
// 				{
// 					imageInfo.bitDepthReal = 8;
// 				}
// 				else
// 				{
// 					ENSURE_THROW_MSG(imageInfo.bitDepthReal == 8, "Unsupported tiff format!");
// 				}

				TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &fileInfo.imageInfo.size.width);
				TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &fileInfo.imageInfo.size.height);
				if (fileInfo.imageInfo.size.width % 64 != 0)
				{
					m_data = ippsMalloc_32f(fileInfo.imageInfo.size.width * fileInfo.imageInfo.size.height);
				}
				fileInfo.imageCounts;

				return fileInfo;
			}


			void Read(std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error Image Format");
				auto image = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(anyImage);
				auto data = reinterpret_cast<unsigned char *>(image->Data());
				tsize_t offset = 0;
				tsize_t result = 0;
				if (image->Width() * sizeof(float) == image->WidthBytes())
				{
					for (int i = 0; i < m_numberOfStrips; ++i)
					{
						result = TIFFReadEncodedStrip(m_tiff, i, data + offset, m_stripSize);
						offset += result;
					}
				}
				else
				{
					for (int i = 0; i < m_numberOfStrips; ++i)
					{
						result = TIFFReadEncodedStrip(m_tiff, i, m_data + offset, m_stripSize);
						offset += result;
					}
					IppStatus status = ippiCopy_32f_C1R
					(
						m_data,
						image->Width() * sizeof(Ipp32f),
						image->Data(),
						image->WidthBytes(),
						{ image->Width(), image->Height() }
					);
					ENSURE_THROW_MSG(status == ippStsNoErr, "ippiCopy_32f_C1R failed!");
				}
				
			}

			void Close()
			{
				if (m_tiff != nullptr)
				{
					TIFFClose(m_tiff);
					m_tiff = nullptr;
				}
				if (m_data != nullptr)
				{
					ippsFree(m_data);
					m_data = nullptr;
				}
			}

		private:
			Ipp32f * m_data;
		};


		/// \brief CTifWriter class.
		class CTifWriter : public CPictureWriter, public CTif
		{
		public:
			CTifWriter()
				: CPictureWriter()
				, CTif()
			{}

			~CTifWriter() override = default;

			void Write(const std::string &, std::any) {};
		};


		/// \brief CTifWriter8u1c class.
		class CTifWriter8u1c final : public CTifWriter
		{
		public:
			CTifWriter8u1c() 
				: CTifWriter()				
			{}


			~CTifWriter8u1c() override
			{}

			/// \brief Write tif image. 8bit
			/// \param[in] filePath the path to save tif
			/// \param[in] anyImage the image must be std::shared_ptr<CImage8u1cIPPI>
			void Write(const std::string &filePath, std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage8u1cIPPI>), "Error Image Format");
				TIFF *tiff = TIFFOpen(filePath.c_str(), "w");
				ENSURE_THROW_MSG(tiff != nullptr, "Create tiff file failed!");
				
				auto image = std::any_cast<std::shared_ptr<CImage8u1cIPPI>>(anyImage);
				TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, image->Width());
				TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, image->Height());
				TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, image->BitDepth());
				TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, image->Channel());
				//TIFFSetField(m_tiff, TIFFTAG_IMAGEDEPTH, imageInfo.bitDepthReal);
				TIFFSetField(tiff, TIFFTAG_ROWSPERSTRIP, image->Height());
				TIFFSetField(tiff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
				TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
				TIFFSetField(tiff, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
				TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
				TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
				TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
				TIFFSetField(tiff, TIFFTAG_XRESOLUTION, 96);
				TIFFSetField(tiff, TIFFTAG_YRESOLUTION, 96);

				auto data = image->Data();
				for (int i = 0; i < image->Height(); ++i)
				{
					TIFFWriteEncodedStrip(tiff, i, data + image->WidthBytes() * i, image->Width());
				}

				TIFFClose(tiff);
				tiff = nullptr;
			}
		};


		/// \brief CTifWriter16u1c class.
		class CTifWriter16u1c final : public CTifWriter
		{
		public:
			CTifWriter16u1c() 
				: CTifWriter()
			{}


			~CTifWriter16u1c() override
			{}

			
			void Write(const std::string &filePath, std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage16u1cIPPI>), "Error image type");
				TIFF *tiff = TIFFOpen(filePath.c_str(), "w");
				ENSURE_THROW_MSG(tiff != nullptr, "Create tiff file failed!");

				auto image = std::any_cast<std::shared_ptr<CImage16u1cIPPI>>(anyImage);
				TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, image->Width());
				TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, image->Height());
				TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, image->BitDepth());
				//TIFFSetField(m_tiff, TIFFTAG_IMAGEDEPTH, imageInfo.bitDepthReal);
				TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, image->Channel());
				TIFFSetField(tiff, TIFFTAG_ROWSPERSTRIP, image->Height());
				TIFFSetField(tiff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
				TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
				TIFFSetField(tiff, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
				TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
				TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
				TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
				TIFFSetField(tiff, TIFFTAG_XRESOLUTION, 96);
				TIFFSetField(tiff, TIFFTAG_YRESOLUTION, 96);
				auto data = image->Data();
				for (int i = 0; i < image->Height(); ++i)
				{
					TIFFWriteEncodedStrip(tiff, i, data + image->WidthBytes() * i, image->Width());
				}
				

				TIFFClose(tiff);
				tiff = nullptr;
			}	
		};


		/// \brief CTWTif32f1c class.
		class CTifWriter32f1c final : public CTifWriter
		{
		public:
			CTifWriter32f1c() 
				: CTifWriter()
			{}


			~CTifWriter32f1c() override
			{}


			void Write(const std::string &filePath, std::any anyImage) override
			{
				ASSERT_LOG(anyImage.type() == typeid(std::shared_ptr<CImage32f1cIPPI>), "Error image type");
				TIFF *tiff = TIFFOpen(filePath.c_str(), "w");
				ENSURE_THROW_MSG(tiff != nullptr, "Create tiff file failed!");

				auto image = std::any_cast<std::shared_ptr<CImage32f1cIPPI>>(anyImage);
				TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, image->Width());
				TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, image->Height());
				TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, image->BitDepth());
				//TIFFSetField(m_tiff, TIFFTAG_IMAGEDEPTH, imageInfo.bitDepthReal);
				TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, image->Channel());
				TIFFSetField(tiff, TIFFTAG_ROWSPERSTRIP, image->Height());
				TIFFSetField(tiff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
				TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
				TIFFSetField(tiff, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
				TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
				TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
				TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
				TIFFSetField(tiff, TIFFTAG_XRESOLUTION, 96);
				TIFFSetField(tiff, TIFFTAG_YRESOLUTION, 96);

				auto data = image->Data();
				for (int i = 0; i < image->Height(); ++i)
				{
					TIFFWriteEncodedStrip(tiff, i, data + image->WidthBytes() * i, image->Width());
				}

				TIFFClose(tiff);
				tiff = nullptr;
			}
		};
	}
}

#endif













