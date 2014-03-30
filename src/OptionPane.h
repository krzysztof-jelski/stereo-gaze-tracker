/** @file OptionPane.h
 *  Interface for the OptionPane class.
 */


#ifndef OPTIONPANE_H
#define OPTIONPANE_H

#include "wxprec.h"
#include "ParametersGroup.h"

extern const wxEventType wxEVT_SPINSLIDER;

class OptionPane : public wxPanel  
{
public:
	enum
	{
		wxID_SPINSLIDER1ST = 6900,
		wxID_SPINSLIDERLAST = 7000
	};
	OptionPane(ParametersGroup* group, wxWindow* parent,
		wxWindowID id = -1,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL,
		const wxString& name = "option_pane");
	virtual ~OptionPane();
	wxString GetName();
	/**
	 * Update all sliders.
	 */
	void Update();
	void Populate();
	void SetParametersGroup(ParametersGroup *pGroup);
protected:
	void DoLayout();
	void UpdateLayout();
	void Align();
	void OnSpinSlider(wxCommandEvent& event);
	
protected:
	/// number of spinsliders inside
	int m_count;
	/// Parameters Group object - these params will be displayed
	ParametersGroup* m_pGroup;
	wxString m_Name;
	wxBoxSizer* m_sizer;
	DECLARE_EVENT_TABLE()

};

#endif // #ifndef OPTIONPANE_H
