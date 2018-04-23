#ifndef LITTLEMM_CORE
#define LITTLEMM_CORE

#define M_PI 3.1415926f

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <random>
#include <iostream>
#include <math.h>

using namespace DirectX;
using namespace std;



typedef XMFLOAT3 RGB_COLOR;
typedef XMFLOAT3 Point;
enum Refl_t
{
	DIFF,SPEC,REFR
};



class Ray
{
public:
	Ray()
	{
		origin = XMFLOAT3(0, 0, 0);
		direction = XMFLOAT3(0, 0, 0 );
	}
	Ray(XMFLOAT3 o, XMFLOAT3 d, float min_t = 0.0f, float max_t = 9999.0f)
	{
		origin = o;
		direction = d;
		mint = min_t;
		maxt = max_t;
	}

	XMFLOAT3 GetPoint(float t)
	{
		XMFLOAT3 temp;
		XMStoreFloat3(&temp, (XMLoadFloat3(&origin) + t * XMLoadFloat3(&direction)));
		return  temp;
	}

	XMFLOAT3 origin;
	XMFLOAT3 direction;
	float mint, maxt;
};


inline XMMATRIX Perspective(float fov, float n, float f)
{
	float invTanAng = 1.0f / tanf((fov*3.1415926f / 180.0f) / 2.0f);
	return XMMatrixScaling(invTanAng, invTanAng, 1)*XMLoadFloat4x4(&XMFLOAT4X4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, f / (f - n), -f * n / (f - n),
		0, 0, 1, 0));
}


//test radiance

//if (!Quadratic(A, B, C, &t0, &t1));

inline bool Quadratic(float A,float B,float C,float *t0,float *t1)
{
	float dleta = B * B - 4.f * A * C;
	if (dleta < 0.) return false;
	float rootDiscrim = sqrtf(dleta);

	// Compute quadratic _t_ values
	float q;
	if (B < 0) q = -.5f * (B - rootDiscrim);
	else       q = -.5f * (B + rootDiscrim);
	*t0 = q / A;
	*t1 = C / q;
	if (*t0 > *t1) swap(*t0, *t1);
	return true;
}

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

#endif // !LITTLEMM_CORE