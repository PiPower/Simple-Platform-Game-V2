#include "Board.h"

using namespace std;
using namespace DirectX;

Board::Board(Graphics* pGFX,float BlockScale)
	:
	pGFX(pGFX) , BlockScale(BlockScale)
{
	this->proportion =  (float)pGFX->GetHeight()/ (float)pGFX->GetWidth();

	std::vector<Line> Lines;

	for (float y = BlockScale; y < 1.0f; y += BlockScale * 2.0f)
	{
		Lines.push_back(Line{ -1/ proportion, y, 0, 0, 0 });
		Lines.push_back(Line{ 1/ proportion, y, 0, 0, 0 });
	}
	for (float y = -BlockScale; y > -1.0f; y -= BlockScale * 2.0f)
	{
		Lines.push_back(Line{ -1/ proportion, y, 0, 0, 0 });
		Lines.push_back(Line{ 1/ proportion, y, 0, 0, 0 });
	}

	for (float x = BlockScale; x < 1.0f/proportion; x += BlockScale * 2)
	{
		Lines.push_back(Line{ x, -1, 0, 0, 0 });
		Lines.push_back(Line{ x, 1, 0, 0, 0 });
	}
	for (float x = -BlockScale; x > -1.0f/ proportion; x -= BlockScale * 2)
	{
		Lines.push_back(Line{ x, -1, 0, 0, 0 });
		Lines.push_back(Line{ x, 1, 0, 0, 0 });
	}

	VertexCount = Lines.size();
	ScreenBinds.push_back(new VertexBufferBind(move(Lines),pGFX));

	VertexShaderBind* VSshader = new VertexShaderBind(L"VanillaVertexShader.cso", pGFX);
	vector<D3D11_INPUT_ELEMENT_DESC> ied = 
	{
	{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,8,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	ScreenBinds.push_back(new InputLayoutBind(move(ied), VSshader->GetBlob(),pGFX));
	ScreenBinds.push_back(VSshader);

	ScreenBinds.push_back(new PixelShaderBind(L"VanillaPixelShader.cso", pGFX));

	PositionTransformer transforms;

	transforms.proportion = this->proportion;
	ScreenBinds.push_back(new VSConstantBufferBind(transforms, pGFX));
	ScreenBinds.push_back(new PrimitiveTopologyBind(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, pGFX));
}

void Board::Draw()
{
	for (auto b : ScreenBinds)
	{
		b->Bind();
	}
	pGFX->Draw(VertexCount);
}
