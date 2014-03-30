// FloatSpinCtrl.cpp: implementation of the FloatSpinCtrl class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "FloatSpinCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(FloatSpinCtrl, wxPanel)
	EVT_SPIN_UP(FloatSpinCtrl::wxID_SPINBUTTON, FloatSpinCtrl::OnSpinUp)
	EVT_SPIN_DOWN(FloatSpinCtrl::wxID_SPINBUTTON, FloatSpinCtrl::OnSpinDown)
	EVT_TEXT_ENTER(FloatSpinCtrl::wxID_TEXTCTRL, FloatSpinCtrl::OnTextEnter)
	EVT_CUSTOM(wxEVT_LOSEFOCUS, FloatSpinCtrl::wxID_TEXTCTRL, FloatSpinCtrl::OnKillFocus)
END_EVENT_TABLE()

const wxEventType wxEVT_FLOATSPINCTRL = wxNewEventType();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FloatSpinCtrl::FloatSpinCtrl(wxWindow* parent,
	wxWindowID id,
	double value,
	double min,
	double max,
	double step,
	const wxPoint& point,
	const wxSize& size,
	long style,
	const wxString& name
	) :
	wxPanel(parent, id, point, size, style, name),
	m_bSettingProcess(false),
	m_Min(min),
	m_Max(max),
	m_Step(step),
	m_Value(value),
	m_NumericValidator(wxFILTER_NUMERIC)
{	
	m_textCtrl = new MyTextCtrl(this,
		FloatSpinCtrl::wxID_TEXTCTRL,
		"",
		wxDefaultPosition,
		wxSize(-1,-1),
		wxTE_PROCESS_ENTER,
		m_NumericValidator);
	m_spinButton = new wxSpinButton(this,
		FloatSpinCtrl::wxID_SPINBUTTON,
		wxDefaultPosition,
		wxSize(16, 21),
		wxSP_ARROW_KEYS | wxSP_VERTICAL);
	
	UpdateTextValue();

	m_sizer = new wxBoxSizer(wxHORIZONTAL);
	DoLayout();
}

FloatSpinCtrl::~FloatSpinCtrl()
{
}

void FloatSpinCtrl::DoLayout()
{	
    m_sizer->Add(m_textCtrl, 1, wxFIXED_MINSIZE | wxRIGHT, 1);
    m_sizer->Add(m_spinButton, 0, wxFIXED_MINSIZE, 0);

	SetAutoLayout(true);
	SetSizer(m_sizer);
	m_sizer->SetSizeHints(this);
	Layout();
	
}

void FloatSpinCtrl::OnSpinUp(wxSpinEvent& event)
{
	m_bSettingProcess = true;
	UpdateValue(m_Value + m_Step);
	m_bSettingProcess = false;
}

void FloatSpinCtrl::OnSpinDown(wxSpinEvent& event)
{
	m_bSettingProcess = true;
	UpdateValue(m_Value - m_Step);
	m_bSettingProcess = false;
}

void FloatSpinCtrl::OnKillFocus(wxEvent& event)
{
	ValidateTextValue();
}
void FloatSpinCtrl::OnTextEnter(wxCommandEvent& event)
{
	ValidateTextValue();
}

void FloatSpinCtrl::UpdateTextValue()
{
	wxString stringValue;
	stringValue.Printf("%.3f", m_Value);
	m_textCtrl->SetValue(stringValue);
}

void FloatSpinCtrl::UpdateValue(double newValue)
{
	if (newValue > m_Max)
		newValue = m_Max;
	if (newValue < m_Min)
		newValue = m_Min;
	m_Value = newValue;
	UpdateTextValue();
	SendEvent();
}

void FloatSpinCtrl::ValidateTextValue()
{
	m_bSettingProcess = true;
	wxString stringValue = m_textCtrl->GetValue();
	double temp;
	if (stringValue.ToDouble(&temp))
	{
		UpdateValue(temp);
	}
	else
	{
		UpdateTextValue();
	}
	m_bSettingProcess = false;
}

void FloatSpinCtrl::SendEvent()
{
	wxCommandEvent event(wxEVT_FLOATSPINCTRL, GetId());
	event.SetEventObject(this);
	// Give it some contents
	event.SetString(m_textCtrl->GetValue());
	// Send it
	GetEventHandler()->ProcessEvent(event);
}

void FloatSpinCtrl::SetValue(double newValue)
{
	UpdateValue(newValue);
}
double FloatSpinCtrl::GetValue() const
{
	return m_Value;
}

void FloatSpinCtrl::SetRange(double min, double max)
{
	m_Min = min;
	m_Max = max;
}