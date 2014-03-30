/** @file EyeCornersFinder.cpp
 *  Implementation of the EyeCornersFinder class.
 */

#include "EyeCornersFinder.h"
#include "EyeCornersFinderZhu.h"

EyeCornersFinder* EyeCornersFinder::Create(wxString name)
{
	if (name.Cmp("EyeCornersFinderZhu") == 0)
		return new EyeCornersFinderZhu();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}
