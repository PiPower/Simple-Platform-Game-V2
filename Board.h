#pragma once
#include "DirectX.h"
#include "BindPack.h"
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
	void Draw();
private:
	std::vector<BindBase* >ScreenBinds;
	int VertexCount;
	float proportion;
	float BlockScale;
	Graphics* pGFX;
};

