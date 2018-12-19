#include "stdafx.h"
#include "GameTimer.h"
#include "LittleEngineResource.h"

bool first = true;



void littlemm::LittleEngineResource::Update(const GameTimer& gt)
{

		OnKeyboardInput(gt);

		mCurrConstantResourceIndex = (mCurrConstantResourceIndex + 1) % Setting::gNumFrameResource;
		mCurrConstantResource = mConstantResource[mCurrConstantResourceIndex].get();


		// Has the GPU finished processing the commands of the current frame resource?
   // If not, wait until the GPU has completed commands up to this fence point.
		if (mCurrConstantResource->Fence != 0 && mFence->GetCompletedValue() < mCurrConstantResource->Fence)
		{
			HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
			ThrowIfFailed(mFence->SetEventOnCompletion(mCurrConstantResource->Fence, eventHandle));
			WaitForSingleObject(eventHandle, INFINITE);
			CloseHandle(eventHandle);
		}

#ifdef WAVES
		UpdateWaves(gt);
#endif
		// Update the constant buffer with the latest worldViewProj matrix.
		UpdateMainPassCB(gt);
		UpdateObjectCBs(gt);
		UpdateMaterialBuffer(gt);
 	


}


void littlemm::LittleEngineResource::UpdateObjectCBs(const GameTimer& gt)
{


	auto currObjectCB = mCurrConstantResource->ObjectCB.get();

	for (auto& e : mAllRitems)
	{
		// Only update the cbuffer data if the constants have changed.  
		// This needs to be tracked per frame resource.
		if (e->NumFramesDirty > 0)
		{
			XMMATRIX world = XMLoadFloat4x4(&e->World);
			XMMATRIX texTransform = XMLoadFloat4x4(&e->TexTransform);

			ConstantsPerObject objectconstant;

			//物体世界坐标与纹理坐标
			XMStoreFloat4x4(&objectconstant.World, XMMatrixTranspose(world));
			XMStoreFloat4x4(&objectconstant.TexTransform, XMMatrixTranspose(texTransform));
			
			//XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));
			objectconstant.MaterialIndex = e->Mat->MatCBIndex;

			currObjectCB->CopyData(e->ObjCBIndex, objectconstant);

			// Next FrameResource need to be updated too.
			e->NumFramesDirty--;
		}
	}
}

//per frame update 
void littlemm::LittleEngineResource::UpdateMainPassCB(const GameTimer& gt)
{

	ConstantsPerFrame mMainPassCB;

	XMMATRIX view = mCamera.GetView();
	XMMATRIX proj = mCamera.GetProj();

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);

	XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
	XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
	XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	mMainPassCB.EyePosW = mCamera.GetPosition3f();
	mMainPassCB.LookAt = mCamera.GetLook3f();

	mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
	mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
	mMainPassCB.NearZ = 1.0f;
	mMainPassCB.FarZ = 1000.0f;
	mMainPassCB.TotalTime = gt.TotalTime();
	mMainPassCB.DeltaTime = gt.DeltaTime();
	mMainPassCB.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	mMainPassCB.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[0].Strength = { 0.8f, 0.8f, 0.8f };
	mMainPassCB.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[1].Strength = { 0.4f, 0.4f, 0.4f };
	mMainPassCB.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	mMainPassCB.Lights[2].Strength = { 0.2f, 0.2f, 0.2f };

	//auto bug =  std::to_wstring(mCamera.GetLook3f().x) + std::to_wstring(mCamera.GetLook3f().y) + std::to_wstring(mCamera.GetLook3f().z)+L'\n';
	//OutputDebugString(bug.c_str());
	auto currPassCB = mCurrConstantResource->frameCB.get();



	//update shadow
	





	//update shadow

	currPassCB->CopyData(0, mMainPassCB);
}


void littlemm::LittleEngineResource::UpdateMaterialBuffer(const GameTimer& gt)
{
	auto currMaterialBuffer = mCurrConstantResource->Materials.get();
	for (auto& e : mMaterials)
	{
		
		Material* mat = e.second.get();
		if (mat->NumFramesDirty > 0)
		{
			XMMATRIX matTransform = XMLoadFloat4x4(&mat->MatTransform);

			MaterialData matData;
			matData.DiffuseAlbedo = mat->DiffuseAlbedo;
			matData.FresnelR0 = mat->FresnelR0;
			matData.Roughness = mat->Roughness;
			XMStoreFloat4x4(&matData.MatTransform, XMMatrixTranspose(matTransform));
			matData.DiffuseMapIndex = mat->DiffuseSrvHeapIndex;

			currMaterialBuffer->CopyData(mat->MatCBIndex, matData);

			// Next FrameResource need to be updated too.
			mat->NumFramesDirty--;
		}
	}
}


void littlemm::LittleEngineResource::AnimateMaterials(const GameTimer& gt)
{
	
}


#ifdef WAVES
void LittleEngineResource::UpdateWaves(const GameTimer& gt)
{
	static float t_base = 0.0f;
	
	if ((mTimer.TotalTime() - t_base) >= 0.25f)
	{
		t_base += 0.25f;

		int i = MathHelper::Rand(4, mWaves->RowCount() - 5);
		int j = MathHelper::Rand(4, mWaves->ColumnCount() - 5);

		float r = MathHelper::RandF(0.2f, 0.5f);

		mWaves->Disturb(i, j, r);
	}

	// Update the wave simulation.
	mWaves->Update(gt.DeltaTime());

	// Update the wave vertex buffer with the new solution.
	
	auto currWavesVB = mCurrConstantResource->WavesVB.get();
	for (int i = 0; i < mWaves->VertexCount(); ++i)
	{
		Vertex v;

		v.Pos = mWaves->Position(i);
		v.Normal = mWaves->Normal(i);

		// Derive tex-coords from position by 
		// mapping [-w/2,w/2] --> [0,1]
		v.TexC.x = 0.5f + v.Pos.x / mWaves->Width();
		v.TexC.y = 0.5f - v.Pos.z / mWaves->Depth();

		currWavesVB->CopyData(i, v);
	}

	// Set the dynamic VB of the wave renderitem to the current frame VB.
	mWaveRitem->Geo->VertexBufferGPU = currWavesVB->Resource();
}
#endif

