/**
* \file ImageBadPixelCorrection.hpp
* \brief Image bad pixels correction.
*
* detail description
*
* \author mbq
* \email
* \version 1.0.0.0
* \date 2017.07.19
*/
#ifndef _IMAGE_BAD_PIXEL_CORRECTION2_H
#define _IMAGE_BAD_PIXEL_CORRECTION2_H


// System Class Includes
#include <iostream>
#include <vector>
#include <string>


// My Class Includes
#include "ImageAlgorithmBase.hpp"
#include "../ImageOperator/ImageSetConstant.hpp"
#include "../ImageOperator/ImageConvert.hpp"
#include "../ImageOperator/ImageCopy.hpp"


namespace ELDER
{
	namespace ALGORITHM
	{
		struct DECorrectionPixelInfo
		{
			IppiPoint point;
			std::vector<UINT> goodPixels;
		};

		
		/// \brief CBadPixelCorrection
		class CBadPixelCorrection : public IPixelCorrection
		{

		public:
			CBadPixelCorrection()
				: IPixelCorrection(),
				m_imageBuf(nullptr),
				m_imageWidth(0),
				m_imageHeight(0),
				m_offsetX(0),
				m_offsetY(0),
				m_binning(1),
				m_bufStep(0)
			{
				Clear();
				m_badPixelsFactoryImage = std::make_shared<ELDER::CImage8u1cIPPI>();
			}


			virtual ~CBadPixelCorrection() override
			{
				Clear();
			}

			void Initialize(const int offsetX, const int offsetY, int sizeX, int sizeY, int binning)
			{
				m_binning = binning;
				sizeX /= m_binning;
				sizeY /= m_binning;
				m_offsetX = offsetX / m_binning;
				m_offsetY = offsetY / m_binning;

				m_badPixelsFactoryImage->Initialize(sizeX, sizeY, nullptr);
				ELDER::OPERATOR::CImageSetConstant<ELDER::OPERATOR::CSetConstant8u1c>::SetConstant(m_badPixelsFactoryImage, 1);

				m_imageBuf = m_badPixelsFactoryImage->Data();
				ASSERT_LOG(m_imageBuf != NULL, "m_imageBuf ptr is NULL");
				m_imageWidth = m_badPixelsFactoryImage->Width();
				ASSERT_LOG(m_imageWidth != 0, "m_imageWidth = 0!");
				m_imageHeight = m_badPixelsFactoryImage->Height();
				ASSERT_LOG(m_imageHeight != 0, "m_imageHeight = 0!");

				AnalyzeDefect();
				AnalyzeGoodPixels();
			}

			
			virtual bool Apply(std::any &&, std::any &&, ImageInfo &) {}

			
			template<typename T>
			void Process(T *image)
			{
				ASSERT_LOG(image != nullptr, "image is nullptr");

				FixPointBadPixels(image);
				FixRowAndColBadPixels(image);
				FixRowsAndColsBadPixels(image);
			}


			void SetPointDefect(const std::vector<Point> points)
			{
				m_points.clear();
				m_points = points;
			}

			
			void SetRowDefect(const std::vector<int> row)
			{
				m_row.clear();
				m_row = row;
			}

			
			void SetColDefect(const std::vector<int> col)
			{
				m_col.clear();
				m_col = col;
			}

			
			void SetRowsDefect(const std::vector<Rows> rows)
			{
				m_rows.clear();
				m_rows = rows;
			}


			void SetColsDefect(const std::vector<Columns> cols)
			{
				m_cols.clear();
				m_cols = cols;
			}


		private:

			void AnalyzeDefect()
			{
				MatchROI();
				MatchPointDefect();
				MatchRowAndColDefect();
				MatchRowsAndColsDefect();
			}


