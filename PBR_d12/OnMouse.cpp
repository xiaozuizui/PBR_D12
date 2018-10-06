#include "stdafx.h"
#include "LittleEngineResource.h"

void littlemm::LittleEngineResource::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void littlemm::LittleEngineResource::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void littlemm::LittleEngineResource::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON ))
		//&&( GetAsyncKeyState(VK_MENU) & 0x8000) != 0)
	{
		
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCamera.Pitch(dy);
		mCamera.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}