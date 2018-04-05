#pragma once
#ifndef LITTLEMM_SHAPE
#define LITTLEMM_SHAPE
#include "core.h"

class Shape
{
public:
	XMFLOAT4X4 ObjectToWorld;
	XMFLOAT4X4 WorldToObject;
	//void* operator new(int i){}
	virtual bool Intersection(Ray ray)const = 0;
};

#endif


