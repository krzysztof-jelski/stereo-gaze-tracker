// ParametersGroup.cpp: implementation of the ParametersGroup class.
//
//////////////////////////////////////////////////////////////////////
#include "wxprec.h"
#include "ParametersGroup.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

int CompareParameters(Parameter *item1, Parameter *item2)
{
	return item1->GetName().Cmp(item2->GetName());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ParametersGroup::ParametersGroup(wxString name) :
	m_bIsIterating(false),
	m_Name(name),
	m_Params(CompareParameters)
{

}

ParametersGroup::~ParametersGroup()
{
	for (int i = 0; i < (int) m_Params.GetCount(); i++)
		delete m_Params[i];
}

void ParametersGroup::AddParam(ParameterPtr param)
{
	m_Params.Add(param);
	m_ParamsNames.Add(param->GetName());
}


ParameterPtr& ParametersGroup::operator[](wxString key)
{
	int index = m_ParamsNames.Index(key);
	return m_Params[index];
}

int ParametersGroup::HasNext()
{
	if (m_bIsIterating)
	{
		if (m_Index == (int) m_Params.GetCount())
			m_bIsIterating = false;
	}
	else
	{
		m_Index = 0;
		m_bIsIterating = ( m_Index != (int) m_Params.GetCount() );
	}
	if (!m_bIsIterating)
		return 0;

	while ( !m_Params[m_Index]->IsActive() )
	{
		m_Index++;
		if ( m_Index == (int) m_Params.GetCount() )
		{
			m_bIsIterating = false;
			return 0;
		}
	}
	return 1;

}

int ParametersGroup::GetNext(Parameter *&param)
{
	wxASSERT_MSG(m_bIsIterating, "Call HasNext() first!");
	wxASSERT_MSG(m_Index != (int) m_Params.GetCount(), "End of hash reached.");

	Parameter *par = m_Params[m_Index];

	param = par;
	
	m_Index++;
	return 1;	
}
int ParametersGroup::GetNext(Parameter *&param, wxString& key)
{
	wxASSERT_MSG(m_bIsIterating, "Call HasNext() first!");
	wxASSERT_MSG(m_Index != (int) m_Params.GetCount(), "End of hash reached.");
	
	key = m_ParamsNames[m_Index];
	
	return GetNext(param);
}

