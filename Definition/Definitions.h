/**
* \file Definition.h
* \brief Declare the values to be evaluated at compile time.
* 
* detail description
*
* \author qdd
* \email
* \version 1.0.0.0
* \date 2017.09.13
*/
#ifndef _DEFINITION_H
#define _DEFINITION_H

namespace ELDER
{
	/// PI value.
	constexpr double kPI = 3.1415926536;

	/// float value equal compare
	constexpr float kEpsinon32 = 0.00001f;

	/// double value equal compare
	constexpr double kEpsinon64 = 0.00000001;

	/// 8bit gray scale image min value
	constexpr unsigned char kMinIntensity8u = 0;

	/// 8bit gray scale image max value
	constexpr unsigned char kMaxIntensity8u = 255;

	/// 8bit gray scale image pixel levels
	constexpr int kLevelsIntensity8u = 256;

	/// 16bit gray scale image min value
	constexpr unsigned short kMinIntensity16u = 0;

	/// 16bit gray scale image max value
	constexpr unsigned short kMaxIntensity16u = 65535;

	/// 16bit gray scale image pixel levels
	constexpr int kLevelsIntensity16u = 65536;
}



#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          