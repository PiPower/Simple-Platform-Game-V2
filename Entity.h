#pragma once
#include "GraphicalObject.h"
#include "Window.h"
#include "Creature.h"
#include <list>

class Entity : public GraphicalObject
{

	enum LastDirection
	{
		Right,
		Standing,
		Left
	};
public:
	using::GraphicalObject::GraphicalObject;
	void UpdatePos(Window& wnd, float Time, Camera& cam, std::list<GraphicalObject*>& Blocks,bool BuilderMode);
	bool ContactWithMonstet(std::list<Creature*>& Creatures, float BlockScale);
	bool RectVsRey(const DirectX::XMFLOAT2& RayOrigin, const DirectX::XMFLOAT2& RayDir,
		 const CollRect& rect, DirectX::XMFLOAT2& ContactPoint, DirectX::XMFLOAT2& ContactNormal, float& t_hit_near);
	bool DynamicRectVsRect(const CollRect& in, DirectX::XMFLOAT2& Velocity, const CollRect& target, DirectX::XMFLOAT2& contact_point,
		DirectX::XMFLOAT2& contact_normal, float& contact_time);
private:
	float VelX = 0.7;
	float VelY = 1.0f;
	bool Jump = false;
	float JumpFactor = 0.0f;
	float Timer = 0;
	float FrameChange = 0.05;
	LastDirection  LastDir;
};

