#pragma once 
#include "BindBase.h"

template<typename T>
class PSConstantBufferBind : public BindBase
{
public:
	PSConstantBufferBind(T Data, Graphics* pGFX, UINT slot=0 )
		:
		BindBase(pGFX),  slot(slot)
	{
		D3D11_BUFFER_DESC cbd = {};
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(T);
		cbd.StructureByteStride = 0u;
		D3D11_SUBRESOURCE_DATA sbd;
		sbd.pSysMem = &Data;
		GetDevice()->CreateBuffer(&cbd, &sbd, &ConstBuff);
	}
	void Bind()
	{
		GetContext()->PSSetConstantBuffers(slot, 1u, ConstBuff.GetAddressOf());
	}
	void Map(T TransformMap)
	{
		HRESULT hr;

		D3D11_MAPPED_SUBRESOURCE	mappedData;
		hr = GetContext()->Map(ConstBuff.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedData);
		memcpy(mappedData.pData, &TransformMap, sizeof(TransformMap));
		GetContext()->Unmap(ConstBuff.Get(), 0u);
	}
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> ConstBuff;
	UINT slot;
};