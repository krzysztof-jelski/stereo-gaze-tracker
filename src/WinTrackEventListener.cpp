// WinTrackEventListener.cpp: implementation of the WinTrackEventListener class.
//
//////////////////////////////////////////////////////////////////////

#include "WinTrackEventListener.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WinTrackEventListener::WinTrackEventListener()
{
	state = OFF;
}

WinTrackEventListener::~WinTrackEventListener()
{

}

void WinTrackEventListener::On()
{
	state = ON;
}

void WinTrackEventListener::Off()
{
	state = OFF;
}

void WinTrackEventListener::Toggle()
{
	if (state == OFF)
		On();
	else
		Off();
}

int WinTrackEventListener::MoveMouse(int x, int y)
{
	if (state == OFF)
		return 0;
	
	MOUSEINPUT stMI;

	stMI.dx = x;
	stMI.dy = y;
	stMI.mouseData = 0;
	stMI.dwFlags = MOUSEEVENTF_MOVE;
	stMI.time = 0;
	stMI.dwExtraInfo = 0;

	INPUT stI;

	stI.type = INPUT_MOUSE;
	stI.mi = stMI;

	return SendInput(1, &stI, sizeof(stI));

}

int WinTrackEventListener::MoveMouseAbsolute(long x, long y)
{
	if (state == OFF)
		return 0;
	
	MOUSEINPUT stMI;

	stMI.dx = x;
	stMI.dy = y;
	stMI.mouseData = 0;
	stMI.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	stMI.time = 0;
	stMI.dwExtraInfo = 0;

	INPUT stI;

	stI.type = INPUT_MOUSE;
	stI.mi = stMI;

	return SendInput(1, &stI, sizeof(stI));

}

int WinTrackEventListener::MouseDown()
{
	if (state == OFF)
		return 0;

	MOUSEINPUT stMI;

	stMI.dx = 0;
	stMI.dy = 0;
	stMI.mouseData = 0;
	stMI.dwFlags = MOUSEEVENTF_LEFTDOWN;
	stMI.time = 0;
	stMI.dwExtraInfo = 0;

	INPUT stI;

	stI.type = INPUT_MOUSE;
	stI.mi = stMI;

	return SendInput(1, &stI, sizeof(stI));
	
}
int WinTrackEventListener::MouseUp()
{
	if (state == OFF)
		return 0;

	MOUSEINPUT stMI;

	stMI.dx = 0;
	stMI.dy = 0;
	stMI.mouseData = 0;
	stMI.dwFlags = MOUSEEVENTF_LEFTUP;
	stMI.time = 0;
	stMI.dwExtraInfo = 0;

	INPUT stI;

	stI.type = INPUT_MOUSE;
	stI.mi = stMI;

	return SendInput(1, &stI, sizeof(stI));
	
}

int WinTrackEventListener::ClickMouse()
{
	if (state == OFF)
		return 0;

	MouseDown();
	MouseUp();
	return 1;
}

int WinTrackEventListener::DoubleClickMouse()
{
	if (state == OFF)
		return 0;

	ClickMouse();
	ClickMouse();
	return 1;
}

