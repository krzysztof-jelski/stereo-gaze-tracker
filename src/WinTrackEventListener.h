// WinTrackEventListener.h: interface for the WinTrackEventListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined _WINTRACKEVENTLISTENER_H_
#define _WINTRACKEVENTLISTENER_H_

#define _WIN32_WINNT 0x800000
#include <windows.h>
#include <winuser.h>

#include "TrackEventListener.h"


class WinTrackEventListener : public TrackEventListener  
{
protected:
	enum States
{
	ON,
	OFF
};
public:
	WinTrackEventListener();
	virtual ~WinTrackEventListener();

	virtual void On();
	virtual void Off();
	virtual void Toggle();
	virtual int MoveMouse(int x, int y);
	virtual int MoveMouseAbsolute(long x, long y);
	virtual int ClickMouse();
	virtual int DoubleClickMouse();
	virtual int MouseDown();
	virtual int MouseUp();
protected:
	States state;

};

#endif // !defined _WINTRACKEVENTLISTENER_H_
