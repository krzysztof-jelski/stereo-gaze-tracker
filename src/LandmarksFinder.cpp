/** @file LandmarksFinder.cpp
 *  Implementation of the LandmarksFinder class.
 */

#include "wxprec.h"
#include "LandmarksFinder.h"
#include "HoughEllipseIrisFinder.h"
#include "GlobalConfig.h"
#include "ImgLib.h"
#include "LandmarksFinderNull.h"
#include "LandmarksFinderGPF.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LandmarksFinder::LandmarksFinder()
{
}

LandmarksFinder::~LandmarksFinder()
{
}

LandmarksFinder *LandmarksFinder::Create(const wxString &name)
{
	if (name.Cmp("HoughEllipseIrisFinder") == 0)
		return new HoughEllipseIrisFinder();
	if (name.Cmp("LandmarksFinderNull") == 0)
		return new LandmarksFinderNull();
	if (name.Cmp("LandmarksFinderGPF") == 0)
		return new LandmarksFinderGPF();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}