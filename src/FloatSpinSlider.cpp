// FloatSpinSlider.cpp: implementation of the FloatSpinSlider class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "FloatSpinSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(FloatSpinSlider, wxPanel)
	EVT_COMMAND_SCROLL(FloatSpinSlider::wxID_SLIDER, FloatSpinSlider::OnScroll)
	EVT_COMMAND(FloatSpinSlider::wxID_SPINCTRL, wxEVT_FLOATSPINCTRL, FloatSpinSlider::OnSpinCtrl)
END_EVENT_TABLE()

const wxEventType wxEVT_FLOATSPINSLIDER = wxNewEventType();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FloatSpinSlider::FloatSpinSlider(wxWindow* parent,
	wxWindowID id,
	double value,
	double min,
	double max,
	double stepSpin,
	double stepSlider,
	const wxString& label,
	const wxString& info,
	const wxPoint& point,
	const wxSize& size,
	long style,
	const wxString& name
	) :
	wxPanel(parent, id, point, size, style, name),
	m_bSettingProcess(false),
	m_Min(min), m_Max(max), m_Value(value), m_StepSpin(stepSpin), m_StepSlider(stepSlider)
{
	CalcSliderValues();
	m_slider = new wxSlider(this,
		FloatSpinSlider::wxID_SLIDER,
		m_SliderValue,
		m_SliderMin,
		m_SliderMax,
		wxDefaultPosition,
        wxSize(20,-1));
	m_spinctrl = new FloatSpinCtrl(this,
		FloatSpinSlider::wxID_SPINCTRL,
		value,
		m_Min,
		m_Max,
		m_StepSpin,
		wxDefaultPosition,
		wxSize(40,-1));
	m_label = new wxStaticText(this, -1, label, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	m_label->SetToolTip(info);
	m_sizer = new wxBoxSizer(wxHORIZONTAL);
	DoLayout();

}

FloatSpinSlider::~FloatSpinSlider()
{
	m_slider->Destroy();
	m_spinctrl->Destroy();

}

void FloatSpinSlider::DoLayout()
{
	m_sizer->Add(m_label, 0, wxALIGN_CENTER_VERTICAL | wxFIXED_MINSIZE);
	m_sizer->Add(m_slider, 2, wxFIXED_MINSIZE);
	m_sizer->Add(m_spinctrl, 1);
	SetAutoLayout(true);
	SetSizer(m_sizer);
	m_sizer->Fit(this);
	Layout();
}
void FloatSpinSlider::OnSpinCtrl(wxCommandEvent& event)
{
	if (m_bSettingProcess)
		return;
	m_bSettingProcess = true;
	m_Value = m_spinctrl->GetValue();
	CalcSliderValue();
	m_slider->SetValue(m_SliderValue);
	SendEvent();
	m_bSettingProcess = false;
}
void FloatSpinSlider::OnScroll(wxScrollEvent& event)
{
	if (m_bSettingProcess)
		return;
	int pos = event.GetPosition();
	m_bSettingProcess = true;
	m_spinctrl->SetValue(m_Min + pos * m_StepSlider);
	m_Value = m_spinctrl->GetValue();
	m_bSettingProcess = false;
	SendEvent();
}
/*void FloatSpinSlider::OnText(wxCommandEvent& event)
{
	if (m_bSettingProcess)
		return;
	m_slider->SetValue(m_spinctrl->GetValue());
	SendEvent();

}
*/
void FloatSpinSlider::SendEvent()
{
	static int lastValue = m_slider->GetValue();
	int currentValue = m_slider->GetValue();

	wxCommandEvent event(wxEVT_FLOATSPINSLIDER, GetId());
	event.SetEventObject(this);
	// Give it some contents
	event.SetString(m_label->GetLabel());
	event.SetInt(m_slider->GetValue());
	// Send it
	GetEventHandler()->ProcessEvent( event );
}

wxString FloatSpinSlider::GetName()
{
	return m_label->GetLabel();
}

void FloatSpinSlider::SetValue(double newValue)
{
	if (newValue < m_Min)
		newValue = m_Min;
	else if (newValue > m_Max)
		newValue = m_Max;
	m_Value = newValue;
	m_spinctrl->SetValue(m_Value);
}
double FloatSpinSlider::GetValue() const
{
	return m_Value;
}

void FloatSpinSlider::SetRange(double min, double max)
{
	m_Min = min;
	m_Max = max;
	UpdateMinMax();
}

void FloatSpinSlider::CalcSliderValues()
{
	m_Range = m_Max - m_Min;
	long sliderRange = m_Range / m_StepSlider;
	m_SliderMin = 0;
	m_SliderMax = sliderRange;
	CalcSliderValue();
}

void FloatSpinSlider::CalcSliderValue()
{
	m_SliderValue = (m_Value - m_Min) / m_StepSlider;
}

int FloatSpinSlider::GetLabelWidth() const
{
	int width, height;
	m_label->GetSize(&width, &height);
	return width;
}

void FloatSpinSlider::SetLabelWidth(int newWidth)
{
	int width, height;
	m_label->GetSize(&width, &height);
	m_label->SetBestFittingSize(wxSize(newWidth, height));
	Layout();
}

void FloatSpinSlider::UpdateMinMax()
{
	CalcSliderValues();
	m_slider->SetMax(m_SliderMax);
	m_slider->SetMin(m_SliderMin);
	m_slider->SetValue(m_SliderValue);
	m_spinctrl->SetRange(m_Min, m_Max);
}
