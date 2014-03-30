/** @file MyTextCtrl.h
 *  Interface for the MyTextCtrl class.
 */

#ifndef MyTextCtrl_H
#define MyTextCtrl_H

#include "wxprec.h"

extern const wxEventType wxEVT_LOSEFOCUS;

class MyTextCtrl : public wxTextCtrl
{
public:
	MyTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = "", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxTextCtrlNameStr);
protected:
	void OnKillFocus(wxFocusEvent & event);
	DECLARE_EVENT_TABLE()
};


#endif // ifndef MyTextCtrl_H
