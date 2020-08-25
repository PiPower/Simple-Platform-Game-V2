#include "BindBase.h"


void BindBase::Bind()
{
	int x = 3;
}

BindBase::~BindBase()
{
	pGFX = nullptr;
}

ID3D11Device* BindBase::GetDevice()
{
	return pGFX->pDevice.Get();
}

ID3D11DeviceContext* BindBase::GetContext()
{
	return pGFX->pImmediateContext.Get();
}

ID3D11RenderTargetView* BindBase::GetRTV()
{
	return pGFX->pRenderTargetView.Get();
}
