#pragma once
#ifndef LITTLEMM_FILM
#define LITTLEMM_FILM


class Film
{
public:
	Film(int x,int y);
	int xResolution, yResolution;
	~Film();
};

#endif // !LITTLEMM_FILM