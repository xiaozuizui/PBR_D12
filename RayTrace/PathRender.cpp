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
	//�˴���ʵ�ֶ��߳�

}



void Task::Run()
{

}