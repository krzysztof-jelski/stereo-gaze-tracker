/** @file StepPreprGray.cpp
 *  Implementation of the StepPreprGray class.
 */

#include "StepPreprGray.h"

IplImage* StepPreprGray::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);
	cvCvtColor(src1, m_resultImg, CV_BGR2GRAY);
	return m_resultImg;
}

