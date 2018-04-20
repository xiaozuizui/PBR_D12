#pragma once
#ifndef LITTLEMM_SAMPLE
#define LITTLEMM_SAMPLE


struct CameraSample
{
public:
	float imageX, imageY;
	float lensU, lensV;
	float time;
};


class Sample
{
public:
	Sample();
	~Sample();
};


class Sampler
{

};

#endif // !LITTLEMM_SAMPLE