			void MatchROI()
			{
				//Erase point which is out of range.
				for (auto p = m_points.begin(); p != m_points.end(); ++p)
				{
					p->x /= m_binning;
					p->y /= m_binning;

					if ((p->x < m_offsetX) || (p->x >(m_offsetX + m_imageWidth)) || (p->y < m_offsetY) || (p->y >(m_offsetY + m_imageHeight)))
					{
						m_points.erase(p);
						--p;
					}
					else
					{
						p->x -= m_offsetX;
						p->y -= m_offsetY;
					}
				}

				//Erase row which is out of range.
				for (auto row = m_row.begin(); row != m_row.end(); ++row)
				{
					*row /= m_binning;
					if ((*row < m_offsetY) || (*row >(m_offsetY + m_imageHeight)))
					{
						m_row.erase(row);
						--row;
					}
					else
					{
						*row -= m_offsetY;
					}
				}

				//Erase col which is out of range.
				for (auto col = m_col.begin(); col != m_col.end(); ++col)
				{
					*col /= m_binning;
					if ((*col < m_offsetX) || (*col >(m_offsetX + m_imageWidth)))
					{
						m_col.erase(col);
						--col;
					}
					else
					{
						*col -= m_offsetX;
					}
				}

				//Erase rows which is out of range.
				for (auto rows = m_rows.begin(); rows != m_rows.end(); ++rows)
				{
					rows->startRow /= m_binning;
					rows->endRow /= m_binning;

					if (rows->startRow > rows->endRow)
					{
						int temp = rows->startRow;
						rows->startRow = rows->endRow;
						rows->endRow = temp;
					}

					if (rows->startRow < m_offsetY)
					{
						rows->startRow = 0;
					}
					else if (rows->startRow >(m_offsetY + m_imageHeight))
					{
						rows->startRow = m_imageHeight - 1;
					}
					else
					{
						rows->startRow -= m_offsetY;
					}

					if (rows->endRow < m_offsetY)
					{
						rows->endRow = 0;
					}
					else if (rows->endRow >(m_offsetY + m_imageHeight))
					{
						rows->endRow = m_imageHeight - 1;
					}
					else
					{
						rows->endRow -= m_offsetY;
					}
				}

				//Erase cols which is out of range.
				for (auto cols = m_cols.begin(); cols != m_cols.end(); ++cols)
				{
					cols->startCol /= m_binning;
					cols->endCol /= m_binning;
					if (cols->startCol > cols->endCol)
					{
						int temp = cols->startCol;
						cols->startCol = cols->endCol;
						cols->endCol = temp;
					}

					if (cols->startCol < m_offsetX)
					{
						cols->startCol = 0;
					}
					else if (cols->startCol >(m_offsetX + m_imageWidth))
					{
						cols->startCol = m_imageWidth - 1;
					}
					else
					{
						cols->startCol -= m_offsetX;
					}

					if (cols->endCol < m_offsetX)
					{
						cols->endCol = 0;
					}
					else if (cols->endCol >(m_offsetX + m_imageWidth))
					{
						cols->endCol = m_imageWidth - 1;
					}
					else
					{
						cols->endCol -= m_offsetX;
					}
				}
			}


			void MatchPointDefect()
			{
				for (const auto &p : m_points)
				{
					m_imageBuf[p.x + p.y * m_imageWidth] = 0;
				}
			}


			void MatchRowAndColDefect()
			{
				for (const auto &row : m_row)
				{
					for (int i = 0; i < m_imageWidth; i++)
					{
						m_imageBuf[i + row * m_imageWidth] = 0;
					}
				}

				for (const auto &col : m_col)
				{
					for (int i = 0; i < m_imageHeight; i++)
					{
						m_imageBuf[col + i * m_imageWidth] = 0;
					}
				}
			}


			void MatchRowsAndColsDefect()
			{
				if (!m_rows.empty())
				{
					for (const auto &rows : m_rows)
					{
						for (int j = rows.startRow; j <= rows.endRow; ++j)
						{
							for (int i = 0; i < m_imageWidth; ++i)
							{
								m_imageBuf[i + j * m_imageWidth] = 0;
							}
						}
					}
				}

				if (!m_cols.empty())
				{
					for (const auto &cols : m_cols)
					{
						for (int j = 0; j < m_imageHeight; ++j)
						{
							for (int i = cols.startCol; i <= cols.endCol; ++i)
							{
								m_imageBuf[i + j * m_imageWidth] = 0;
							}
						}
					}
				}
			}


