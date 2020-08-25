#include "GraphicalObject.h"
using namespace DirectX;
using namespace std;

GraphicalObject::GraphicalObject(Graphics* gfx, std::wstring path, float OffsetX, float OffsetY, float ScaleX, float ScaleY, float RotationAngle)
	:
	pGFX(gfx),OffsetX(OffsetX), OffsetY(OffsetY), ScaleX(ScaleX), ScaleY(ScaleY), RotationAngle(RotationAngle)
{
	//Creating Vertex Buffer-----------------------------------------------------
	Vertecies.emplace_back(Point{-1, 1, 0, 0});
	Vertecies.emplace_back(Point{ 1, 1, 1, 0});
	Vertecies.emplace_back(Point{-1, -1, 0, 1});
	Vertecies.emplace_back(Point{ 1,-1, 1, 1});

	Binds.push_back(new VertexBufferBind<Point>(std::move(Vertecies), gfx));

	//Creating Index Buffer-----------------------------------------------------
	std::vector<short int> indicies;
	indicies.push_back(0); 
	indicies.push_back(1);
	indicies.push_back(3);

	indicies.push_back(0);
	indicies.push_back(3); 
	indicies.push_back(2);
	Binds.push_back(new IndexBufferBind(move(indicies), gfx));

	//Creating Input Layout and VS --------------------------------------------------
	vector<D3D11_INPUT_ELEMENT_DESC> ied;
	ied.push_back({ "POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 });
	ied.push_back({ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,8,D3D11_INPUT_PER_VERTEX_DATA,0 });

	VertexShaderBind* bd = new VertexShaderBind(L"VS.cso", gfx);

	Binds.push_back(new  InputLayoutBind(move(ied), bd->GetBlob(), gfx));
	Binds.push_back(bd);
	//Creating PS --------------------------------------------------
	Binds.push_back(new PixelShaderBind(L"PS.cso", gfx));
	//Creating Topology --------------------------------------------------
	Binds.push_back(new PrimitiveTopologyBind(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, gfx));
	//Creating Texture and Sampler --------------------------------------------------
	Img = new ImageFile(path);
	Binds.push_back(new TextureBind(Img, gfx));
	Binds.push_back(new SamplerBind(gfx));

	//----------------------------------------------------------------------------------
	UVTransformer UVTransform;
	UVTransform.HigherBoundX = 1;
	UVTransform.LowerBoundX = 0;
	UVTransform.HigherBoundY = 1;
	UVTransform.LowerBoundY = 0;


	// UV transformer slot 0
	Binds.push_back(new PSConstantBufferBind<UVTransformer>(UVTransform, pGFX));
	NextPScBuffSlot = 1;

	//----------------------------------------------------------------------------------
	PositionTransformer PosTranform;
	PosTranform.transforms = XMMatrixTranspose(XMMatrixRotationZ(this->RotationAngle)* 
	XMMatrixScaling(this->ScaleX, this->ScaleY, 0) * XMMatrixTranslation(this->OffsetX, this->OffsetY, 0));

	PosTranform.proportion = (float)(pGFX->GetHeight()) / pGFX->GetWidth();

	PosTransformer = new VSConstantBufferBind<PositionTransformer>(PosTranform, pGFX);
	Binds.push_back(PosTransformer);
	NextVScBuffSlots = 1;
}

void GraphicalObject::SetUVCord(int LowerBoundX, int HigherBoundX, int LowerBoundY, int HigherBoundY)
{

	UVTransformer UVTransformer2;
	UVTransformer2.HigherBoundX = (float)HigherBoundX / Img->GetWidth();
	UVTransformer2.LowerBoundX = (float)LowerBoundX / Img->GetWidth();
	UVTransformer2.HigherBoundY = (float)HigherBoundY / Img->GetHeight();
	UVTransformer2.LowerBoundY = (float)LowerBoundY / Img->GetHeight();

	for (BindBase* bind : Binds)
	{
		if (auto ptr = dynamic_cast<PSConstantBufferBind<UVTransformer>*>(bind))
		{
			ptr->Map(UVTransformer2);
			break;
		}
	}


}

void GraphicalObject::Move(float OffsetX, float OffsetY)
{
	this->OffsetX += OffsetX;
	this->OffsetY += OffsetY;
}

void GraphicalObject::Scale(float ScaleX, float ScaleY)
{
	this->ScaleX *= ScaleX;
	this->ScaleY *= ScaleY;
}

void GraphicalObject::Rotate(float RotationAngle)
{
	this->RotationAngle += RotationAngle;
}

void GraphicalObject::Draw()
{

	PositionTransformer PosTranform;
	PosTranform.transforms = XMMatrixTranspose(XMMatrixRotationZ(this->RotationAngle) *
	XMMatrixScaling(this->ScaleX, this->ScaleY, 0) * XMMatrixTranslation(this->OffsetX, this->OffsetY, 0));

	PosTranform.proportion = (float)(pGFX->GetHeight()) / pGFX->GetWidth();
	PosTransformer->Map(PosTranform);

	int Indicies;
	for (auto bind : Binds)
	{
		bind->Bind();
		if (auto ptr = dynamic_cast<IndexBufferBind*>(bind))
		{
			Indicies = ptr->GetNumberOfIndicies();
		}
	}
	pGFX->DrawIndexed(Indicies);
}

GraphicalObject::~GraphicalObject()
{
	for (auto b : Binds)
	{
		delete b;
		b = nullptr;
	}
	delete Img;
}
