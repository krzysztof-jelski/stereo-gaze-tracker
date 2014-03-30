// AlgosPanel.cpp: implementation of the AlgosPanel class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "AlgosPanel.h"
#include "GlobalConfig.h"
#include "GazeTracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(AlgosPanel, wxPanel)
	EVT_BUTTON (wxID_APPLYBUTTON, AlgosPanel::OnApplyButton)
	EVT_COMBOBOX(wxID_ANY, AlgosPanel::OnComboBox)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AlgosPanel::AlgosPanel(TrackRunner *pTrackRunner,
	wxWindow* parent,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name) :
	wxPanel(parent, id, pos, size, style, name),
	m_pTrackRunner(pTrackRunner)
{
	m_sizer = new wxBoxSizer(wxVERTICAL);
	DoLayout();
}

AlgosPanel::~AlgosPanel()
{
}


void AlgosPanel::Populate()
{
	wxArrayString algosGroupsNames = GlobalConfig::GetInstance().GetAlgosGroupsNames();
	wxComboBox *combo;
	wxStaticText *label;
	unsigned int i;
	for (i = 0; i < algosGroupsNames.Count(); i++)
	{
		AlgorithmsGroup *pGroup = GlobalConfig::GetInstance().GetAlgoGroup(algosGroupsNames[i]);
		label = new wxStaticText(this, -1, pGroup->GetName()+":");
		combo = new wxComboBox(this,
			-1,
			pGroup->GetSelected(),
			wxDefaultPosition,
			wxDefaultSize,
			pGroup->GetAvailabale(),
			wxCB_READONLY | wxCB_SORT,
			wxDefaultValidator,
			pGroup->GetName());
		m_sizer->Add(label, 0, wxEXPAND | wxFIXED_MINSIZE | wxTOP | wxBOTTOM, 2);
		m_sizer->Add(combo, 0, wxEXPAND | wxFIXED_MINSIZE);
	}
	if (i > 0)
	{
		m_sizer->Add(
			new wxButton(this, wxID_APPLYBUTTON, "Apply"),
			0,
			wxFIXED_MINSIZE);
		m_Count = i + 1;
	}
	else
		m_Count = 0;

}

void AlgosPanel::DoLayout()
{
	Populate();
	SetAutoLayout(true);
	SetSizer(m_sizer);
	m_sizer->Fit(this);
	Layout();
}



void AlgosPanel::Update()
{
	// remove everything from sizer
	for (int i = m_Count - 1; i >=0; i--)
	{
		wxSizerItem *item = m_sizer->GetItem(i);
		wxWindow *win = item->GetWindow();
		m_sizer->Detach(win);
		win->Destroy();
	}
	// populate again
	DoLayout();
}

void AlgosPanel::OnApplyButton(wxCommandEvent &event)
{
	NotifyObservers();
}

void AlgosPanel::OnComboBox(wxCommandEvent &event)
{
	wxComboBox *comboBox = (wxComboBox *)event.GetEventObject();
	AlgorithmsGroup *pGroup = GlobalConfig::GetInstance().GetAlgoGroup(comboBox->GetName());
	pGroup->SetSelected(comboBox->GetValue());
}