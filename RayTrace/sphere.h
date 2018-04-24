#ifndef LITTLEMM_SPHERE
#define LITTLEMM_SPHERE


#include "shape.h"
#include "Intersection.h"

class Sphere : public  Shape
{
public:
	//Sphere();
	Sphere(XMFLOAT4X4 ObjectToWorld, XMFLOAT4X4 WorldToObject, float r);
	
	bool Intersect(const Ray &ray, Intersection *p)const;
private:
	float radius;
};

#endif // !LITTLEMM_SPHERE