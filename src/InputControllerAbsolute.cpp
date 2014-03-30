// InputControllerAbsolute.cpp: implementation of the InputControllerAbsolute class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "InputControllerAbsolute.h"
#include "GlobalConfig.h"

InputControllerAbsolute::InputControllerAbsolute() : 
	m_initDone(false),
	m_sensitivity(* (double *) (*GlobalConfig::GetInstance()["Mouse"])["sensitivity"]->GetValue()),
	m_activated(* (long *) (*GlobalConfig::GetInstance()["Mouse"])["activated"]->GetValue()),
	m_clickDepth(* (double *) (*GlobalConfig::GetInstance()["Mouse"])["clickDepth"]->GetValue()),
	m_isMouseDown(false)
{
}

InputControllerAbsolute::~InputControllerAbsolute()
{
}

void InputControllerAbsolute::Toggle()
{
	m_listener.Toggle();
}

void InputControllerAbsolute::On()
{
	m_listener.On();
}

void InputControllerAbsolute::Off()
{
	m_listener.Off();
}
void InputControllerAbsolute::Init(float x, float y, float z)
{
	m_iniX = x;
	m_iniY = y;
	m_iniZ = z;
}

void InputControllerAbsolute::Process(float x, float y, float z)
{
	if (!m_activated)
		return;
	float dx = -x + m_iniX;
	float dy = y - m_iniY;
	float dz = fabs(z - m_iniZ);
	int xmove = (65535 / 2) + dx * (65535 / 2) / (100 / m_sensitivity);
	int ymove = (65535 / 2) - dy * (65535 / 2) / (100 / m_sensitivity);
	m_listener.MoveMouseAbsolute(xmove, ymove);
	if (dz > m_clickDepth)
	{
		if (!m_isMouseDown)
		{
			m_listener.MouseDown();
			m_isMouseDown = true;
		}
	}
	else
	{
		if (m_isMouseDown)
		{
			m_listener.MouseUp();
			m_isMouseDown = false;
		}
	}
}

bool InputControllerAbsolute::IsMouseDown()
{
	return m_isMouseDown;
}