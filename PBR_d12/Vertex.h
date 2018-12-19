#pragma once
#include <d3d12.h>

#include <DirectXMath.h> 

namespace littlemm
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 TexC;
	};
}
