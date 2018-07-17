/**
* \file Enums.h
* \brief More than one file will be used
*
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.06.22
*/
#ifndef _ENUMS_H
#define _ENUMS_H


namespace ELDER
{

	/// \brief Data format.
	enum class DataFormats
	{
		kNoneGraySacle = 0,                     ///< Unknown data format.
		k8BitGrayScale = 1,                     ///< 8 bit gray scale.
		k10BitGrayScale,                        ///< 10 bit gray scale.
		k12BitGrayScale,                        ///< 12 bit gray scale.
		k16BitGrayScale,                        ///< 16 bit gray scale.
		k32BitGrayScale                         ///< 32 bit gray scale.
	};
}



#endif
