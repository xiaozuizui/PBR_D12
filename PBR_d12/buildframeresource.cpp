#include "stdafx.h"
#include "PBR_d12.h"
#include "Setting.h"


void PBRD12::BuildFrameResource()
{
	for (int i = 0; i < Setting::gNumFrameResource; ++i)
	{
		mConstantResource.push_back(std::make_unique<ConstantResource>(md3dDevice.Get(),
			1, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
	}
}