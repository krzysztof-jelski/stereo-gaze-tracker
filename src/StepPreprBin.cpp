/** @file StepPreprBin.cpp
 *  Implementation of the StepPreprBin class.
 */

#include "StepPreprBin.h"
#include "GlobalConfig.h"

StepPreprBin::StepPreprBin() :
	m_binThresh(* (long *) (*GlobalConfig::GetInstance()["Preprocessing"])["binThresh"]->GetValue())
{

}

IplImage* StepPreprBin::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);

	cvThreshold(src1, m_resultImg, (float) m_binThresh, 255.0, CV_THRESH_BINARY);

	return m_resultImg;
}

