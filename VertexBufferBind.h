#pragma once
#include "BindBase.h"
#include <vector>
template <typename T>
class VertexBufferBind : public BindBase
{
public:
	VertexBufferBind(std::vector<T>&& vertecies,Graphics* pGFX)
		:
	BindBase(pGFX)
	{
		this->vertecies = vertecies;
		HRESULT hr;
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		bd.ByteWidth = vertecies.size() * sizeof(T);
		bd.StructureByteStride = sizeof(T);
		D3D11_SUBRESOURCE_DATA sbd = {};
		sbd.pSysMem = vertecies.data();
		hr=this->GetDevice()->CreateBuffer(&bd, &sbd, &pVertexBuffer);
	}
	void Bind() override
	{
		UINT strides = sizeof(T);
		UINT offsets = 0;
		this->GetContext()->IASetVertexBuffers(0u,1, pVertexBuffer.GetAddressOf(), &strides, &offsets);
	}
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	std::vector<T> vertecies;
};