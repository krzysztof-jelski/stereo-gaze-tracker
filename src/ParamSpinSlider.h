/** @file ParamSpinSlider.h
 *  Interface for the ParamSpinSlider class.
 */

#ifndef ParamSpinSlider_H
#define ParamSpinSlider_H

#include "wxprec.h"
#include "Parameter.h"
#include "FloatSpinSlider.h"
#include "SpinSlider.h"
#include "Observer.h"

class ParamSpinSlider : public wxPanel, public Observer
{
protected:
	// control ids
	enum
	{
		wxID_SPINCTRL = 7007,
		wxID_CHKPERCENT,
		wxID_SLIDERPERCENT
	};
public:
	ParamSpinSlider(wxWindow* parent,
		wxWindowID id,
		Parameter *param,
		const wxPoint& point = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0, // to be used in the future
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = "param_spin_slider"
		);
	virtual ~ParamSpinSlider();
	void SetLabelWidth(int newWidth);
	int GetLabelWidth() const;
	virtual void Update(Observable *observable);
protected:
	void DoLayout();
	void UpdatePercentVisibility();
	void OnFloatSpinSlider(wxCommandEvent& event);
	void OnSpinSlider(wxCommandEvent& event);
	void OnChkPercent(wxCommandEvent& event);
	void OnPercentSlider(wxCommandEvent& event);
	bool m_bSettingProcess;
	FloatSpinSlider* m_floatSpinSlider;
	FloatSpinSlider* m_percentSpinSlider;
	SpinSlider* m_SpinSlider;
	wxCheckBox* m_chkPercent;
	wxBoxSizer* m_sizer;
	Parameter * m_pParam;
	DECLARE_EVENT_TABLE()


};


#endif // ifndef ParamSpinSlider_H
