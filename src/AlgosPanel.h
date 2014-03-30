/** @file AlgosPanel.h
 *  Interface for the AlgosPanel class.
 */


#ifndef AlgosPanel_H
#define AlgosPanel_H

#include "wxprec.h"
#include "TrackRunner.h"
#include "Observable.h"

class AlgosPanel : public wxPanel, public Observable
{
public:
	enum
	{
		wxID_APPLYBUTTON = 7450
	};
	AlgosPanel(TrackRunner *pTrackRunner,
		wxWindow* parent,
		wxWindowID id = -1,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL,
		const wxString& name = "algos_panel");
	virtual ~AlgosPanel();

	void Update();
	void Populate();
protected:
	void DoLayout();
	void OnApplyButton(wxCommandEvent &event);
	void OnComboBox(wxCommandEvent &event);

protected:
	wxBoxSizer* m_sizer;
	int m_Count;
	TrackRunner* m_pTrackRunner;

	DECLARE_EVENT_TABLE()
};

#endif // #ifndef AlgosPanel_H
