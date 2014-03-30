/** @file StepDiffLDD.cpp
 *  Implementation of the StepDiffLDD class.
 */
#include "StepDiffLDD.h"
#include "GlobalConfig.h"

StepDiffLDD::StepDiffLDD() :
	m_diffImg(NULL),
	m_lastImg(NULL),
	m_LDDBoxSide(* (long *) (*GlobalConfig::GetInstance()["Preprocessing"])["LDDBoxSide"]->GetValue()),
	m_LDDThresh(* (double *) (*GlobalConfig::GetInstance()["Preprocessing"])["LDDThresh"]->GetValue())
{

}

StepDiffLDD::~StepDiffLDD()
{
	Clear();
}

IplImage* StepDiffLDD::DoDiff(IplImage* src)
{
	if (m_sizeData.SizeChanged(src))
		ReInit(src);
	
	
	// number of pixels in the neighbourhood
//	int neighPixels = m_adaptThreshSide * m_adaptThreshSide;
	int half_side = m_LDDBoxSide / 2;
	// brightness of pixel from current frame
	uchar curValue;
	// brightness of pixel from last frame
	uchar lastValue;
	uchar* curRow;
	uchar* lastRow;
	uchar* row;
	float ratio;

	float variance;
	float sum, sqrsum;
	float n;
	int k, j;
	//
	//(x+k,y+j)
	//			(x, y)
	//
	//
	for (int x = 0; x < src->width; x++)
	{
		for (int y = 0; y < src->height; y++)
		{
			row = (uchar*)(m_diffImg->imageData + y * m_diffImg->widthStep);
			// find mean
			sum = 0.0; sqrsum = 0.0;
			n = 0;
			for (k = -half_side; k <= half_side; k++)
				for (j = -half_side; j <= half_side; j++)
				{
					if ((x + k >= 0) && (x + k < src->width)
						&& (y + j >= 0) && (y + j < src->height))
					{
						curRow = (uchar*)(src->imageData + (y + j) * src->widthStep);
						lastRow = (uchar*)(m_lastImg->imageData + (y + j) * m_lastImg->widthStep);
						curValue = curRow[x + k];
						lastValue = lastRow[x + k];
						if (curValue == 0.0)
							curValue = 0.0001;
						ratio = (float) lastValue / (float) curValue;
						sum += ratio;
						sqrsum += ratio * ratio;
						n++;
					}
				}

			variance = sqrsum / n - (sum * sum) / (n * n);
			
			row[x] = variance < m_LDDThresh ? 0 : 255;
		}
	}
	cvCopy(src, m_lastImg);
	return m_diffImg;
}

void StepDiffLDD::ReInit(IplImage *src)
{
	Clear();

	m_diffImg = cvCreateImage(cvSize(src->width, src->height),
			IPL_DEPTH_8U,
			1);

	m_lastImg = cvCreateImage(cvSize(src->width, src->height),
		IPL_DEPTH_8U,
		1);
	cvZero(m_diffImg);
	cvCopy(src, m_lastImg);
}

void StepDiffLDD::Clear()
{
	if (m_diffImg != NULL)
		cvReleaseImage(&m_diffImg);
	if (m_lastImg)
		cvReleaseImage(&m_lastImg);
}