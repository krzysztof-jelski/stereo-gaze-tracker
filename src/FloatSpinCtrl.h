/** @file FloatSpinCtrl.h
 *  Interface for the FloatSpinCtrl class.
 */

#ifndef FloatSpinCtrl_H
#define FloatSpinCtrl_H

#include "wxprec.h"
#include "MyTextCtrl.h"

extern const wxEventType wxEVT_FLOATSPINCTRL;

class FloatSpinCtrl : public wxPanel
{
protected:
	// control ids
	enum
	{
		wxID_SPINBUTTON = 7001,
		wxID_TEXTCTRL
	};
public:
	FloatSpinCtrl(wxWindow* parent,
		wxWindowID id = -1,
		double value = 0,
		double min = 0,
		double max = 100,
		double step = 1,
		const wxPoint& point = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0, // to be used in the future
		const wxString& name = "spin_ctrl"
		);
	virtual ~FloatSpinCtrl();
	void SetValue(double newValue);
	double GetValue() const;
	void SetRange(double min, double max);
protected:
	void DoLayout();
	void OnSpinUp(wxSpinEvent& event);
	void OnSpinDown(wxSpinEvent& event);
	void OnTextEnter(wxCommandEvent& event);
	void OnKillFocus(wxEvent& event);
	void ValidateTextValue();
	void UpdateTextValue();
	void UpdateValue(double newValue);
	void SendEvent();

	bool m_bSettingProcess;
	wxSpinButton* m_spinButton;
	MyTextCtrl* m_textCtrl;
	wxBoxSizer* m_sizer;
	double m_Min, m_Max, m_Step, m_Value;
	wxString m_StringValue;
	wxTextValidator m_NumericValidator;

	DECLARE_EVENT_TABLE()


};


#endif // ifndef FloatSpinCtrl_H
