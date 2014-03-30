/** @file StepPreprAdaptBin.cpp
 *  Implementation of the StepPreprAdaptBin class.
 */

#include "StepPreprAdaptBin.h"
#include "GlobalConfig.h"

StepPreprAdaptBin::StepPreprAdaptBin() :
	m_binThresh(* (long *)(*GlobalConfig::GetInstance()["Preprocessing"])["binThresh"]->GetValue()),
	m_adaptThreshSide(* (long *) (*GlobalConfig::GetInstance()["Preprocessing"])["adaptThreshSide"]->GetValue())
{

}

IplImage* StepPreprAdaptBin::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);

	int side = m_adaptThreshSide;
	CvRect ROI;
	ROI.width = ROI.height = side;

	double global_mean = cvAvg(src2).val[0];
	double local_mean;
	float threshold;

	for (int x = 0; x < src2->width; x += side)
		for (int y = 0; y < src2->height; y += side)
	{
		ROI.x = x;
		ROI.y = y;
		cvSetImageROI(src1, ROI);
		cvSetImageROI(src2, ROI);
		cvSetImageROI(m_resultImg, ROI);
		local_mean = cvAvg(src2).val[0];
		threshold = (local_mean / global_mean) * (float) m_binThresh;
		cvThreshold(src1, m_resultImg, threshold, 255.0, CV_THRESH_BINARY);	
	}
	
	cvResetImageROI(src1);
	cvResetImageROI(src2);
	cvResetImageROI(m_resultImg);
	return m_resultImg;
}

