#pragma once

#include "shape.h"

class Sphere : public  Shape
{
public:
	bool Intersection(Ray ray);
	
private:
	float radius;
};