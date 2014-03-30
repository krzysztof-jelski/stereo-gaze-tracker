/** @file EyeCornersFinderZhu.cpp
 *  Implementation of the EyeCornersFinderZhu class.
 */

#include "EyeCornersFinderZhu.h"
#include "ImgLib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EyeCornersFinderZhu::EyeCornersFinderZhu() :
	m_eyeImg(NULL)
{
}

EyeCornersFinderZhu::~EyeCornersFinderZhu()
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
}

void EyeCornersFinderZhu::PrepareImage(const CvRect& rect)
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
	m_eyeImg = cvCreateImage(cvSize(rect.width, rect.height), IPL_DEPTH_8U, 1);

}
bool EyeCornersFinderZhu::Find(IplImage* image, CvRect eyeROI, CvPoint2D32f irisCentre)
{
	if (m_sizeData.SizeChanged(eyeROI))
		PrepareImage(eyeROI);
	ImgLib::CopyRect(image, m_eyeImg, eyeROI, cvPoint(0, 0));

	double kernel1[] = {	-1,	-1,	-1,	1,	1,	1,
							-1,	-1,	-1,	-1,	1,	1, 
							-1,	-1,	-1,	-1,	-1,	1,
							1,	1,	1,	1,	1,	1};
	double kernel2[] = {	1,	1,	1,	-1,	-1,	-1,
							1,	1,	-1,	-1,	-1,	-1, 
							1,	-1,	-1,	-1,	-1,	-1,
							1,	1,	1,	1,	1,	1};
	CvMat kernel_mat1, kernel_mat2;
	cvInitMatHeader(&kernel_mat1, 4, 6, CV_32FC1, kernel1);
	cvInitMatHeader(&kernel_mat2, 4, 6, CV_32FC1, kernel2);
	cvSmooth(m_eyeImg, m_eyeImg);
	cvCanny(m_eyeImg, m_eyeImg, 150, 200);
	cvFilter2D(m_eyeImg, m_eyeImg, &kernel_mat2);

	double max_val;
	CvPoint max_loc;
	cvMinMaxLoc(m_eyeImg, 0, &max_val,
                  NULL, &max_loc);
//	if (max_val == 255.0)
		ImgLib::DrawCross(m_eyeImg, max_loc, 6, 6, CV_RGB(255, 255, 255), 1);
	ImgLib::CopyRect(m_eyeImg,
		image,
		cvRect(0, 0, m_eyeImg->width, m_eyeImg->height),
		cvPoint(eyeROI.x, eyeROI.y));
	return false;
}
