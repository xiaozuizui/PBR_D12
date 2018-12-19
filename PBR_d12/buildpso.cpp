
#include "stdafx.h"
#include "LittleEngineResource.h"


void littlemm::LittleEngineResource::BuildPSO()
{


	//ComPtr<ID3D12PipelineState> standPso;

	//opaque pso
	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaque;
	ZeroMemory(&opaque, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	opaque.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	opaque.pRootSignature = mRootSignature.Get();
	opaque.VS =
	{
		reinterpret_cast<BYTE*>(mShaders["standardVs"]->GetBufferPointer()),
		mShaders["standardVs"]->GetBufferSize()
	};
	opaque.PS =
	{
		reinterpret_cast<BYTE*>(mShaders["standardPs"]->GetBufferPointer()),
		mShaders["standardPs"]->GetBufferSize()
	};
	opaque.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	opaque.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	//opaque.BlendState.RenderTarget[0].
	opaque.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	//opaque.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	//
	//opaque.DepthStencilState.DepthEnable = 1;
	//
	opaque.SampleMask = UINT_MAX;
	opaque.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	opaque.NumRenderTargets = 1;
	opaque.RTVFormats[0] = mBackBufferFormat;
	opaque.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	opaque.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	opaque.DSVFormat = mDepthStencilFormat;
	HRESULT hr = md3dDevice->CreateGraphicsPipelineState(&opaque, IID_PPV_ARGS(&mPSOs["opaque"]));
	//= md3dDevice->CreateGraphicsPipelineState();

	//mPSOs["Opq"] =  std::move()


	//transparent PSO
	D3D12_GRAPHICS_PIPELINE_STATE_DESC transparentPsoDesc = opaque;


	D3D12_RENDER_TARGET_BLEND_DESC transparencyBlendDesc;
	transparencyBlendDesc.BlendEnable = true;
	transparencyBlendDesc.LogicOpEnable = false;
	transparencyBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	transparencyBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	transparencyBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
	transparencyBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	transparencyBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
	transparencyBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	transparencyBlendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
	transparencyBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	transparentPsoDesc.BlendState.RenderTarget[0] = transparencyBlendDesc;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&transparentPsoDesc, IID_PPV_ARGS(&mPSOs["transparent"])));




	D3D12_DEPTH_STENCIL_DESC shadowDSS;
	shadowDSS.DepthEnable = true;
	shadowDSS.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;                                  
	shadowDSS.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	shadowDSS.StencilEnable = true;
	shadowDSS.StencilReadMask = 0xff;
	shadowDSS.StencilWriteMask = 0xff;

	shadowDSS.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	shadowDSS.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	shadowDSS.FrontFace.StencilPassOp = D3D12_STENCIL_OP_INCR;
	shadowDSS.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_EQUAL;

	// We are not rendering backfacing polygons, so these settings do not matter.
	shadowDSS.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	shadowDSS.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	shadowDSS.BackFace.StencilPassOp = D3D12_STENCIL_OP_INCR;
	shadowDSS.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_EQUAL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC shadowPsoDesc = transparentPsoDesc;
	shadowPsoDesc.DepthStencilState = shadowDSS;
	
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&shadowPsoDesc, IID_PPV_ARGS(&mPSOs["shadow"])));







	D3D12_GRAPHICS_PIPELINE_STATE_DESC SelectObj;
	ZeroMemory(&SelectObj, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	D3D12_INPUT_ELEMENT_DESC SelectInputLayer[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	SelectObj.InputLayout = { SelectInputLayer,3 };
	SelectObj.pRootSignature = mRootSignature.Get();

	//complier shader for border
	/*{
		
		SelectVSCode = d3dUtil::CompileShader(L"Shaders/select.hlsl", nullptr, "VS", "vs_5_1");
		SelectPSCode = d3dUtil::CompileShader(L"Shaders/select.hlsl", nullptr, "PS", "ps_5_1");

	}


	SelectObj.VS =
	{
		reinterpret_cast<BYTE*>(SelectVSCode->GetBufferPointer()),
		SelectVSCode->GetBufferSize()
	};
	SelectObj.PS =
	{
		reinterpret_cast<BYTE*>(SelectPSCode->GetBufferPointer()),
		SelectPSCode->GetBufferSize()
	};
	SelectObj.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	SelectObj.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	SelectObj.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	SelectObj.SampleMask = UINT_MAX;
	SelectObj.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
	SelectObj.NumRenderTargets = 1;
	SelectObj.RTVFormats[0] = mBackBufferFormat;
	SelectObj.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	SelectObj.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	SelectObj.DSVFormat = mDepthStencilFormat;
	hr = md3dDevice->CreateGraphicsPipelineState(&SelectObj, IID_PPV_ARGS(&SeletedPso));
*/


	ThrowIfFailed(hr);
}
