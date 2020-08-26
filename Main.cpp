#include "Window.h"
#include "GraphicalObject.h"
#include "Board.h"


int main()
{
	Window wnd(1600, 900, L"klasa", L"HUJ");
	wnd.InitDx11();

	/*GraphicalObject obj(wnd.GetGraphicsPointer(), L"D:\\C++\\Programy C++\\2DGame\\Blocks.png");

	obj.Scale(0.3, 0.3);
	obj.Move(0.2, -0.2);
	obj.SetUVCord(20, 50, 20, 50);*/

	Board bd(wnd.GetGraphicsPointer(),0.06);
	while (wnd.ProcessMessages() ==0)
	{
		bd.Controll(wnd);

		wnd.DX_BeginFrame(1,1,1);
		bd.Draw();
		wnd.DX_EndFrame();
	}

}