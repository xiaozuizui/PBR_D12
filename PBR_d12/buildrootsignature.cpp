#include "stdafx.h"


#include "LittleEngineResource.h"


void littlemm::LittleEngineResource::BuildRootSignature()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[4];

	// Create a single descriptor table of CBVs.


	slotRootParameter[0].InitAsConstantBufferView(0);//perframe
	slotRootParameter[1].InitAsConstantBufferView(1);//perobject


	CD3DX12_DESCRIPTOR_RANGE texTable;//Œ∆¿Ì
	texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 5, 0, 0);

	slotRootParameter[2].InitAsDescriptorTable(1, &texTable, D3D12_SHADER_VISIBILITY_PIXEL);

	//material buffer
	slotRootParameter[3].InitAsShaderResourceView(0, 1);

	// A root signature is an array of root parameters.
	auto staticSamplers = littlemm::Setting::GetStaticSamplers();

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(4, slotRootParameter,staticSamplers.size() , staticSamplers.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature)));
}
