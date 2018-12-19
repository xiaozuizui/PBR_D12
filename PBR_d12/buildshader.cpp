#include "stdafx.h"
#include <d3d12.h>
#include "d3dUtil.h"
#include "LittleEngineResource.h"

void littlemm::LittleEngineResource::BuildShadersAndInputLayout()
{
	HRESULT hr = S_OK;

	const D3D_SHADER_MACRO defines[] =
	{
		"FOG", "1",
		NULL, NULL
	};

	const D3D_SHADER_MACRO alphaTestDefines[] =
	{
		"FOG", "1",
		"ALPHA_TEST", "1",
		NULL, NULL
	};



	//mvsByteCode = d3dUtil::CompileShader(L"Shaders/littleshader.hlsl", nullptr, "VS", "vs_5_1");
	//mpsByteCode = d3dUtil::CompileShader(L"Shaders/littleshader.hlsl", nullptr, "PS", "ps_5_1");

	mShaders["standardVs"] = d3dUtil::CompileShader(L"Shaders/littleshader.hlsl", nullptr, "VS", "vs_5_1");
	mShaders["standardPs"] = d3dUtil::CompileShader(L"Shaders/littleshader.hlsl", nullptr, "PS", "ps_5_1");

	mShaders["opaquePS"] = d3dUtil::CompileShader(L"Shaders/littleshader.hlsl", defines, "PS", "ps_5_1");
	mShaders["alphaTestedPS"] = d3dUtil::CompileShader(L"Shaders/littleshader.hlsl", alphaTestDefines, "PS", "ps_5_1");
	//mInputLayout =
	//{
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	//};

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
}
