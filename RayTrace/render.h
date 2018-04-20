#ifndef  LITTLEMM_RENDER
#define LITTLEMM_RENDER

#include "core.h"
#include "scene.h"
#include "sample.h"

class Render {
public:
	virtual ~Render();
	virtual RGB_COLOR Li(const Scene *scene, const Ray *ray, const Sample *sample);
	virtual void RunRender(const Scene *scene);
};

#endif // ! LITTLEMM_RENDER

