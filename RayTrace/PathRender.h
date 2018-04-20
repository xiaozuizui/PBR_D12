#ifndef LITTLEMM_PATHRENDER
#define LITTLEMM_PATHRENDER

#include "render.h"
#include "sample.h"
#include "camera.h"
#include "scene.h"

class PathRender : public Render
{
public:
	PathRender(Sampler *sampler,Camera *camera);
	RGB_COLOR Li(const Scene *scene, const Ray *ray, const Sample *sample);

	void RunRender(const Scene *scene);
	~PathRender();
private:
	Sampler * sampler;
	Camera *camera;
	
};


class Task
{
public:
	Task(const Scene *scene, Camera *c, int xs, int xe, int ys, int yd);
	void Run();
private:
	const Scene *scene;
	Camera *camera;
	int xstart, xend, ystart, yend;


	
};

#endif // !LITTLEMM_PATHRENDER