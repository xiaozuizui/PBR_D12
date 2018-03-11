#pragma once
#ifndef LITTLEMM_CORE
#define LITTLEMM_CORE


#include <DirectXMath.h>
#include <DirectXPackedVector.h>


using namespace DirectX;



class Ray
{
public:
	Ray()
	{
		origin = XMFLOAT3(0, 0, 0);
		direction = XMFLOAT3(0, 0, 0 );
	}
	Ray(XMFLOAT3 o, XMFLOAT3 d)
	{
		origin = o;
		direction = d;
	}
	XMFLOAT3 origin;
	XMFLOAT3 direction;
};

XMMATRIX Perspective(float fov, float n, float f)
{
	float invTanAng = 1.0f / tanf((fov*3.1415926f / 180.0f) / 2.0f);
	return XMMatrixScaling(invTanAng, invTanAng, 1)*XMLoadFloat4x4(&XMFLOAT4X4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, f / (f - n), -f * n / (f - n),
		0, 0, 1, 0));
}


#endif // !LITTLEMM_CORE