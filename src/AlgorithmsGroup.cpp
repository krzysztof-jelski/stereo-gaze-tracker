#include "AlgorithmsGroup.h"

AlgorithmsGroup::AlgorithmsGroup(wxString name) :
	m_Name(name)
{
}

AlgorithmsGroup::~AlgorithmsGroup(void)
{
}

const wxString& AlgorithmsGroup::GetName() const
{
	return m_Name;
}
wxArrayString& AlgorithmsGroup::GetAvailabale()
{
	return m_AvailableAlgos;
}
const wxString& AlgorithmsGroup::GetSelected() const
{
	return m_SelectedAlgo;
}
void AlgorithmsGroup::SetSelected(const wxString& name)
{
	m_SelectedAlgo = name;
}
void AlgorithmsGroup::AddAvailable(const wxString& algoName)
{
	m_AvailableAlgos.Add(algoName);
}