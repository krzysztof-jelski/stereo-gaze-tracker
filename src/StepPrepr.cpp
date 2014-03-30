/** @file StepPrepr.cpp
 *  Implementation of the StepPrepr class.
 */

#include "StepPrepr.h"
#include "StepPreprGray.h"
#include "StepPreprBin.h"
#include "StepPreprRed.h"
#include "StepPreprHue.h"
#include "StepPreprAdaptBin.h"
#include "StepPreprCvAdaptBin.h"
#include "StepPreprClean.h"

StepPrepr::StepPrepr() :
	m_resultImg(NULL)
{

}
StepPrepr::~StepPrepr()
{
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
}
StepPrepr* StepPrepr::Create(wxString name)
{
	if (name.Cmp("StepPreprGray") == 0)
		return new StepPreprGray();
	if (name.Cmp("StepPreprBin") == 0)
		return new StepPreprBin();
	if (name.Cmp("StepPreprRed") == 0)
		return new StepPreprRed();
	if (name.Cmp("StepPreprHue") == 0)
		return new StepPreprHue();
	if (name.Cmp("StepPreprAdaptBin") == 0)
		return new StepPreprAdaptBin();
	if (name.Cmp("StepPreprCvAdaptBin") == 0)
		return new StepPreprCvAdaptBin();
	if (name.Cmp("StepPreprClean") == 0)
		return new StepPreprClean();
	wxCHECK_MSG(0, NULL, "Wrong type!");
}

void StepPrepr::PrepareImg(IplImage* src)
{
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
	m_resultImg = cvCreateImage(cvSize(m_sizeData.GetWidth(), m_sizeData.GetHeight()),
		IPL_DEPTH_8U,
		1);
}