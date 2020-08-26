#include "Entity.h"

using namespace DirectX;

void Entity::UpdatePos(Window& wnd, float Time, Camera& cam, std::vector<GraphicalObject*>& Blocks)
{

	XMFLOAT2 MoveVec = { 0,-0.6f };

	if (wnd.IsKeyPressed('D')) MoveVec.x += VelX;
	if (wnd.IsKeyPressed('A')) MoveVec.x += -VelX;
	if (wnd.IsKeyPressed('W'))MoveVec.y += VelY;
	if (wnd.IsKeyPressed('S')) MoveVec.y += -VelY;

	Move(MoveVec.x * Time, MoveVec.y * Time);

	CollRect PlayerRect = GetRect();
	if (PlayerRect.TopLeft.x + cam.X < -1.0|| PlayerRect.BottomRight.x + cam.X > 1.0)  cam.X += -MoveVec.x * Time;
}
