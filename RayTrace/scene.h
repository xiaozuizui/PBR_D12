#ifndef  LITTLEMM_SCENE
#define LITTLEMM_SCENE

#include "Primitive.h"
#include "Intersection.h"

class Scene
{
private:
	int NumOfSphere;
	Primitive *firstPrimitive;
public:
	Scene(int Num, Primitive *p);
	bool Intersect(const Ray& r,Intersection *p);

};



#endif // ! LITTLEMM_SCENE

