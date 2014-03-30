/** @file StepSegmentate.cpp
 *  Implementation of the StepSegmentate class.
 */

#include "StepSegmentate.h"
#include "StepSegmFFill.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfComponents);

StepSegmentate::StepSegmentate() //:
//	m_resultImg(NULL)
{

}
StepSegmentate::~StepSegmentate()
{
//	if (m_resultImg != NULL)
//		cvReleaseImage(&m_resultImg);
}
StepSegmentate* StepSegmentate::Create(wxString name)
{
	if (name.Cmp("StepSegmFFill") == 0)
		return new StepSegmFFill();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}

