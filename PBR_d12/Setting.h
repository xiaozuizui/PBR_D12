#pragma once
#include "stdafx.h"
#include <array>
#include <d3d12.h>
#include "d3dx12.h"

namespace littlemm
{



	class Setting
	{

	public:

		Setting();
		~Setting();


		static int gNumFrameResource;
		static int SwapChainBufferCount;
		static int Width;
		static int Height;


		static int vKey_W;
		static int vKey_S;
		static int vKey_A;
		static int vKey_D;
		///
		

		///
		static void InitSetting()
		{
			vKey_W = 'W';
			vKey_S = 'S';
			vKey_A = 'A';
			vKey_D = 'D';
			gNumFrameResource = 3;

			Width = 800;
			Height = 800;
			

		}

		static std::array<CD3DX12_STATIC_SAMPLER_DESC, 6>  GetStaticSamplers()
		{
			const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
				0, // shaderRegister
				D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
				D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

			const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
				1, // shaderRegister
				D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

			const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
				2, // shaderRegister
				D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
				D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

			const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
				3, // shaderRegister
				D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

			const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
				4, // shaderRegister
				D3D12_FILTER_ANISOTROPIC, // filter
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
				D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
				0.0f,                             // mipLODBias
				8);                               // maxAnisotropy

			const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
				5, // shaderRegister
				D3D12_FILTER_ANISOTROPIC, // filter
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
				D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
				0.0f,                              // mipLODBias
				8);                                // maxAnisotropy

			return {
				pointWrap, pointClamp,
				linearWrap, linearClamp,
				anisotropicWrap, anisotropicClamp };
		}
	};


	
}
