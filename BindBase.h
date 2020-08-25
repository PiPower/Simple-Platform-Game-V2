#pragma once
#include "DirectX.h"
class BindBase
{
public:
	virtual void Bind();
	virtual ~BindBase();
protected:
	BindBase() = delete;
	BindBase(Graphics* pGFX) : pGFX(pGFX){}
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	ID3D11RenderTargetView* GetRTV();
private:
	Graphics* pGFX;
};