#ifndef LITTLEMM_SHAPE
#define LITTLEMM_SHAPE
#include "core.h"
#include "Intersection.h"

class Shape
{
public:
	//virtual ~Shape();
	Shape(XMFLOAT4X4 ObjectToWorld, XMFLOAT4X4 WorldToObject){
		this->ObjectToWorld = ObjectToWorld;
		this->WorldToObject = WorldToObject;
	}
	XMFLOAT4X4 ObjectToWorld;
	XMFLOAT4X4 WorldToObject;
	//void* operator new(int i){}
	virtual bool Intersect(const Ray &ray,Intersection *p)const=0;
};

#endif