			void AnalyzeGoodPixels()
			{
				FindPointGoodPixels();
				FindRowAndColGoodPixels();
				FindRowsAndColsGoodPixels();
			}


			void FindPointGoodPixels()
			{
				m_pointPixelInfo.clear();
				for (const auto &p : m_points)
				{
					m_pointPixelInfo.push_back(FindGoodPixels(p.x, p.y));
				}
			}


			void FindRowAndColGoodPixels()
			{
				m_rowPixelInfo.clear();
				for (const auto &row : m_row)
				{
					for (int i = 0; i < m_imageWidth; ++i)
					{
						m_rowPixelInfo.push_back(FindGoodPixels(i, row));
					}
				}

				m_colPixelInfo.clear();
				for (const auto &col : m_col)
				{
					for (int i = 0; i < m_imageHeight; ++i)
					{
						m_colPixelInfo.push_back(FindGoodPixels(col, i));
					}
				}
			}


			void FindRowsAndColsGoodPixels()
			{
				m_rowsPixelInfo.clear();
				for (const auto &rows : m_rows)
				{
					for (int x = 0; x < m_imageWidth; ++x)
					{
						m_rowsPixelInfo.push_back(FindGoodPixels(x, rows.startRow));
						m_rowsPixelInfo.push_back(FindGoodPixels(x, rows.endRow));
					}
				}

				m_colsPixelInfo.clear();
				for (const auto &cols : m_cols)
				{
					for (int y = 0; y < m_imageHeight; ++y)
					{
						m_colsPixelInfo.push_back(FindGoodPixels(cols.startCol, y));
						m_colsPixelInfo.push_back(FindGoodPixels(cols.endCol, y));
					}
				}
			}


			DECorrectionPixelInfo FindGoodPixels(const int x, const int y)
			{
				int minX = (x > 0) ? x - 1 : 0;
				int maxX = (x + 1 < m_imageWidth) ? x + 1 : m_imageWidth - 1;
				int minY = (y - 1 > 0) ? y - 1 : 0;
				int maxY = (y + 1 < m_imageHeight) ? y + 1 : m_imageHeight - 1;
				DECorrectionPixelInfo info;
				info.point.x = x;
				info.point.y = y;
				for (int i = minY; i <= maxY; i++)
				{
					for (int j = minX; j <= maxX; j++)
					{
						if (1 == m_imageBuf[i * m_imageWidth + j])
						{
							info.goodPixels.push_back(i * m_imageWidth + j);
						}
					}
				}
				return info;
			}


			template<typename T>
			void FixPointBadPixels(T *image)
			{
				for (const auto &pointPixelInfo : m_pointPixelInfo)
				{
					FixBadPixel(pointPixelInfo, image);
				}
			}


			template<typename T>
			void FixRowAndColBadPixels(T *image)
			{
				for (const auto &rowPixelInfo : m_rowPixelInfo)
				{
					FixBadPixel(rowPixelInfo, image);
				}

				for (const auto &colPixelInfo : m_colPixelInfo)
				{
					FixBadPixel(colPixelInfo, image);
				}
			}


