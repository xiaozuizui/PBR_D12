#include "stdafx.h"
#include "LittleEngineResource.h"

void littlemm::LittleEngineResource::GameInit()
{
	//float x = mRadius * sinf(mPhi)*cosf(mTheta);
	//float z = mRadius * sinf(mPhi)*sinf(mTheta);
	//float y = mRadius * cosf(mPhi);

	//// Build the view matrix.
	//XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	//XMVECTOR target = XMVectorZero();
	//XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


	////mCamera.LookAt(pos, target, up);


	//XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	////XMStoreFloat4x4(&mView, view);

	//
	//XMMATRIX world = XMLoadFloat4x4(&mWorld);
	//XMMATRIX proj = XMLoadFloat4x4(&mProj);
	//XMMATRIX worldViewProj = world * view*proj;

	//mCamera.LookAt(pos, target, up);
	mCamera.SetPosition(0.0f, 2.0f, -15.0f);
	//mCamera.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	// Update the constant buffer with the latest worldViewProj matrix.
	//ObjectConstants objConstants;
	//XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	//mObjectCB->CopyData(0, objConstants);
}


