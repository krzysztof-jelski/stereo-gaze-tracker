/** @file StepDiff.cpp
 *  Implementation of the StepDiff class.
 */

#include "StepDiff.h"
#include "StepDiff1st.h"
#include "StepDiff2nd.h"
#include "StepDiffLDD.h"

StepDiff* StepDiff::Create(wxString name)
{
	if (name.Cmp("StepDiff1st") == 0)
		return new StepDiff1st();
	if (name.Cmp("StepDiffLDD") == 0)
		return new StepDiffLDD();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}
