#pragma once
#include "BindBase.h"
#include <string>
class PixelShaderBind : public BindBase
{
public:
	PixelShaderBind(const std::wstring& path, Graphics* pGFX)
		:
		BindBase(pGFX)
	{
		HRESULT hr;
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
		D3DReadFileToBlob(path.c_str(), &pBlob);
		hr = GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	}
	void Bind()
	{
		GetContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	}
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};