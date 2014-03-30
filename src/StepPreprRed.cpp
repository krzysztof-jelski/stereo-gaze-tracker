/** @file StepPreprRed.cpp
 *  Implementation of the StepPreprRed class.
 */

#include "StepPreprRed.h"

IplImage* StepPreprRed::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);
	cvSplit(src1, NULL, m_resultImg, NULL, NULL);
	return m_resultImg;
}

