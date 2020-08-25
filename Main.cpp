#include "Window.h"
#include "GraphicalObject.h"

int main()
{
	Window wnd(1600, 900, L"klasa", L"HUJ");
	wnd.InitDx11();

	GraphicalObject obj(wnd.GetGraphicsPointer(), L"D:\\C++\\Programy C++\\2DGame\\Blocks.png");

	obj.Scale(0.3, 0.3);
	obj.Move(0.2, -0.2);
	obj.SetUVCord(20, 50, 20, 50);

	while (wnd.ProcessMessages() ==0)
	{
		if (wnd.IsKeyPressed('L')) obj.Rotate(0.9);

		wnd.DX_BeginFrame();
		obj.Draw();
		wnd.DX_EndFrame();
	}
}