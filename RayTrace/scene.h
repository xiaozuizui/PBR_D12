#ifndef  LITTLEMM_SCENE
#define LITTLEMM_SCENE

#include "Primitive.h"

class Scene
{
private:
	int NumOfSphere;
	Primitive *firstPrimitive;
public:
	bool Intersect(Ray r);

};



#endif // ! LITTLEMM_SCENE

