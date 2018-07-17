/**
* \file Structs.h
* \brief brief description
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2018.02.25
*/
#ifndef _STRUCTS_H
#define _STRUCTS_H


namespace ELDER
{
	/// \brief Rows class stand for row range.
	struct Rows
	{
		int startRow;          ///< the start row position.
		int endRow;            ///< the end row position.
	};

	/// \brief Columns class stand for column range.
	struct Columns
	{
		int startCol;          ///< the start column position.
		int endCol;            ///< the end column position.
	};

	/// \brief Point class.
	struct Point
	{
		/// construct.
		Point()
			: x(0)
			, y(0)
		{}

		/// construct.
		/// \param[in] px The x value of point.
		/// \param[in] py The y value of point.
		Point(int px, int py)
			: x(px)
			, y(py)
		{}

		/// copy construct.
		/// \param[in] p The point value. 
		Point(const Point &p)
			: x(p.x)
			, y(p.y)
		{}

		int x;                  ///< The x value of point.
		int y;                  ///< The y value of point.
	};

	/// \brief Size data struct.
	struct Size
	{
		/// construct.
		Size()
			: width(0)
			, height(0)
		{}

		/// construct.
		/// \param[in] w The width value of size.
		/// \param[in] h The height value of size.
		Size(int w, int h)
			: width(w)
			, height(h)
		{}

		/// copy construct.
		/// \param[s] The size value.
		Size(const Size &s)
			: width(s.width)
			, height(s.height)
		{}

		bool operator==(const Size &s) const
		{
			return (this->width == s.width && this->height == s.height);
		}

		bool operator!=(const Size &s)
		{
			return (this->width != s.width || this->height != s.height);
		}

		bool operator<(const Size &s) const
		{
			if (this->width < s.width)
			{
				return true;
			}
			else if (this->width == s.width && this->height < s.height)
			{
				return true;
			}

			return false;
		}

		bool operator>(const Size &s) const
		{
			return !((*this < s) || (*this == s));
		}

		int width;              ///< the width value of size.
		int height;             ///< the height value of size.
	};

	/// \brief Rect class.
	struct Rect
	{
		/// construct.
		Rect()
			: point()
			, size()
		{}

		/// construct.
		/// \param[in] r Rect value.
		Rect(const Rect &r)
			: point(r.point)
			, size(r.size)
		{}

		/// construct.
		/// \param[in] p The start point.
		/// \param[in] s The rect size.
		Rect(const Point &p, const Size &s)
			: point(p)
			, size(s)
		{}

		/// construct.
		/// \param[in] x The x value of start point.
		/// \param[in] y The y value of start point.
		/// \param[in] w The width value.
		/// \param[in] h The height value.
		Rect(int x, int y, int w, int h)
			: point(x, y)
			, size(w, h)
		{}


		bool operator==(const Rect &r)
		{
			return (this->point.x == r.point.x && this->point.y == r.point.y && this->size.width == r.size.width && this->size.height == r.size.height);
		}

		bool operator!=(const Rect &r)
		{
			return (this->point.x != r.point.x || this->point.y != r.point.y || this->size.width != r.size.width || this->size.height != r.size.height);
		}


		Point point;            ///< point member.
		Size size;              ///< size member.
	};

	/// Struct
	struct ImageInfo
	{
		ImageInfo()
			: size()
			, bitDepth(0)
			, channel(0)
		{}

		ImageInfo(Size s, int bd, int ch = 1)
			: size(s)
			, bitDepth(bd)
			, channel(ch)
		{}

		ImageInfo(const ImageInfo &that)
			: size(that.size)
			, bitDepth(that.bitDepth)
			, channel(that.channel)
		{}

		bool operator==(const ImageInfo &that)
		{
			return (this->size == that.size && this->bitDepth == that.bitDepth && this->channel == that.channel);
		}

		bool operator!=(const ImageInfo &that)
		{
			return (this->size != that.size || this->bitDepth != that.bitDepth || this->channel != that.channel);
		}

		bool operator<(const ImageInfo &that) const
		{
			if (this->size < that.size)
			{
				return true;
			}
			else if ((this->size == that.size) && (this->bitDepth < that.bitDepth))
			{
				return true;
			}
			else if ((this->size == that.size) && (this->bitDepth == that.bitDepth) && (this->channel < that.channel))
			{
				return true;
			}
			return false;
		}

		Size size;
		int bitDepth;
		int channel;
	};

	/// \brief File information data struct.
	struct FileInfo
	{
		ImageInfo imageInfo;
		unsigned long imageCounts;
	};
}



#endif
