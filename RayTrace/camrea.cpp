#include "camera.h"

Camera::Camera(const XMFLOAT4X4 & cam2world, float sopen, float sclose, Film * f):CameraToWorld(cam2world),shutterOpen(sopen),shutterClose(sclose)
{
	film = f;
}

Camera::~Camera()
{
	delete film;
}

//screenÊÇÆÁÄ»±ÈÀý
PerspectiveCamera::PerspectiveCamera(XMFLOAT4X4 cam2world, float screenWindow[4], float sopen, float sclose, float fov, Film * film):Camera(cam2world,sopen,sclose,film)
{
	CameraToScreen = XMFLOAT4X4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, fov / (fov - 0.0001), -fov * 0.0001 / (fov - 0.0001),
		0, 0, 1, 0);

	XMMATRIX Temp_ScreenToRaster = XMMatrixScaling(film->xResolution, film->yResolution, 1)*
		XMMatrixScaling(1.f / (screenWindow[1] - screenWindow[0]), 1.f / (screenWindow[2] - screenWindow[3]), 1.f)*
		XMMatrixTranslation(-screenWindow[0], -screenWindow[3], 0.f);

		//ScreenToRaster = XMFLOAT4X4();
	XMStoreFloat4x4(&ScreenToRaster, temp_ScreenToRaster);

	XMMATRIX Temp_RasterToScreen = 
	XMStoreFloat4x4(&RasterToScreen,XMMatrixInverse(Temp_RasterToScreen,)
	RasterToScreen = ScreenToRaster

}