			template<typename T>
			void FixRowsAndColsBadPixels(T *image)
			{
				for (const auto &rowsPixelInfo : m_rowsPixelInfo)
				{
					FixBadPixel(rowsPixelInfo, image);
				}

				for (const auto &colsPixelInfo : m_colsPixelInfo)
				{
					FixBadPixel(colsPixelInfo, image);
				}
				//
				int lengthToStart = 0;
				int lengthToEnd = 0;
				int lengthHeight = 0;
				float proportionToStart = 0.0f;
				float proportionToEnd = 0.0f;
				for (const auto &rows : m_rows)
				{
					for (int y = rows.startRow + 1; y < rows.endRow; ++y)
					{
						lengthToStart = y - rows.startRow;
						lengthToEnd = rows.endRow - y;
						lengthHeight = rows.endRow - rows.startRow;
						proportionToStart = (float)lengthToStart / lengthHeight;
						proportionToEnd = (float)lengthToEnd / lengthHeight;
						for (int x = 0; x < m_imageWidth; ++x)
						{
							image[x + y * m_imageWidth] = (T)(image[x + rows.startRow * m_imageWidth] * proportionToEnd)
								+ (T)(image[x + rows.endRow * m_imageWidth] * proportionToStart);
						}
					}
				}

				int lengthWidth = 0;
				for (const auto &cols : m_cols)
				{
					for (int x = cols.startCol + 1; x < cols.endCol; ++x)
					{
						lengthToStart = x - cols.startCol;
						lengthToEnd = cols.endCol - x;
						lengthWidth = cols.endCol - cols.startCol;
						proportionToStart = (float)lengthToStart / lengthWidth;
						proportionToEnd = (float)lengthToEnd / lengthWidth;
						for (int y = 0; y < m_imageHeight; ++y)
						{
							auto t1 = (T)(image[cols.startCol + y * m_imageWidth] * proportionToEnd);
							auto t2 = (T)(image[cols.endCol + y * m_imageWidth] * proportionToStart);

							image[x + y * m_imageWidth] = (T)(image[cols.startCol + y * m_imageWidth] * proportionToEnd)
								+ (T)(image[cols.endCol + y * m_imageWidth] * proportionToStart);
						}
					}
				}
			}


			template<typename T>
			void FixBadPixel(const DECorrectionPixelInfo pixelInfo, T *image)
			{
				if (pixelInfo.goodPixels.size() > 0)
				{
					float temp = 0.0;
					for (const auto &goodPixelIndex : pixelInfo.goodPixels)
					{
						temp += image[goodPixelIndex];
					}
					image[pixelInfo.point.x + pixelInfo.point.y * m_imageWidth] = (T)(temp / pixelInfo.goodPixels.size());
				}
			}


			void Clear()
			{
				m_points.clear();
				m_points.swap(std::vector<Point>());

				m_row.clear();
				m_row.swap(std::vector<int>());

				m_col.clear();
				m_col.swap(std::vector<int>());

				m_rows.clear();
				m_rows.swap(std::vector<Rows>());

				m_cols.clear();
				m_cols.swap(std::vector<Columns>());

				m_pointPixelInfo.clear();
				m_pointPixelInfo.swap(std::vector<DECorrectionPixelInfo>());

				m_rowPixelInfo.clear();
				m_rowPixelInfo.swap(std::vector<DECorrectionPixelInfo>());

				m_colPixelInfo.clear();
				m_colPixelInfo.swap(std::vector<DECorrectionPixelInfo>());

				m_rowsPixelInfo.clear();
				m_rowsPixelInfo.swap(std::vector<DECorrectionPixelInfo>());

				m_colsPixelInfo.clear();
				m_colsPixelInfo.swap(std::vector<DECorrectionPixelInfo>());
			}

		protected:

			std::shared_ptr<ELDER::CImage8u1cIPPI> m_badPixelsFactoryImage;
			unsigned char *m_imageBuf;
			int m_imageWidth;
			int m_imageHeight;
			int m_offsetX;
			int m_offsetY;
			int m_binning;
			int m_bufStep;
			
			std::vector<Point>				m_points;
			std::vector<int>					m_row;
			std::vector<int>					m_col;
			std::vector<Rows>					m_rows;
			std::vector<Columns>				m_cols;
			std::vector<DECorrectionPixelInfo>  m_pointPixelInfo;
			std::vector<DECorrectionPixelInfo>  m_rowPixelInfo;
			std::vector<DECorrectionPixelInfo>  m_colPixelInfo;
			std::vector<DECorrectionPixelInfo>  m_rowsPixelInfo;
			std::vector<DECorrectionPixelInfo>  m_colsPixelInfo;
			
		};


