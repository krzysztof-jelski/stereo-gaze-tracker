/** @file StepVerify.cpp
 *  Implementation of the StepVerify class.
 */

#include "StepVerify.h"
#include "StepVerKawato.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfCandidates);

StepVerify::StepVerify() :
	m_resultImg(NULL)
{

}
StepVerify::~StepVerify()
{
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
}
StepVerify* StepVerify::Create(wxString name)
{
	if (name.Cmp("StepVerKawato") == 0)
		return new StepVerKawato();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}

void StepVerify::PrepareImg(IplImage* src)
{
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
	m_resultImg = cvCreateImage(cvSize(m_sizeData.GetWidth(), m_sizeData.GetHeight()),
		IPL_DEPTH_8U,
		3);
}