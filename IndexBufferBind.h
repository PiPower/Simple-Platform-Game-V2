#pragma once
#include "BindBase.h"
#include <vector>


class IndexBufferBind : public BindBase
{
public:

	IndexBufferBind(std::vector<short int>&& vertecies, Graphics* pGFX)
		:
		BindBase(pGFX)
	{
		this->vertecies = vertecies;
		HRESULT hr;
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;

		bd.ByteWidth = vertecies.size() * sizeof(short int);
		bd.StructureByteStride = sizeof(short int);

		bd.ByteWidth = vertecies.size() * sizeof(short int);
		bd.StructureByteStride = sizeof(short int);
		D3D11_SUBRESOURCE_DATA sbd = {};
		sbd.pSysMem = vertecies.data();
		hr = this->GetDevice()->CreateBuffer(&bd, &sbd, &pIndexBuffer);
	}
	void Bind() override
	{
		UINT strides = sizeof(short int);
		UINT offsets = 0;
		this->GetContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
	}
	int GetNumberOfIndicies()
	{
		return vertecies.size();
	}
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	std::vector<short int> vertecies;
};