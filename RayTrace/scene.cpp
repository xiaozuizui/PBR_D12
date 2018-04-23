#include "scene.h"

Scene::Scene(int num, Primitive *p)
{
	NumOfSphere = num;
	firstPrimitive = p;
}

bool Scene::Intersect(const Ray& r,Intersection *p)
{
	Primitive *primitive = firstPrimitive;
	for (int i = 0; i < NumOfSphere; i++)
	{
		//Primitive * p =
		//Intersection intersection;
		if (primitive->Intersect(r, p))
			return true;
		primitive = primitive->next;
	}
	return false;
}