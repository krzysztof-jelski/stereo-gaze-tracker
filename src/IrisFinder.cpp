/** @file IrisFinder.cpp
 *  Implementation of the IrisFinder class.
 */

#include "IrisFinder.h"
#include "IrisFinderFit.h"

IrisFinder* IrisFinder::Create(wxString name)
{
	if (name.Cmp("IrisFinderFit") == 0)
		return new IrisFinderFit();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}
