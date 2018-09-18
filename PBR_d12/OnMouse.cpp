#include "stdafx.h"
#include "PBR_d12.h"

void PBRD12::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void PBRD12::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void PBRD12::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON )&&( GetAsyncKeyState(VK_MENU) & 0x8000) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCamera.Pitch(dy);
		mCamera.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}