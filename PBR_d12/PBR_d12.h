#pragma once

#include "resource.h"
#include "d3dApp.h"

class PBRD12 :public D3DApp
{
public:
	PBRD12(HINSTANCE hInstance);
	~PBRD12();

	virtual bool Initialize()override;

private:
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

};