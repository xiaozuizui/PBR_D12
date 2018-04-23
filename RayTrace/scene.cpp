#include "scene.h"


bool Scene::Intersect(Ray r)
{
	Primitive *p = firstPrimitive;
	for (int i = 0; i < NumOfSphere; i++)
	{
		//Primitive * p =
		Intersection intersection;
		p->Intersect(r, &intersection);
	}
	return false;
}