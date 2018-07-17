/**
* \file Avi.hpp
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.07.14
*/
#ifndef _FILE_AVI_H
#define _FILE_AVI_H


// ThirdParty Includes
#include "opencv/include/opencv2/core/core.hpp"
#include "opencv/include/opencv2/opencv.hpp"


// My Class Includes
#include "Video.hpp"


namespace ELDER
{
	/// \brief About file interface.
	namespace FILE
	{

		/// Define default frame rate.
		constexpr double DEFAULT_FPS = 20.0;


		/// \brief Avi format file writer class.
		class CAviWriter : public CVideoWriter
		{
		public:
			/// construct.
			CAviWriter() : CVideoWriter() {};

			/// destruct.
			~CAviWriter() override = default;

			/// Create file by file information.
			/// \param[in] FileInfo File information data struct.
			void Create(const std::string &, const VideoInfo &) override {};

			/// Write data into file.
			/// \param[in] CAny.
			void Write(CAny) override {};

			/// Close the opened file.
			void Close() override
			{
				if (m_videoWriter.isOpened())
				{
					m_videoWriter.release();
				}
			}

		protected:
			cv::VideoWriter m_videoWriter;

		};


		/// \brief Avi writer for 8 bit unsigned 1 channel.
		class CAviWriter8u1c final : public CAviWriter
		{
		public:
			CAviWriter8u1c() : CAviWriter() {}


			~CAviWriter8u1c() override
			{
				Close();
			}


			void Create(const std::string &filePath, const VideoInfo &videoInfo) override
			{
				Close();
				m_videoWriter.open(filePath, CV_FOURCC('D', 'I', 'V', '3'), DEFAULT_FPS, { videoInfo.frameSize.width, videoInfo.frameSize.height }, true);
			}


			void Write(CAny anyImage) override
			{
				ASSERT_LOG(anyImage.Is<std::shared_ptr<CImage8u1cIPPI>>(), "Error image type");
				auto image = anyImage.AnyCast<std::shared_ptr<CImage8u1cIPPI>>();				
				//cv::Mat mat(image->Height(), image->Width(), CV_8UC1, image->Data());
				//IplImage *imageSrc = cvCreateImage(cvSize(image->Width(), image->Height()), 8, 1);
				//IplImage *imageDst = cvCreateImage(cvSize(image->Width(), image->Height()), 8, 3);
				cv::Mat matSrc(image->Height(), image->Width(), CV_8UC1, image->Data());
				cv::Mat matDst(image->Height(), image->Width(), CV_8UC3);
				//imageSrc->imageData = (char*)image->Data();
				cvtColor(matSrc, matDst, CV_GRAY2RGB);
				//cvCvtColor(matSrc, matDst, CV_GRAY2RGB);
				//cv::Mat mat(image->Height(), image->Width(), CV_8UC3, imageDst->imageData);
				m_videoWriter.write(matDst);
			}
		};


		/// \brief Avi writer for 16 bit unsigned 1 channel.
		class CAviWriter16u1c final : public CAviWriter
		{
		public:
			CAviWriter16u1c() : CAviWriter() {}


			~CAviWriter16u1c() override
			{
				Close();
			}

			
			void Create(const std::string &filePath, const VideoInfo &videoInfo) override
			{
				Close();
				m_videoWriter.open(filePath, CV_FOURCC('I', 'Y', 'U', 'V'), DEFAULT_FPS, { videoInfo.frameSize.width, videoInfo.frameSize.height }, true);
			}


			void Write(CAny anyImage) override
			{
				ASSERT_LOG(anyImage.Is<std::shared_ptr<CImage16u1cIPPI>>(), "Error image type");
				auto image = anyImage.AnyCast<std::shared_ptr<CImage16u1cIPPI>>();
				cv::Mat mat(image->Height(), image->Width(), CV_8UC1, image->Data());
// 				IplImage *imageSrc = cvCreateImage(cvSize(image->Width(), image->Height()), 8, 1);
// 				IplImage *imageDst = cvCreateImage(cvSize(image->Width(), image->Height()), 8, 3);
// 				imageSrc->imageData = (char*)image->Data();
// 				cvCvtColor(imageSrc, imageDst, CV_GRAY2RGB);
// 				cv::Mat mat(image->Height(), image->Width(), CV_8UC3, imageDst->imageData);
				m_videoWriter.write(mat);
			}
		};
	}
}

#endif













