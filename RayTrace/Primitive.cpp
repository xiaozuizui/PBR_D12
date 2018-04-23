#include "Primitive.h"


bool Primitive::Intersect(const Ray &r, Intersection *p)
{
	return	shape->Intersect(r, p);
}