#pragma once
#include "DirectX.h"
#include "BindPack.h"
#include "GraphicalObject.h"
#include "Window.h"
class Board
{
private:
	struct Line
	{
		float x;
		float y;
		float R;
		float G;
		float B;
	};
	struct PositionTransformer
	{
		float proportion;
		float padd[3];
	};
public:
	Board(Graphics* pGFX, float BlockScale );
	void Controll(Window& wnd);
	void Draw();
private:
	std::vector<BindBase* >ScreenBinds;
	std::vector<GraphicalObject* > Blocks;
	GraphicalObject::Camera cam{ 0,0 };
	int VertexCount;
	float proportion;
	float BlockScale;
	Graphics* pGFX;
};

