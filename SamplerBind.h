#pragma once
#include "BindBase.h"

class SamplerBind : public BindBase
{
public:
	SamplerBind(Graphics* pGFX)
		:
		BindBase(pGFX)
	{
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		GetDevice()->CreateSamplerState(&samplerDesc, &pSampler);
	}
	void Bind()
	{
	    GetContext()->PSSetSamplers(0, 1, pSampler.GetAddressOf());
	}
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};
