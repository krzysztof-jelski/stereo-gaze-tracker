#pragma once

#include "wxprec.h"

class AlgorithmsGroup
{
public:
	AlgorithmsGroup(wxString name);
	~AlgorithmsGroup(void);

	const wxString& GetName() const;
	wxArrayString& GetAvailabale();
	void AddAvailable(const wxString& algoName);
	const wxString& GetSelected() const;
	void SetSelected(const wxString& name);

protected:
	wxArrayString m_AvailableAlgos;
	wxString m_SelectedAlgo;
	wxString m_Name;
};
