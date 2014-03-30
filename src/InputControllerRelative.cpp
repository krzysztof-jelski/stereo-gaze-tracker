// InputControllerRelative.cpp: implementation of the InputControllerRelative class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "InputControllerRelative.h"
#include "GlobalConfig.h"

InputControllerRelative::InputControllerRelative() : 
	m_initDone(false),
	m_sensitivity(* (double *) (*GlobalConfig::GetInstance()["Mouse"])["sensitivity"]->GetValue()),
	m_activated(* (long *) (*GlobalConfig::GetInstance()["Mouse"])["activated"]->GetValue()),
	m_clickDepth(* (double *) (*GlobalConfig::GetInstance()["Mouse"])["clickDepth"]->GetValue()),
	m_isMouseDown(false)
{
}

InputControllerRelative::~InputControllerRelative()
{
}

void InputControllerRelative::Toggle()
{
	m_listener.Toggle();
}

void InputControllerRelative::On()
{
	m_listener.On();
}

void InputControllerRelative::Off()
{
	m_listener.Off();
}
void InputControllerRelative::Init(float x, float y, float z)
{
	m_iniX = x;
	m_iniY = y;
	m_iniZ = z;
}

void InputControllerRelative::Process(float x, float y, float z)
{
	if (!m_activated)
		return;
	float dx = x - m_iniX;
	float dy = y - m_iniY;
	float dz = fabs(z - m_iniZ);
	int xmove = -dx * m_sensitivity;
	int ymove = -dy * m_sensitivity;
	m_listener.MoveMouse(xmove, ymove);
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

bool InputControllerRelative::IsMouseDown()
{
	return m_isMouseDown;
}