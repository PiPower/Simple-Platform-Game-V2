#pragma once
#include "BindPack.h"
#include <fstream>
#include <vector>

class GraphicalObject
{
public:
	struct Camera
	{
		float X;
		float Y;
		float padd[2];
	};
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
	// Does not copy Camera const buffer
	GraphicalObject(const GraphicalObject& copy);
	GraphicalObject(GraphicalObject&& doner);
	// Camera stuff
	void BindCamera(Camera Tranformation);
	void UpdateCamera(Camera Tranformation);
	//Area of pixels to draw in rect
	void SetUVCord(int LowerBoundX, int HigherBoundX, int LowerBoundY, int HigherBoundY);
	void Move(float OffsetX = 0, float OffsetY = 0);
	void Scale(float ScaleX = 1, float ScaleY = 1);
	void Rotate(float RotationAngle);
	void Save(std::fstream& stream);
	void Draw() const;
	// For collision detection
	CollRect GetRect() const;
	// Getters
	float GetScaleX() const { return ScaleX; }
	float GetScaleY() const { return ScaleY; }
	float GetOffsetX() const { return OffsetX; }
	float GetOffsetY() const { return OffsetX; }
	float GetRotationAngle() const { return RotationAngle; };

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
	CollRect CollisionRectangle{ {-1,1},{1,-1} };
	VSConstantBufferBind<PositionTransformer>* PosTransformer=nullptr;
	VSConstantBufferBind<Camera>* Cam = nullptr;
	ImageFile* Img;
	Graphics* pGFX = nullptr;
};

