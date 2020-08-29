#pragma once
#include "DirectX.h"
#include "BindPack.h"
#include "GraphicalObject.h"
#include "Window.h"
#include "Entity.h"
#include "Creature.h"
#include <chrono>
#include <list>
#include <fstream>

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
	void SaveBoard(std::string path);
	void LoadBoard(std::string path);
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

