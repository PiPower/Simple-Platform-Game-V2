#pragma once
#include "GraphicalObject.h"
#include <list>


class Creature : public GraphicalObject
{
public:
	using::GraphicalObject::GraphicalObject;

	void UpdatePos(std::list<GraphicalObject*>& Blocks,float Time);
	bool RectVsRey(const DirectX::XMFLOAT2& RayOrigin, const DirectX::XMFLOAT2& RayDir,
		const CollRect& rect, DirectX::XMFLOAT2& ContactPoint, DirectX::XMFLOAT2& ContactNormal, float& t_hit_near);
	bool DynamicRectVsRect(const CollRect& in, DirectX::XMFLOAT2& Velocity, const CollRect& target, DirectX::XMFLOAT2& contact_point,
		DirectX::XMFLOAT2& contact_normal, float& contact_time);
private:
	DirectX::XMFLOAT2 Vel{ 0.6,-0.6 };
};

