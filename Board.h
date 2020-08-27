#pragma once
#include "DirectX.h"
#include "BindPack.h"
#include "GraphicalObject.h"
#include "Window.h"
#include "Entity.h"
#include "Creature.h"
#include <chrono>
#include <list>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
class Board
{
private:
	enum class AddingElem
	{
		Block,
		Creature
	};
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
	std::list<GraphicalObject* > Blocks;
	std::list<Creature* > Monsters;
	GraphicalObject::Camera cam{ 0,0 };
	bool lost = false;
	int VertexCount;
	float proportion;
	float BlockScale;
	bool BuilderMode = true;
	Graphics* pGFX;
	Entity* Mario = nullptr;
	AddingElem switcher = AddingElem::Block;
	TimePoint last;
	TimePoint old;
};

