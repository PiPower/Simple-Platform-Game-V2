#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include <bitset>
#include <queue>
#include <algorithm>
#include <objidl.h>
#include <gdiplusenums.h>
#include <gdiplus.h>
#include "DirectX.h"
#include <chrono>


typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

class Window
{
public:
	struct KeyEvent
	{

		enum class Event
		{
			Press,
			Release,
			Invalid
		};
		KeyEvent(unsigned char code, Event type) noexcept
			:
			Code(code), Type(type)
		{}
		const unsigned char Code;
		const Event Type;
	};

	struct MouseEvent
	{

		enum class Event
		{
			LeftPress,
			LeftRelease,
			RightPress,
			RightRelease,
			WheelPrees,
			WheelRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
		MouseEvent(int x, int y, Event type) noexcept
			:
			x(x), y(y), Type(type)
		{}
		const int x;
		const int y;
		const Event Type;
	};

public:
	Window(int width, int height, std::wstring CLassName, std::wstring WndName);
	int ProcessMessages() noexcept;
	void SetFPS();
	void DrawMessageBox(std::wstring mes);
	~Window();
	// Keyboard ------------------------------------
	bool IsKeyPressed(unsigned char key);
	wchar_t GetChar();
	bool IsCharEmpty();
	bool IsKeyboardEventEmpty();
	Window::KeyEvent ReadKeyEvent();
	void ClearKeyEvent();
	void ClearCharQueue();
	// Mouse ---------------------------------------
	bool IsRightPressed() noexcept;
	bool IsLeftPressed() noexcept;
	bool IsMiddlePressed() noexcept;
	int GetMousePosX() noexcept;
	int GetMousePosY() noexcept;
	float GetMousePosXNormalized() noexcept;
	float GetMousePosYNormalized() noexcept;
	bool IsMouseEventEmpty();
	Window::MouseEvent ReadMouseEvent();
	void ClearMouseQueue();
	//GraphicsStuff
	void InitDx11();
	void DX_BeginFrame(const float& R=0, const float& G=0, const float& B=0, const float& A=0);
	Graphics* GetGraphicsPointer() { return pDx11; }
	void DX_EndFrame();
	//------------------------
	void SimpleTypeBox();
private:
	static LRESULT CALLBACK  HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(UINT msg, WPARAM wParam, LPARAM lParam);
private:
	std::wstring CLASS_NAME;
	bool Dx11Init = false;
	HINSTANCE Hinstace;
	HWND hwnd;
	int width;
	int height;
	int QueueLimit = 13;
	// Keyboard ------------------------------------
	std::bitset<256> KeyStates;
	std::queue<wchar_t> CharQueue;
	std::queue<KeyEvent> KeyQueue;
	// Mouse ---------------------------------------
	bool LeftPress = false;
	bool RightPress = false;
	bool MiddlePress = false;
	int ScrollAcumulate = 0;
	int ScrollDelta;
	int PosX;
	int PosY;
	std::queue<MouseEvent> MouseQueue;
	// Graphics ------------------------------------
	std::wstring lol;
	std::wstring WindowName;

	Graphics*  pDx11 = nullptr;
	TimePoint last;
	TimePoint old;
};

