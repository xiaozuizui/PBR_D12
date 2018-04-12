#ifndef LITTLEMM_CORE
#define LITTLEMM_CORE

#define M_PI 3.1415926f

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <random>
#include <iostream>
#include <math.h>

using namespace DirectX;

#pragma region testSphere

typedef XMFLOAT3 RGB_COLOR;
enum Refl_t
{
	DIFF,SPEC,REFR
};

std::default_random_engine generator;
std::uniform_real_distribution<float> distr(0.0f, 1.0f);

float erand48(unsigned short X)
{
	return distr(generator);
}
#pragma endregion


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


//test radiance

//if (!Quadratic(A, B, C, &t0, &t1));
//bool Quadratic();

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

#endif // !LITTLEMM_CORE