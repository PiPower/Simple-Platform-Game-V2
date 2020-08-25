#pragma once
#include "BindPack.h"
#include <vector>

class GraphicalObject
{
public:
	struct UVTransformer
	{
		float LowerBoundX;
		float HigherBoundX;
		float LowerBoundY;
		float HigherBoundY;
	};
	struct PositionTransformer
	{
		DirectX::XMMATRIX transforms;
		float proportion;
	};
	struct CollRect
	{
		DirectX::XMFLOAT2  TopLeft;
		DirectX::XMFLOAT2  BottomRight;
	};
public:
	GraphicalObject(Graphics* gfx, std::wstring path, float OffsetX = 0, float OffsetY = 0, float ScaleX = 1, float ScaleY = 1, float RotationAngle = 0);
	//Area of pixels to draw in rect
	void SetUVCord(int LowerBoundX, int HigherBoundX, int LowerBoundY, int HigherBoundY);
	void Move(float OffsetX = 0, float OffsetY = 0);
	void Scale(float ScaleX = 1, float ScaleY = 1);
	void Rotate(float RotationAngle);
	void Draw();
	~GraphicalObject();
protected:
	struct Point
	{
		float x;
		float y;
		float TX;
		float TY;
	};
	float ScaleX;
	float ScaleY;
	float OffsetX;
	float OffsetY;
	float RotationAngle;
	unsigned short int NextPScBuffSlot=0;
	unsigned short int NextVScBuffSlots =0;
	std::vector<Point> Vertecies;
	std::vector<BindBase* > Binds;
	VSConstantBufferBind<PositionTransformer>* PosTransformer=nullptr;
	ImageFile* Img;
	Graphics* pGFX = nullptr;
};
