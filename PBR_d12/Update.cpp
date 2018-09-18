#include "stdafx.h"
#include "GameTimer.h"
#include "PBR_d12.h"

bool first = true;

void PBRD12::Update(const GameTimer& gt)
{

		OnKeyboardInput(gt);
	
		
		// Update the constant buffer with the latest worldViewProj matrix.
		ObjectConstants objConstants;
		XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(mCamera.GetView()*mCamera.GetProj()));
		mObjectCB->CopyData(0, objConstants);
 	


}

//
//void PBRD12::UpdateObjectCBs(const GameTimer& gt)
//{
//	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
//	for (auto& e : mAllRitems)
//	{
//		// Only update the cbuffer data if the constants have changed.  
//		// This needs to be tracked per frame resource.
//		if (e->NumFramesDirty > 0)
//		{
//			XMMATRIX world = XMLoadFloat4x4(&e->World);
//			XMMATRIX texTransform = XMLoadFloat4x4(&e->TexTransform);
//
//			ObjectConstants objConstants;
//			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
//			//XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));
//			//objConstants.MaterialIndex = e->Mat->MatCBIndex;
//
//			currObjectCB->CopyData(e->ObjCBIndex, objConstants);
//
//			// Next FrameResource need to be updated too.
//			e->NumFramesDirty--;
//		}
//	}
//}