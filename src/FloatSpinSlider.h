/** @file FloatSpinSlider.h
 *  Interface for the FloatSpinSlider class.
 */

#ifndef FloatSpinSlider_H
#define FloatSpinSlider_H

#include "wxprec.h"
#include "FloatSpinCtrl.h"

extern const wxEventType wxEVT_FLOATSPINSLIDER;

class FloatSpinSlider : public wxPanel  
{
protected:
	// control ids
	enum
	{
		wxID_SLIDER = 7003,
		wxID_SPINCTRL
	};
public:
	FloatSpinSlider(wxWindow* parent,
		wxWindowID id = -1,
		double value = 0,
		double min = 0,
		double max = 100,
		double stepSpin = 1,
		double stepSlider = 0.5,
		const wxString& label = wxEmptyString,
		const wxString& info = wxEmptyString,
		const wxPoint& point = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = "float_spin_slider"
		);
	virtual ~FloatSpinSlider();
	wxString GetName();
	void SetValue(double newValue);
	void SetRange(double min, double max);
	double GetValue() const;
	void SetLabelWidth(int newWidth);
	int GetLabelWidth() const;
protected:
	void DoLayout();
	void OnSpinCtrl(wxCommandEvent& event);
	void OnScroll(wxScrollEvent& event);
//	void OnText(wxCommandEvent& event);
	void SendEvent();
	void CalcSliderValues();
	void CalcSliderValue();
	void UpdateMinMax();

	bool m_bSettingProcess;
	wxSlider* m_slider;
	FloatSpinCtrl* m_spinctrl;
	wxBoxSizer* m_sizer;
	wxStaticText* m_label;
	double m_Min, m_Max, m_Value, m_StepSpin, m_StepSlider, m_Range;
	long m_SliderMin, m_SliderMax, m_SliderValue;
	DECLARE_EVENT_TABLE()


};


#endif // ifndef FloatSpinSlider_H
