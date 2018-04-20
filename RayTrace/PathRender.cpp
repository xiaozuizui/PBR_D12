#include "PathRender.h"

PathRender::PathRender(Sampler *s, Camera *c)
{
	sampler = s;
	camera = c;

}

PathRender::~PathRender()
{
	delete sampler;
	delete camera;

}

void PathRender::RunRender(const Scene *scene)
{
	//此处需实现多线程

}



void Task::Run()
{

}