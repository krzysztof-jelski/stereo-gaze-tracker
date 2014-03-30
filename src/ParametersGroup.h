/** @file ParametersGroup.h
 *  Interface for the ParametersGroup class.
 */

#ifndef PARAMETERSGROUP_H
#define PARAMETERSGROUP_H

#include "wxprec.h"
#include "Parameter.h"

typedef Parameter* ParameterPtr;

int CompareParameters(Parameter *item1, Parameter *item2);

//WX_DEFINE_ARRAY_PTR(ParameterPtr, ParamArray);
WX_DEFINE_SORTED_ARRAY(ParameterPtr, ParamArray);

class ParametersGroup  
{
public:
	ParametersGroup(wxString name);
	virtual ~ParametersGroup();

	ParameterPtr& operator[](wxString key);

	void AddParam(ParameterPtr param);
	int HasNext();

	int GetNext(Parameter *&param);
	int GetNext(Parameter *&param, wxString& key);
	

	/**
	 * The HasChanged function.
	 * Indicates if the parameters have changed.
	 *
	 * @return bool true if there was a change in parameters' values
	 */
	bool HasChanged() { return m_bHasChanged; }

	wxString GetName() const { return m_Name; }

protected:
	ParamArray m_Params;
	wxSortedArrayString m_ParamsNames;
	int m_Index;
	bool m_bIsIterating;
	bool m_bHasChanged;
	wxString m_Name;
};

#endif // #ifndef PARAMETERSGROUP_H
