#pragma once 
#include "BindBase.h"
#include <vector>
class InputLayoutBind: public BindBase
{
public:
	InputLayoutBind(std::vector<D3D11_INPUT_ELEMENT_DESC> desc, ID3DBlob* pBlob,Graphics* pGFX)
		:
		BindBase(pGFX)
	{
		HRESULT hr;

		hr = GetDevice()->CreateInputLayout(desc.data(), desc.size(), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	}
	void Bind() override
	{
		GetContext()->IASetInputLayout(pInputLayout.Get());
	}
private:
   Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};