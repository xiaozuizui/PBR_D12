#ifndef  LITTLEMM_SCENE
#define LITTLEMM_SCENE

#include "Primitive.h"
#include "Intersection.h"
#include "../PBR_d12/d3dUtil.h"
#include "light.h"

class Scene
{
private:
	int NumOfSphere;
	Primitive *firstPrimitive;
public:
	Scene(int Num, Primitive *p);
	bool Intersect(const Ray& r,Intersection *p);
	vector<light* > lights;
	
};



#endif // ! LITTLEMM_SCENE

