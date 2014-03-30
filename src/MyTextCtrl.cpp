// MyTextCtrl.cpp: implementation of the MyTextCtrl class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "MyTextCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(MyTextCtrl, wxControl)
	EVT_KILL_FOCUS(MyTextCtrl::OnKillFocus)
END_EVENT_TABLE()

const wxEventType wxEVT_LOSEFOCUS = wxNewEventType();

MyTextCtrl::MyTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name) :
	wxTextCtrl(parent, id, value, pos, size, style, validator, name)
{
}
void MyTextCtrl::OnKillFocus(wxFocusEvent & event)
{
	wxCommandEvent newEvent(wxEVT_LOSEFOCUS, GetId());
    newEvent.SetEventObject(this);
    // Send it
    GetEventHandler()->ProcessEvent(newEvent);
}
