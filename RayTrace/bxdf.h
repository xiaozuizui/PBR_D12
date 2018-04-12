#ifndef LITTLEMM_BSDF
#define LITTLEMM_BSDF

#include "core.h"


enum BSDF_TYPE
{
	BSDF_REFLECTION,
	BSDF_TRANSMISSION,
	BSDF_DIFFUSE,
	BSDF_SPECULAR
};

class BxDF
{
	
public:
	virtual XMFLOAT3 f(const XMFLOAT3 *wi, const XMFLOAT3 *wo);
	virtual XMFLOAT3 rh(const XMFLOAT3 *wi, const XMFLOAT3 *wo);
private:
	BSDF_TYPE type;



};

#endif // !LITTLEMM_BSDF
