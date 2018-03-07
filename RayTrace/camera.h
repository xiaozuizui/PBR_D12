#pragma once
#ifndef  LITTLEMM_CAMERA
#define LITTLEMM_CAMERA

#include "../PBR_d12/d3dUtil.h"
#include "core.h"
#include "Film.h"
#include "sample.h"

using namespace DirectX;

class Camera
{
public:

	Camera(const XMFLOAT4X4 &cam2world, float sopen, float sclose,
		Film *f);
	virtual ~Camera();
	virtual float GenerateRay(const CameraSample &sample,
		Ray *ray) const = 0;

	//virtual float GenerateRayDifferential(const CameraSample &sample, RayDifferential *rd) const;

	// Camera Public Data
	XMFLOAT4X4 CameraToWorld;
	const float shutterOpen, shutterClose;
	Film *film;
};


class PerspectiveCamera :Camera
{
public:
	PerspectiveCamera(XMFLOAT4X4 &cam2world , float screenWindow[4], float sopen, float sclose, float fov, Film *film);
	float GenerateRay(CameraSample &sample, Ray* ray);
private:
	XMFLOAT4X4 CameraToScreen, RasterToCamera;
	XMFLOAT4X4 ScreenToRaster, RasterToScreen;
};


#endif // ! LITTLEMM_CAMERA