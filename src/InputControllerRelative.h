// InputControllerRelative.h: interface for the InputControllerRelative class.
//
//////////////////////////////////////////////////////////////////////

#if !defined _InputControllerRelative_H_
#define _InputControllerRelative_H_


#include "wxprec.h"
#include "WinTrackEventListener.h"
#include "InputController.h"

class InputControllerRelative : public InputController  
{
public:
	InputControllerRelative();
	virtual ~InputControllerRelative();
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

#endif // !defined _InputControllerRelative_H_
