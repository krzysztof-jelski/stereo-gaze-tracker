// TrackEventListener.h: interface for the TrackEventListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined _TRACKEVENTLISTENER_H_
#define _TRACKEVENTLISTENER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TrackEventListener  
{
public:
	TrackEventListener();
	virtual ~TrackEventListener();

	virtual void On()=0;
	virtual void Off()=0;
	virtual void Toggle()=0;
	virtual int MoveMouse(int x, int y)=0;
	virtual int MoveMouseAbsolute(long x, long y)=0;
	virtual int ClickMouse()=0;
	virtual int DoubleClickMouse()=0;
	virtual int MouseDown()=0;
	virtual int MouseUp()=0;

};

#endif // !defined _TRACKEVENTLISTENER_H_
