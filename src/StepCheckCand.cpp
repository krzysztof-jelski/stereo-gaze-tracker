/** @file StepCheckCand.cpp
 *  Implementation of the StepCheckCand class.
 */

#include "StepCheckCand.h"
#include "StepCheckCandKawato.h"
#include "StepCheckCandKawatoNoSymmetry.h"

StepCheckCand::StepCheckCand() : 
	m_resultImg(NULL)
{

}

StepCheckCand::~StepCheckCand()
{
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
}

StepCheckCand* StepCheckCand::Create(wxString name)
{
	if (name.Cmp("StepCheckCandKawato") == 0)
		return new StepCheckCandKawato();
	if (name.Cmp("StepCheckCandKawatoNoSymmetry") == 0)
		return new StepCheckCandKawatoNoSymmetry();
	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}

void StepCheckCand::PrepareImg(IplImage* src)
{
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
	m_resultImg = cvCreateImage(cvSize(m_sizeData.GetWidth(), m_sizeData.GetHeight()),
		IPL_DEPTH_8U,
		3);
}
