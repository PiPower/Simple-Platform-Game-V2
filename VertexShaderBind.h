#pragma once
#include "BindBase.h"
#include <string>
class VertexShaderBind: public BindBase
{
public:
	VertexShaderBind(const std::wstring path, Graphics* pGFX)
		:
	    BindBase(pGFX)
	{
		 HRESULT hr;
         D3DReadFileToBlob(path.c_str(), &pBlob);
	    hr = GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	}
	ID3DBlob* GetBlob()
	{
		return pBlob.Get();
	}
	void Bind() override
	{ 
		GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	}
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};