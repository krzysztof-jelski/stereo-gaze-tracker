// OptionPane.cpp: implementation of the OptionPane class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "OptionPane.h"
#include "ParamSpinSlider.h"
#include "GlobalConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(OptionPane, wxPanel)
	EVT_COMMAND_RANGE(OptionPane::wxID_SPINSLIDER1ST, OptionPane::wxID_SPINSLIDERLAST, wxEVT_SPINSLIDER, OptionPane::OnSpinSlider)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OptionPane::OptionPane(ParametersGroup* pGroup, wxWindow* parent,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name) :
	wxPanel(parent, id, pos, size, style, name)
{
	m_sizer = new wxBoxSizer(wxVERTICAL);
	SetParametersGroup(pGroup);
	DoLayout();
}

OptionPane::~OptionPane()
{
}

void OptionPane::SetParametersGroup(ParametersGroup *pGroup)
{
	m_pGroup = pGroup;
	if (m_pGroup != NULL)
		m_Name = m_pGroup->GetName();
}


void OptionPane::Populate()
{
	wxString name;
	Parameter *parameter;
//	long value, min = 0, max = 100;
	int i = 0;

	while (m_pGroup->HasNext())
	{
		m_pGroup->GetNext(parameter, name);
//		switch (parameter->GetType())
//		{
//		case Parameter::LONG:
/*			value = *(long *) parameter->GetValue();
			min = * (long *) parameter->GetMin();
			max = * (long *) parameter->GetMax();
			m_sizer->Add(new SpinSlider(this, wxID_SPINSLIDER1ST + i, value, min, max, name), 0, wxEXPAND);
*/			m_sizer->Add(new ParamSpinSlider(this, wxID_SPINSLIDER1ST + i, parameter), 0, wxEXPAND);
//			break;
//		case Parameter::DOUBLE:
//			break;

//		}

		i++;
	}

	m_count = i;
	Align();
}

void OptionPane::DoLayout()
{
	Populate();
	SetAutoLayout(true);
	SetSizerAndFit(m_sizer);
	UpdateLayout();
}

void OptionPane::UpdateLayout()
{
//	m_sizer->SetSizeHints(this);
//	m_sizer->Fit(this);
	Layout();
}

void OptionPane::OnSpinSlider(wxCommandEvent& event)
{
	long value = event.GetInt();
	(*m_pGroup)[event.GetString()]->SetValue(&value);
}

wxString OptionPane::GetName()
{
	return m_pGroup->GetName();
}

void OptionPane::Align()
{
	ParamSpinSlider *slider;
	int maxWidth = 0, curWidth;

	for (int i = 0; i < m_count; i++)
	{
		wxWindow *win = wxWindow::FindWindowById(wxID_SPINSLIDER1ST + i, this);
		if (win != NULL)
		{
			slider = (ParamSpinSlider *) win;
			curWidth = slider->GetLabelWidth();
			if (curWidth > maxWidth)
				maxWidth = curWidth;
		}
	}
	for (int j = 0; j < m_count; j++)
	{
		wxWindow *win = wxWindow::FindWindowById(wxID_SPINSLIDER1ST + j, this);
		if (win != NULL)
		{
			slider = (ParamSpinSlider *) win;
			slider->SetLabelWidth(maxWidth);
		}
	}
}
void OptionPane::Update()
{
	for (int i = 0; i < m_count; i++)
	{
		wxWindow *win = wxWindow::FindWindowById(wxID_SPINSLIDER1ST + i, this);
		if (win != NULL)
		{
			m_sizer->Detach(win);
			win->Destroy();
		}
	}
	SetParametersGroup(GlobalConfig::GetInstance()[m_Name]);
	Populate();
	UpdateLayout();

}