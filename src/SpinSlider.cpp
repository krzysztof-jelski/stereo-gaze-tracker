// SpinSlider.cpp: implementation of the SpinSlider class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "SpinSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(SpinSlider, wxPanel)
	EVT_SPINCTRL(SpinSlider::wxID_SPINCTRL, SpinSlider::OnSpinCtrl)
	EVT_COMMAND_SCROLL(SpinSlider::wxID_SLIDER, SpinSlider::OnScroll)
	EVT_TEXT(SpinSlider::wxID_SPINCTRL, SpinSlider::OnText)
END_EVENT_TABLE()

//DEFINE_EVENT_TYPE(wxEVT_SPINSLIDER)
const wxEventType wxEVT_SPINSLIDER = wxNewEventType();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpinSlider::SpinSlider(wxWindow* parent,
	wxWindowID id,
	int value,
	int min,
	int max,
	const wxString& label,
	const wxString& info,
	const wxPoint& point,
	const wxSize& size,
	long style, // to be used in the future
	const wxValidator& validator,
	const wxString& name
	) :
	wxPanel(parent, id, point, size, style, name),
	m_bSettingProcess(false)
{
	m_slider = new wxSlider(this,
		SpinSlider::wxID_SLIDER,
		value,
		min,
		max,
		wxDefaultPosition,
        wxSize(20,-1));
	m_spinctrl = new wxSpinCtrl(this,
		SpinSlider::wxID_SPINCTRL,
		wxEmptyString,
		wxDefaultPosition,
		wxSize(30,-1),
		wxSP_ARROW_KEYS,
		min,
		max,
		value);
	m_label = new wxStaticText(this, -1, label, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	this->SetToolTip(info);
	m_spinctrl->SetValue(value);
	m_sizer = new wxBoxSizer(wxHORIZONTAL);
	DoLayout();


}

SpinSlider::~SpinSlider()
{
	m_slider->Destroy();
	m_spinctrl->Destroy();

}

void SpinSlider::DoLayout()
{
	m_sizer->Add(m_label, 0, wxALIGN_CENTER_VERTICAL | wxFIXED_MINSIZE);
	m_sizer->Add(m_slider, 2, wxFIXED_MINSIZE);
	m_sizer->Add(m_spinctrl, 1, wxFIXED_MINSIZE);
	SetAutoLayout(true);
	SetSizer(m_sizer);
	m_sizer->Fit(this);
	Layout();
}
void SpinSlider::OnSpinCtrl(wxSpinEvent& event)
{
//	int pos = event.GetPosition();
//	m_slider->SetValue(pos);
//	SendEvent();
}
void SpinSlider::OnScroll(wxScrollEvent& event)
{
	int pos = event.GetPosition();
	m_bSettingProcess = true;
	m_spinctrl->SetValue(pos);
//	m_spinctrl->SetValue("43,4");
	m_bSettingProcess = false;
	SendEvent();
}
void SpinSlider::OnText(wxCommandEvent& event)
{
	if (m_bSettingProcess)
		return;
	m_slider->SetValue(m_spinctrl->GetValue());
	SendEvent();

}

void SpinSlider::SendEvent()
{
	static int lastValue = m_slider->GetValue();
	int currentValue = m_slider->GetValue();

	wxCommandEvent event(wxEVT_SPINSLIDER, GetId());
	event.SetEventObject(this);
	// Give it some contents
	event.SetString(m_label->GetLabel());
	event.SetInt(m_slider->GetValue());
	// Send it
	GetEventHandler()->ProcessEvent( event );
}

wxString SpinSlider::GetName()
{
	return m_label->GetLabel();
}

void SpinSlider::SetValue(long newValue)
{
	m_spinctrl->SetValue(newValue);
	SendEvent();
}

long SpinSlider::GetValue() const
{
	return m_spinctrl->GetValue();
}

int SpinSlider::GetLabelWidth() const
{
	int width, height;
	m_label->GetSize(&width, &height);
	return width;
}

void SpinSlider::SetLabelWidth(int newWidth)
{
	int width, height;
	m_label->GetSize(&width, &height);
	m_label->SetBestFittingSize(wxSize(newWidth, height));
	Layout();
}