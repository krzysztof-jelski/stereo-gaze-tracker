/** @file IrisFinderFit.cpp
 *  Implementation of the IrisFinderFit class.
 */

#include "IrisFinderFit.h"
#include "GlobalConfig.h"
#include "ImgLib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IrisFinderFit::IrisFinderFit() :
	m_eyeImg(NULL)
{
	m_storage = cvCreateMemStorage(0);
	m_contours = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), m_storage);
}

IrisFinderFit::~IrisFinderFit()
{
	cvReleaseMemStorage(&m_storage);
}

void IrisFinderFit::PrepareImage(CvRect rect)
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
	m_eyeImg = cvCreateImage(cvSize(rect.width, rect.height), IPL_DEPTH_8U, 1);
}
bool IrisFinderFit::Find(IplImage* image, CvRect eyeROI)
{
	cvClearMemStorage(m_storage);

	if (m_sizeData.SizeChanged(eyeROI))
		PrepareImage(eyeROI);
	ImgLib::CopyRect(image, m_eyeImg, eyeROI, cvPoint(0, 0));
	cvSmooth(m_eyeImg, m_eyeImg);
	cvCanny(m_eyeImg, m_eyeImg, 150, 200);


	ImgLib::CopyRect(m_eyeImg,
		image,
		cvRect(0, 0, m_eyeImg->width, m_eyeImg->height),
		cvPoint(eyeROI.x, eyeROI.y));
	return false;
}

/*
	cvFindContours(m_eyeImg, m_storage, &m_contours, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
    // This loop draw all contours and approximate it by ellipses.
	for(;m_contours;m_contours = m_contours->h_next)
	{
		int i; // Indicator of loop.
		int count = m_contours->total; // This is the number point in the m_contours
		CvPoint center;
		CvSize size;
        
		double area, perimeter, roundness;

		// Number point must be more than or equal to 6 (for cvFitEllipse_32f).        
		if( count < 6 ) // modify this as a manual threshold if thresh-bar doesn't work
			continue;

		// Allocate memory for contours point set.    
		CvPoint* PointArray = (CvPoint*)malloc( count*sizeof(CvPoint) );
		CvPoint2D32f* PointArray2D32f= (CvPoint2D32f*)malloc( count*sizeof(CvPoint2D32f) );

		// Allocate memory for ellipse data.
		CvBox2D32f* box = (CvBox2D32f*)malloc(sizeof(CvBox2D32f));

		// Get contour point set.
		cvCvtSeqToArray(m_contours, PointArray, CV_WHOLE_SEQ);

		// Convert CvPoint set to CvBox2D32f set.
		for(i=0; i<count; i++)
		{
			PointArray2D32f[i].x = (float)PointArray[i].x;
			PointArray2D32f[i].y = (float)PointArray[i].y;
		}

		// Fits ellipse to current m_contoursour.
		cvFitEllipse(PointArray2D32f, count, box);

		// Calculate area and perimeter.
		area = cvContourArea(m_contours, CV_WHOLE_SEQ);
		perimeter = cvArcLength(m_contours, CV_WHOLE_SEQ, 1);
		roundness = (4 * 3.14159 * area) / (perimeter * perimeter);

//		if (roundness > .875) // perfect circle = 1. goes down to 0.
//		{
//			if (area > 80) // used to filter out small, superflous ellipses
//				// Draw current contour.
//				cvDrawContours(m_eyeImg, m_contours, CV_RGB(0,255,0), CV_RGB(0,255,0), 0, 2, 8, cvPoint(0,0));
//		}

		// Convert ellipse data from float to integer representation.
		center.x = cvRound(box->center.x);
		center.y = cvRound(box->center.y);
		size.width = cvRound(box->size.width*.5);
		size.height = cvRound(box->size.height*.5);
		box->angle = -box->angle;


		// Draw ellipse.
		if (roundness > .5) // perfect circle = 1. goes down to 0.
		{
			if (size.width > 0)  // used to filter out small, superflous ellipses
				cvEllipse(m_eyeImg, center, size,
						 box->angle, 0, 360,
						 CV_RGB(255,255,255), 1, 8, 0);
		}

			// Free memory.          
			free(PointArray);
			free(PointArray2D32f);
			free(box);
	}

	*/