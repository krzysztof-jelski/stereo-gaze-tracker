/** @file StepPreprCvAdaptBin.cpp
 *  Implementation of the StepPreprCvAdaptBin class.
 */

#include "StepPreprCvAdaptBin.h"
#include "GlobalConfig.h"

StepPreprCvAdaptBin::StepPreprCvAdaptBin() :
	m_binThresh(* (long *) (*GlobalConfig::GetInstance()["Preprocessing"])["binThresh"]->GetValue())
{

}

IplImage* StepPreprCvAdaptBin::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);

	cvAdaptiveThreshold(src1,
		m_resultImg,
		255.0,
		CV_ADAPTIVE_THRESH_MEAN_C,
		CV_THRESH_BINARY,
		3,
		- m_binThresh);


	return m_resultImg;
}

