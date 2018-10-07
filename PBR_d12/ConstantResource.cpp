#include "stdafx.h"

#include "ConstantResource.h"


ConstantResource::ConstantResource(ID3D12Device* device, UINT passCount, UINT objectCount, UINT materialCount)
{
	
	ThrowIfFailed(device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(CmdListAlloc.GetAddressOf())));

	frameCB = std::make_unique<UploadBuffer<ConstantsPerFrame>>(device, passCount, true);
	ObjectCB = std::make_unique<UploadBuffer<ConstantsPerObject>>(device, objectCount, true);
	Materials = std::make_unique<UploadBuffer<MaterialData>>(device, materialCount, false);
}



ConstantResource::~ConstantResource()
{

}