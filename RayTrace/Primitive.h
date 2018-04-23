#ifndef  LITTLEMM_PRIMITIVE
#define LITTLEMM_PRIMITIVE
 // ! LITTLEMM_PRIMITIVE


#include "core.h"
#include "Intersection.h"
#include "shape.h"


class Primitive
{
public:
	Primitive(Shape* s) :primitiveId(nextprimitiveId++),shape(s) {}
	void Intersect(const Ray &r, Intersection *p);

private:
	Shape * shape;
	uint32_t primitiveId;
	Primitive* next;
	static uint32_t nextprimitiveId;
}; 


#endif