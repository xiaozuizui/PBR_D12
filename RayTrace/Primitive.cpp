#include "Primitive.h"

 uint32_t Primitive::nextprimitiveId = 0;

bool Primitive::Intersect(const Ray &r, Intersection *p)
{
	return	shape->Intersect(r, p);
}