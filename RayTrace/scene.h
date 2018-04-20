#ifndef  LITTLEMM_SCENE
#define LITTLEMM_SCENE

class Scene
{
private:
	int NumOfSphere;
public:
	bool Intersect(Ray r);

};

class Primitive
{
public:
	Primitive():primitiveId()
private:
	uint32_t primitiveId;
	static uint32_t nextprimitiveId;
};
#endif // ! LITTLEMM_SCENE

