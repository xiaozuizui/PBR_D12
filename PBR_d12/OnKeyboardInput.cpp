#include "stdafx.h"
#include "LittleEngineResource.h"
#include "Camera.h"
#include "GameTimer.h"

void littlemm::LittleEngineResource::OnKeyboardInput(const GameTimer& gt)
{
	const float dt = gt.DeltaTime();

	if (GetAsyncKeyState(Setting::vKey_W) & 0x8000)
		mCamera.Walk(10.0f*dt);

	if (GetAsyncKeyState(Setting::vKey_S) & 0x8000)
		mCamera.Walk(-10.0f*dt);

	if (GetAsyncKeyState(Setting::vKey_A) & 0x8000)
		mCamera.Strafe(-10.0f*dt);

	if (GetAsyncKeyState(Setting::vKey_D) & 0x8000)
		mCamera.Strafe(10.0f*dt);

	mCamera.UpdateViewMatrix();
}
