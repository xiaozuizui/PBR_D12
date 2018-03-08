#include "../PBR_d12/d3dUtil.h"


using namespace DirectX;



class Ray
{
public:
	Ray(XMFLOAT3 o, XMFLOAT3 d)
	{
		origin = o;
		direction = d;
	}
	XMFLOAT3 origin;
	XMFLOAT3 direction;
};

