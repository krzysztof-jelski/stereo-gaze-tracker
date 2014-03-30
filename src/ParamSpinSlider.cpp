// ParamSpinSlider.cpp: implementation of the ParamSpinSlider class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "ParamSpinSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(ParamSpinSlider, wxPanel)
	EVT_COMMAND(ParamSpinSlider::wxID_SPINCTRL, wxEVT_FLOATSPINSLIDER, ParamSpinSlider::OnFloatSpinSlider)
	EVT_COMMAND(ParamSpinSlider::wxID_SPINCTRL, wxEVT_SPINSLIDER, ParamSpinSlider::OnSpinSlider)
	EVT_COMMAND(ParamSpinSlider::wxID_SLIDERPERCENT, wxEVT_FLOATSPINSLIDER, ParamSpinSlider::OnPercentSlider)
	EVT_CHECKBOX(ParamSpinSlider::wxID_CHKPERCENT, ParamSpinSlider::OnChkPercent)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ParamSpinSlider::ParamSpinSlider(wxWindow* parent,
	wxWindowID id,
	Parameter *param,
	const wxPoint& point,
	const wxSize& size,
	long style, // to be used in the future
	const wxValidator& validator,
	const wxString& name
	) :
	wxPanel(parent, id, point, size, style, name),
	m_bSettingProcess(false),
	m_pParam(param),
	m_SpinSlider(NULL)
{
	if (m_pParam->GetType() == Parameter::LONG)
	{
		m_SpinSlider = new SpinSlider(this,
			ParamSpinSlider::wxID_SPINCTRL,
			*(long*)m_pParam->GetValue(),
			*(long*)m_pParam->GetMin(),
			*(long*)m_pParam->GetMax(),
			m_pParam->GetName(),
			m_pParam->GetInfo(),
			wxDefaultPosition,
			wxDefaultSize);
	}
	else
	{
		m_floatSpinSlider = new FloatSpinSlider(this,
			ParamSpinSlider::wxID_SPINCTRL,
			*(double*)m_pParam->GetValue(),
			*(double*)m_pParam->GetMin(),
			*(double*)m_pParam->GetMax(),
			*(double*)m_pParam->GetStep(),
			*(double*)m_pParam->GetStep() / 2.0,
			m_pParam->GetName(),
			m_pParam->GetInfo(),
			wxDefaultPosition,
			wxDefaultSize);
	}
	m_chkPercent = new wxCheckBox(this,
		ParamSpinSlider::wxID_CHKPERCENT,
		wxEmptyString);
	m_chkPercent->SetValue(m_pParam->IsPercentModification());
	m_chkPercent->SetToolTip("Show in percent");
	if (m_pParam->IsPercentAvail())
	{
		m_percentSpinSlider = new FloatSpinSlider(this,
				ParamSpinSlider::wxID_SLIDERPERCENT,
				m_pParam->GetPercValue(),
				m_pParam->GetPercMin(),
				m_pParam->GetPercMax(),
				1.0,
				0.5,
				m_pParam->GetName(),
				m_pParam->GetInfo(),
				wxDefaultPosition,
				wxDefaultSize);
	}
	m_sizer = new wxBoxSizer(wxHORIZONTAL);
	DoLayout();
	m_pParam->AddObserver(this);

}

ParamSpinSlider::~ParamSpinSlider()
{
	if (m_pParam != NULL)
		m_pParam->RemoveObserver(this);
}

void ParamSpinSlider::DoLayout()
{
//	m_sizer->Add(m_label, 0, wxALIGN_CENTER_VERTICAL);
//	m_sizer->Add(m_slider, 1);
	m_sizer->Add(m_chkPercent, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
	if (m_pParam->GetType() == Parameter::LONG)
		m_sizer->Add(m_SpinSlider, 1, wxEXPAND);
	else
		m_sizer->Add(m_floatSpinSlider, 1, wxEXPAND);
	if (m_pParam->IsPercentAvail())
		m_sizer->Add(m_percentSpinSlider, 1, wxEXPAND);
	else
		m_chkPercent->Enable(false);
	UpdatePercentVisibility();
	SetAutoLayout(true);
	SetSizer(m_sizer);
	m_sizer->Fit(this);
	Layout();
}

void ParamSpinSlider::OnSpinSlider(wxCommandEvent& event)
{
	if (m_SpinSlider == NULL)
		return;
	long l = m_SpinSlider->GetValue();
	m_pParam->SetValue(&l);

}

void ParamSpinSlider::OnFloatSpinSlider(wxCommandEvent& event)
{
	double d = m_floatSpinSlider->GetValue();
	m_pParam->SetValue(&d);
}

void ParamSpinSlider::OnPercentSlider(wxCommandEvent& event)
{
	double d = m_percentSpinSlider->GetValue();
	if (m_chkPercent->IsChecked())
		m_pParam->SetPercValue(d);
}

void ParamSpinSlider::OnChkPercent(wxCommandEvent& event)
{
	UpdatePercentVisibility();
}

void ParamSpinSlider::UpdatePercentVisibility()
{
	if (!m_pParam->IsPercentAvail())
		return;
	if (m_chkPercent->IsChecked())
	{
		m_percentSpinSlider->SetValue(m_pParam->GetPercValue());
		m_percentSpinSlider->Show();
		if (m_pParam->GetType() == Parameter::LONG)
			m_SpinSlider->Hide();
		else
			m_floatSpinSlider->Hide();
	}
	else
	{
		m_percentSpinSlider->Hide();
		if (m_pParam->GetType() == Parameter::LONG)
		{
			long l = * (long *) m_pParam->GetValue();
			m_SpinSlider->SetValue(l);
			m_SpinSlider->Show();
		}
		else
		{
			double d = * (double *) m_pParam->GetValue();
			m_floatSpinSlider->SetValue(d);
			m_floatSpinSlider->Show();
		}
	}
	Layout();
}
int ParamSpinSlider::GetLabelWidth() const
{
	if (m_pParam->GetType() == Parameter::LONG)
		return m_SpinSlider->GetLabelWidth();
	else
		return m_floatSpinSlider->GetLabelWidth();
}

void ParamSpinSlider::SetLabelWidth(int newWidth)
{
	if (m_pParam->GetType() == Parameter::LONG)
		m_SpinSlider->SetLabelWidth(newWidth);
	else
		m_floatSpinSlider->SetLabelWidth(newWidth);
	if (m_pParam->IsPercentAvail())
		m_percentSpinSlider->SetLabelWidth(newWidth);
}

void ParamSpinSlider::Update(Observable *observable)
{
	long l; double d;
	if (m_pParam->IsDestroyed())
	{
		m_pParam = NULL;
		return;
	}
	if (m_pParam->GetType() == Parameter::LONG)
	{
		l = *(long *) m_pParam->GetValue();
		m_SpinSlider->SetValue(l);
		//TODO: min i max?
	}
	else
	{
		d = * (double *) m_pParam->GetValue();
		m_floatSpinSlider->SetValue(d);
	}
	if (m_pParam->IsPercentAvail()) 
	{
		m_percentSpinSlider->SetRange(m_pParam->GetPercMin(), m_pParam->GetPercMax());
		m_percentSpinSlider->SetValue(m_pParam->GetPercValue());
		
		
	}
}