		/// \brief CBadPixelCorrection8u1c
		class CBadPixelCorrection8u1c : public CBadPixelCorrection
		{
		public:

			CBadPixelCorrection8u1c()
				: CBadPixelCorrection()
			{}


			~CBadPixelCorrection8u1c()
			{}

			
			void Initialize(int offsetX, int offsetY, int sizeX, int sizeY, int bin)
			{
				CBadPixelCorrection::Initialize(offsetX, offsetY, sizeX, sizeY, bin);
			}

			
			bool Apply(std::any &&imageIn, std::any &&imageOut, ImageInfo &outImageInfo) override
			{
				ASSERT_LOG(imageIn.Is<std::shared_ptr<CImage8u1cIPPI> >(), "Error imageIn Format");
				ASSERT_LOG(imageOut.Is<std::shared_ptr<CImage8u1cIPPI>>(), "Error imageOut Format");
				auto src = imageIn.AnyCast<std::shared_ptr<CImage8u1cIPPI>>();
				ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
				auto dst = imageOut.AnyCast<std::shared_ptr<CImage8u1cIPPI>>();
				ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

				ELDER::OPERATOR::CImageCopy<ELDER::OPERATOR::CCopy8u1c>::Copy(dst, src);
				Process(dst->Data());

				return true;
			}
		};


		/// \brief CBadPixelCorrection16u1c
		class CBadPixelCorrection16u1c : public CBadPixelCorrection
		{
		public:

			CBadPixelCorrection16u1c()
				: CBadPixelCorrection()
			{}


			~CBadPixelCorrection16u1c()
			{}


			void Initialize(int offsetX, int offsetY, int sizeX, int sizeY, int bin)
			{
				CBadPixelCorrection::Initialize(offsetX, offsetY, sizeX, sizeY, bin);
			}


			bool Apply(std::any &&imageIn, std::any &&imageOut, ImageInfo &outImageInfo) override
			{
				ASSERT_LOG(imageIn.Is<std::shared_ptr<CImage16u1cIPPI> >(), "Error imageIn Format");
				ASSERT_LOG(imageOut.Is<std::shared_ptr<CImage16u1cIPPI>>(), "Error imageOut Format");
				auto src = imageIn.AnyCast<std::shared_ptr<CImage16u1cIPPI>>();
				ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
				auto dst = imageOut.AnyCast<std::shared_ptr<CImage16u1cIPPI>>();
				ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

				ELDER::OPERATOR::CImageCopy<ELDER::OPERATOR::CCopy16u1c>::Copy(dst, src);
				Process(dst->Data());
			}			
		};

		/// \brief CBadPixelCorrection32f1c
		class CBadPixelCorrection32f1c : public CBadPixelCorrection
		{
		public:

			CBadPixelCorrection32f1c()
				: CBadPixelCorrection()
			{}


			~CBadPixelCorrection32f1c()
			{}


			void Initialize(int offsetX, int offsetY, int sizeX, int sizeY, int bin)
			{
				CBadPixelCorrection::Initialize(offsetX, offsetY, sizeX, sizeY, bin);
			}


			bool Apply(std::any &&imageIn, std::any &&imageOut, ImageInfo &outImageInfo) override
			{
				ASSERT_LOG(imageIn.Is<std::shared_ptr<CImage32f1cIPPI> >(), "Error imageIn Format");
				ASSERT_LOG(imageOut.Is<std::shared_ptr<CImage32f1cIPPI>>(), "Error imageOut Format");
				auto src = imageIn.AnyCast<std::shared_ptr<CImage32f1cIPPI>>();
				ASSERT_LOG(src != nullptr, "imageIn ptr is NULL");
				auto dst = imageOut.AnyCast<std::shared_ptr<CImage32f1cIPPI>>();
				ASSERT_LOG(dst != nullptr, "imageOut ptr is NULL");

				ELDER::OPERATOR::CImageCopy<ELDER::OPERATOR::CCopy32f1c>::Copy(dst, src);
				Process(dst->Data());

				return true;
			}			
		};
	}
}



#endif