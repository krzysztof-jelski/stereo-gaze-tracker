/** @file IrisFinderHoughCircle.cpp
 *  Implementation of the IrisFinderHoughCircle class.
 */

#include "IrisFinderHoughCircle.h"
#include "ImgLib.h"
#include "math.h"
#include "Timer.h"
#include "GlobalConfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IrisFinderHoughCircle::IrisFinderHoughCircle() :
	m_eyeImg(NULL)
{
}

IrisFinderHoughCircle::~IrisFinderHoughCircle()
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
}

void IrisFinderHoughCircle::PrepareImage(CvRect rect)
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
	m_eyeImg = cvCreateImage(cvSize(rect.width, rect.height), IPL_DEPTH_8U, 1);
}

bool IrisFinderHoughCircle::Find(IplImage* image, CvRect eyeROI)
{
	if (m_sizeData.SizeChanged(eyeROI))
		PrepareImage(eyeROI);

	ImgLib::IntelligentCopy(image, m_eyeImg);
//	CvMat* circleStorage = cvCreateMat(1, 10, CV_32FC3);
	CvMemStorage* storage = cvCreateMemStorage(0);
	cvSmooth(m_eyeImg, m_eyeImg, CV_GAUSSIAN, 3, 3 );
	CvSeq* circles = cvHoughCircles(m_eyeImg,
		storage,
		CV_HOUGH_GRADIENT,
		1,
		15,
		100,
		1);
	int i;
    for( i = 0; i < circles->total; i++ )
    {
         float* p = (float*)cvGetSeqElem( circles, i );
         cvCircle( m_eyeImg, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
    }
//	cvReleaseMat(&circleStorage);
	ImgLib::IntelligentCopy(m_eyeImg, image);
	cvReleaseMemStorage(&storage);
	return false;
}

