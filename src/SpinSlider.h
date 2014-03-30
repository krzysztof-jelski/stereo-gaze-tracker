/** @file SpinSlider.h
 *  Interface for the SpinSlider class.
 */

#ifndef SPINSLIDER_H
#define SPINSLIDER_H

#include "wxprec.h"

//BEGIN_DECLARE_EVENT_TYPES()
//	DECLARE_EVENT_TYPE(wxEVT_SPINSLIDER, -1)
//END_DECLARE_EVENT_TYPES()
extern const wxEventType wxEVT_SPINSLIDER;


class SpinSlider : public wxPanel  
{
protected:
	// control ids
	enum
	{
		wxID_SLIDER = 7005,
		wxID_SPINCTRL
	};
public:
	SpinSlider(wxWindow* parent,
		wxWindowID id = -1,
		int value = 0,
		int min = 0,
		int max = 100,
		const wxString& label = wxEmptyString,
		const wxString& info = wxEmptyString,
		const wxPoint& point = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0, // to be used in the future
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = "spin_slider"
		);
	virtual ~SpinSlider();
	wxString GetName();
	void SetValue(long newValue);
	long GetValue() const;
	void SetLabelWidth(int newWidth);
	int GetLabelWidth() const;
protected:
	void DoLayout();
	void OnSpinCtrl(wxSpinEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnText(wxCommandEvent& event);
	void SendEvent();

	bool m_bSettingProcess;
	wxSlider* m_slider;
	wxSpinCtrl* m_spinctrl;
	wxBoxSizer* m_sizer;
	wxStaticText* m_label;

	DECLARE_EVENT_TABLE()


};


#endif // ifndef SPINSLIDER_H
