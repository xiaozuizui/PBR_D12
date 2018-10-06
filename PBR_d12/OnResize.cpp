#include "stdafx.h"
#include "LittleEngineResource.h"

void littlemm::LittleEngineResource::OnResize()
{
	LittleEngine::OnResize();


	mCamera.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}


