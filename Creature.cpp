#include "Creature.h"
#include <functional>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace DirectX;
using namespace std;


class Comparision
{
public:
	bool operator()(pair<GraphicalObject*, float >& p1, pair<GraphicalObject*, float >& p2)
	{
		return p1.second > p2.second;
	}
};

/*Creature::Creature(Graphics* gfx, std::wstring path, float OffsetX, float OffsetY, float ScaleX, float ScaleY, float RotationAngle)
	:
	GraphicalObject(gfx,path,OffsetX,OffsetY,ScaleX,ScaleY,RotationAngle)
{
}*/

void Creature::UpdatePos(std::list<GraphicalObject*>& Blocks, float Time)
{
	if (!isDead)
	{
		auto CreatureRect = GetRect();

		XMFLOAT2 MoveVec = Vel;

		XMFLOAT2 contact_point;
		XMFLOAT2 contact_normal{ 0,0 };
		float contact_time;

		XMFLOAT2 senVel = { MoveVec.x * Time,MoveVec.y * Time };
		priority_queue<pair<GraphicalObject*, float>, vector<pair<GraphicalObject*, float>>, Comparision> Rects;


		for (auto Block : Blocks)
		{
			if (DynamicRectVsRect(CreatureRect, senVel, Block->GetRect(), contact_point, contact_normal, contact_time))
			{
				Rects.push({ Block,contact_time });
			}
		}

		while (!Rects.empty())
		{
			auto Rect = Rects.top();
			Rects.pop();

			if (DynamicRectVsRect(CreatureRect, MoveVec, Rect.first->GetRect(), contact_point, contact_normal, contact_time))
			{
				MoveVec.x += contact_normal.x * (1.0f - contact_time) * abs(MoveVec.x);
				MoveVec.y += contact_normal.y * (1.0f - contact_time) * abs(MoveVec.y);

				if (contact_normal.x == 1 || contact_normal.x == -1) Vel.x = -Vel.x;
			}
		}

		Move(MoveVec.x * Time, MoveVec.y * Time);
	}
}

bool Creature::RectVsRey(const DirectX::XMFLOAT2& RayOrigin, const DirectX::XMFLOAT2& RayDir, const CollRect& rect,
	DirectX::XMFLOAT2& ContactPoint, DirectX::XMFLOAT2& ContactNormal, float& t_hit_near)
{
	XMFLOAT2 t_near{ (rect.TopLeft.x - RayOrigin.x) / RayDir.x,(rect.TopLeft.y - RayOrigin.y) / RayDir.y };
	XMFLOAT2 t_far{ (rect.BottomRight.x - RayOrigin.x) / RayDir.x,(rect.BottomRight.y - RayOrigin.y) / RayDir.y };

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;


	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

#ifdef max
#undef max
#endif 

#ifdef min
#undef min
#endif 

	t_hit_near = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0) return false;

	ContactPoint = { RayOrigin.x + t_hit_near * RayDir.x,RayOrigin.y + t_hit_near * RayDir.y };

	if (t_near.x > t_near.y)
		if (RayDir.x < 0)
			ContactNormal = { 1,0 };
		else
			ContactNormal = { -1,0 };
	else if (t_near.x < t_near.y)
		if (RayDir.y < 0)
			ContactNormal = { 0,1 };
		else
			ContactNormal = { 0,-1 };

	return true;
}

bool Creature::DynamicRectVsRect(const CollRect& in, DirectX::XMFLOAT2& Velocity, const CollRect& target,
	DirectX::XMFLOAT2& contact_point, DirectX::XMFLOAT2& contact_normal, float& contact_time)
{
	if (Velocity.x == 0 && Velocity.y == 0)
		return false;

	CollRect Expanded{ {0,0},{0,0} };

	XMFLOAT2 SizeIn{ abs(in.BottomRight.x - in.TopLeft.x),abs(in.BottomRight.y - in.TopLeft.y) };

	float x = target.TopLeft.x - SizeIn.x / 2.0f;
	Expanded.TopLeft = { target.TopLeft.x - SizeIn.x / 2.0f,target.TopLeft.y + SizeIn.y / 2.0f };
	Expanded.BottomRight.x = target.BottomRight.x + SizeIn.x / 2.0f;
	Expanded.BottomRight.y = target.BottomRight.y - SizeIn.y / 2.0f;



	if (RectVsRey(XMFLOAT2{ in.TopLeft.x + SizeIn.x / 2.0f, in.TopLeft.y - SizeIn.y / 2.0f }, Velocity, Expanded, contact_point, contact_normal, contact_time))
	{
		if (contact_time <= 1.0f)
		{
			return true;
		}
	}

	return false;
}

void Creature::Kill()
{
	isDead = true;
	SetUVCord(32, 47, 17, 32);
}
