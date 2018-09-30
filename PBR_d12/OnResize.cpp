#include "stdafx.h"
#include "d3dApp.h"
#include "PBR_d12.h"

void PBRD12::OnResize()
{
	D3DApp::OnResize();


	mCamera.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}


