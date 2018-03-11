#include "camera.h"

Camera::Camera(const XMFLOAT4X4 & cam2world, float sopen, float sclose, Film * f):CameraToWorld(cam2world),shutterOpen(sopen),shutterClose(sclose)
{
	film = f;
}

Camera::~Camera()
{
	delete film;
}

//screen是屏幕比例
PerspectiveCamera::PerspectiveCamera(XMFLOAT4X4& cam2world, float screenWindow[4], float sopen, float sclose, float fov, Film * film):Camera(cam2world,sopen,sclose,film)
{

	//透视投影矩阵
	XMStoreFloat4x4(&CameraToScreen,Perspective(fov, 1e-2f, 1000.0f));
	 

	//计算屏幕坐标（NDC）到光栅坐标的变换矩阵
	XMMATRIX Temp_ScreenToRaster = XMMatrixScaling(film->xResolution, film->yResolution, 1)*
		XMMatrixScaling(1.f / (screenWindow[1] - screenWindow[0]), 1.f / (screenWindow[2] - screenWindow[3]), 1.f)*
		XMMatrixTranspose( XMMatrixTranslation(-screenWindow[0], -screenWindow[3], 0.f));
	XMStoreFloat4x4(&ScreenToRaster, Temp_ScreenToRaster);

	//计算光栅到NDC的变换矩阵
	XMMATRIX Temp_RasterToScreen =  XMMatrixInverse(nullptr, Temp_ScreenToRaster);
	XMStoreFloat4x4(&RasterToScreen, Temp_RasterToScreen);
	
	//计算光栅到相机空间的坐标变换矩阵
	XMMATRIX Temp_RasterToCamera = XMMatrixInverse(nullptr, XMLoadFloat4x4(&CameraToScreen))*Temp_RasterToScreen ;
	XMStoreFloat4x4(&RasterToCamera, Temp_RasterToCamera);


}


 float  PerspectiveCamera::GenerateRay(const CameraSample& sample, Ray* ray) const
{
	XMMATRIX Temp_SamplePoint = XMLoadFloat4x4(&RasterToCamera)*XMMATRIX(
		1,0,0,sample.imageX,
		0,1,0,sample.imageY,																																																						
		0,0,1,0,
		0,0,0,1
	);
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, Temp_SamplePoint);
	XMFLOAT3 SamplePoint(temp._14, temp._24, temp._34);
	
	XMStoreFloat3(&SamplePoint, XMVector3Normalize(XMLoadFloat3(&SamplePoint)));
	ray = &Ray(XMFLOAT3(0.0, 0.0, 0.0), SamplePoint);
	return 0.0f;
}
