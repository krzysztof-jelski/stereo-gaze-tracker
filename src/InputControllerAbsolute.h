// InputControllerAbsolute.h: interface for the InputControllerAbsolute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined _InputControllerAbsolute_H_
#define _InputControllerAbsolute_H_


#include "wxprec.h"
#include "WinTrackEventListener.h"
#include "InputController.h"

class InputControllerAbsolute : public InputController  
{
public:
	InputControllerAbsolute();
	virtual ~InputControllerAbsolute();
	virtual void Toggle();
	virtual void On();
	virtual void Off();
	virtual void Process(float x, float y, float z);
	virtual void Init(float x, float y, float z);
	virtual bool IsMouseDown();

protected:
	WinTrackEventListener m_listener;
	bool m_initDone;
	float m_iniX, m_iniY, m_iniZ;
	float m_lastX, m_lastY, m_lastZ;
	bool m_isMouseDown;
	// params
	double &m_sensitivity;
	double &m_clickDepth;
	long &m_activated;
};

#endif // !defined _InputControllerAbsolute_H_
