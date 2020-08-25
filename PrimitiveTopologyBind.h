#pragma once
#include "BindBase.h"

class PrimitiveTopologyBind : public BindBase
{
public:
	PrimitiveTopologyBind(D3D11_PRIMITIVE_TOPOLOGY top, Graphics* pGFX)
		:
		BindBase(pGFX), topology(top){}
	void Bind() override
	{
		GetContext()->IASetPrimitiveTopology(topology);
	}
private:
	D3D11_PRIMITIVE_TOPOLOGY topology;
};