#include <iostream>

//#include "Structure/Structs.h"
//#include "Enumeration/Enums.h"
//#include "Definition/Definitions.h"

#include "Image/ImagePool.hpp"

#include "ImageOperator/ImageMeanStdDev.hpp"
#include "ImageOperator/ImageMax.hpp"

#include "ImageAlgorithm/ImageFilterMean.hpp"
#include "ImageOperator/ImageAdd.hpp"
#include "ImageOperator/ImageSub.hpp"

int main()
{
// 	Ipp8u *data = ippsMalloc_8u(1023 * 1023);
// 	memset(data, 100, 1023 * 1023);
// 
// 	Ipp8u max = 0;
// 	IppStatus status = ippiMax_8u_C1R
// 	(
// 		data,
// 		1023,
// 		{ 1023, 1023 },
// 		&max
// 	);
// 	std::cout << (int)max << std::endl;

	using Image8 = ELDER::CImage<ELDER::CIDT8U, ELDER::CICH1, ELDER::CImageIPPI>;
	using Image16 = ELDER::CImage<ELDER::CIDT16U, ELDER::CICH1, ELDER::CImageIPPI>;

	Image8 img1;
	img1.Initialize(512, 512);

	Image8 img2;
	img2.Initialize(512, 512);

	unsigned char * buf = new unsigned char[512 * 512];
	memset(buf, 1, 512 * 512);
	ELDER::CImage8u1cIPPI *image3 = new ELDER::CImage8u1cIPPI;
	image3->Initialize(512, 512, buf);

	ELDER::CImage8u1cIPPI *image4 = new ELDER::CImage8u1cIPPI;
	image4->Initialize(512, 512);


	ELDER::OPERATOR::CImageAdd<ELDER::OPERATOR::CAdd8u1c>::Add(image4, image3);

	auto m = ELDER::OPERATOR::CImageMax<ELDER::OPERATOR::CMax8u1c>::Max(image4);
	std::cout << (int)m << std::endl;
	
	int i;
	std::cin >> i;
	
	return 0;
}

