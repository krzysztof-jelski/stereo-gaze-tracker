/** @file StepPreprHue.cpp
 *  Implementation of the StepPreprHue class.
 */

#include "StepPreprHue.h"

StepPreprHue::StepPreprHue() :
	m_hsvImg(NULL)
{
}

StepPreprHue::~StepPreprHue()
{
	if (m_hsvImg != NULL)
		cvReleaseImage(&m_hsvImg);
}
IplImage* StepPreprHue::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);
	cvCvtColor(src1, m_hsvImg, CV_BGR2HSV);
	cvSplit(m_hsvImg, m_resultImg, NULL, NULL, NULL);
	return m_resultImg;
}

void StepPreprHue::PrepareImg(IplImage *src)
{
	StepPrepr::PrepareImg(src);
	if (m_hsvImg != NULL)
		cvReleaseImage(&m_hsvImg);
	m_hsvImg = cvCreateImage(cvSize(m_sizeData.GetWidth(), m_sizeData.GetHeight()),
		IPL_DEPTH_8U,
		3);

}