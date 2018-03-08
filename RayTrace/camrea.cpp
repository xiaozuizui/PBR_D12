#include "camera.h"

Camera::Camera(const XMFLOAT4X4 & cam2world, float sopen, float sclose, Film * f):CameraToWorld(cam2world),shutterOpen(sopen),shutterClose(sclose)
{
	film = f;
}

Camera::~Camera()
{
	delete film;
}

//screen����Ļ����
PerspectiveCamera::PerspectiveCamera(XMFLOAT4X4& cam2world, float screenWindow[4], float sopen, float sclose, float fov, Film * film):Camera(cam2world,sopen,sclose,film)
{

	//͸��ͶӰ����
	CameraToScreen = XMFLOAT4X4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, fov / (fov - 0.0001), -fov * 0.0001 / (fov - 0.0001),
		0, 0, 1, 0);


	//������Ļ���꣨NDC������դ����ı任����
	XMMATRIX Temp_ScreenToRaster = XMMatrixScaling(film->xResolution, film->yResolution, 1)*
		XMMatrixScaling(1.f / (screenWindow[1] - screenWindow[0]), 1.f / (screenWindow[2] - screenWindow[3]), 1.f)*
		XMMatrixTranslation(-screenWindow[0], -screenWindow[3], 0.f);
	XMStoreFloat4x4(&ScreenToRaster, Temp_ScreenToRaster);

	//�����դ��NDC�ı任����
	XMMATRIX Temp_RasterToScreen = XMMatrixInverse(nullptr, Temp_ScreenToRaster);
	XMStoreFloat4x4(&RasterToScreen, Temp_RasterToScreen);
	
	//�����դ������ռ������任����
	XMMATRIX Temp_RasterToCamera = Temp_RasterToScreen * XMMatrixInverse(nullptr,XMLoadFloat4x4(&CameraToScreen));
	XMStoreFloat4x4(&RasterToCamera, Temp_RasterToCamera);


}

float PerspectiveCamera::GenerateRay(CameraSample& sample, Ray* ray)
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
	ray = &Ray(XMFLOAT3(0.0, 0.0, 0.0), SamplePoint);
	return 0.0f;
}
