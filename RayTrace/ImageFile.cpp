#include "ImageFile.h"

#include <string>
int ImageFile::width;
int ImageFile::height;
RGB_COLOR* ImageFile::pixelcolor;
float * ImageFile::R;
float * ImageFile::G;
float * ImageFile::B;

void ImageFile::Initial(int x,int y)
{
	width = x;
	height = y;
	pixelcolor = new RGB_COLOR[height*width];

	memset(pixelcolor, 0, sizeof(RGB_COLOR)*height*width);

}

void ImageFile::SaveFile()
{
	FILE *f = fopen("image.ppm", "w");         // Write image to PPM file. 
	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
	for (int i = 0; i < width*height; i++)
	{
		fprintf(f, "%d %d %d ", toInt(pixelcolor[i].x), toInt(pixelcolor[i].y), toInt(pixelcolor[i].z));
	}
}

void ImageFile::SavePi(RGB_COLOR color,int index)
{
	pixelcolor[index] = color;
}