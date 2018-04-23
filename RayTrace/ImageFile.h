#ifndef LITTLEMM_IMAGEFILE
#define LITTLEMM_IMAGEFILE
#include "core.h"

class ImageFile
{
public:
	static int width;
	static int height;

	static RGB_COLOR* pixelcolor;

	static float *R;
	static float *G;
	static float *B;

	static void Initial(int x, int y);
	static void SavePi(RGB_COLOR color,int index);
	static void SaveFile();
};




#endif // !LITTLEMM_IMAGEFILE
