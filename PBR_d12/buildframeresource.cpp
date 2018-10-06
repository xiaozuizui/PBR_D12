#include "stdafx.h"
#include "LittleEngineResource.h"
#include "Setting.h"


void littlemm::LittleEngineResource::BuildFrameResource()
{
	for (int i = 0; i < littlemm::Setting::gNumFrameResource; ++i)
	{
		mConstantResource.push_back(std::make_unique<ConstantResource>(md3dDevice.Get(),
			1, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
	}
}