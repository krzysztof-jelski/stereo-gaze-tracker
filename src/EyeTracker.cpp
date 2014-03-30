/** @file EyeTracker.cpp
 *  Implementation of the EyeTracker class.
 */
#include "wxprec.h"
#include "EyeTracker.h"
#include "GlobalConfig.h"
#include "ImgLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EyeTracker::EyeTracker() :
	m_templImg(NULL),
	m_resultImg(NULL),
	m_tmplSearchH(*(long *)((*GlobalConfig::GetInstance()["Tracking"])["tmplSearchH"])->GetValue()),
	m_tmplSearchW(*(long *)((*GlobalConfig::GetInstance()["Tracking"])["tmplSearchW"])->GetValue()),
	m_tmplH(*(long *)((*GlobalConfig::GetInstance()["Tracking"])["tmplH"])->GetValue()),
	m_tmplW(*(long *)((*GlobalConfig::GetInstance()["Tracking"])["tmplW"])->GetValue()),
	m_eyeSearchW(*(long *)((*GlobalConfig::GetInstance()["Tracking"])["eyeSearchW"])->GetValue()),
	m_eyeSearchH(*(long *)((*GlobalConfig::GetInstance()["Tracking"])["eyeSearchH"])->GetValue())
{
	m_pStepCheck = StepCheckCand::Create("StepCheckCandKawatoNoSymmetry");
}

EyeTracker::~EyeTracker()
{
	if (m_templImg != NULL)
		cvReleaseImage(&m_templImg);
	if (m_resultImg != NULL)
		cvReleaseImage(&m_resultImg);
}

void EyeTracker::PrepareImg(IplImage *img)
{

}
void EyeTracker::StartTracking(const CvPoint &lEye, const CvPoint &rEye, IplImage *img)
{
	m_X.x = (lEye.x + rEye.x) / 2;
	m_X.y = (lEye.y + rEye.y) / 2;
	m_Xt_1 = m_X;
	m_Xt_2 = m_X;
	m_el.x = lEye.x - m_X.x;
	m_el.y = lEye.y - m_X.y;
	m_er.x = rEye.x - m_X.x;
	m_er.y = rEye.y - m_X.y;

	PrepareTemplate(img, m_X);
}

bool EyeTracker::Track(IplImage* image)
{
	CvPoint lEye, rEye;
	Candidate cand1, cand2;
	
	m_X = Predict();
	m_X = MatchTemplate(image, m_X, m_tmplSearchW, m_tmplSearchH);
	lEye = FindEye(image, cvPoint(m_X.x + m_el.x, m_X.y + m_el.y), m_eyeSearchW, m_eyeSearchH);
	rEye = FindEye(image, cvPoint(m_X.x + m_er.x, m_X.y + m_er.y), m_eyeSearchW, m_eyeSearchH);
	cand1.x = lEye.x; cand1.y = lEye.y;
	cand2.x = rEye.x; cand2.y = rEye.y;
	if ( m_pStepCheck->DoCheckPair(cand1, cand2, image) <= 0)
		return false;
	UpdateData(lEye, rEye);
	PrepareTemplate(image, m_X);

	return true;
}

CvPoint EyeTracker::GetLeftEyeCenter()
{
	CvPoint ret;

	ret.x = m_X.x + m_el.x;
	ret.y = m_X.y + m_el.y;
	return ret;
}
CvPoint EyeTracker::GetRightEyeCenter()
{
	CvPoint ret;

	ret.x = m_X.x + m_er.x;
	ret.y = m_X.y + m_er.y;
	return ret;
}

void EyeTracker::SetEyePositions(CvPoint2D32f lEye, CvPoint2D32f rEye)
{
	CvPoint l, r;
	l.x = lEye.x; l.y = lEye.y;
	r.x = rEye.x; r.y = rEye.y;
	UpdateData(l, r);
}
CvPoint EyeTracker::Predict()
{
	CvPoint ret;
	ret.x = 2 * m_Xt_1.x - m_Xt_2.x;
	ret.y = 2 * m_Xt_1.y - m_Xt_2.y;
	return ret;
}

void EyeTracker::UpdateData(const CvPoint &lEye, const CvPoint &rEye)
{
	m_Xt_2 = m_Xt_1;
	m_Xt_1 = m_X;
	m_X.x = (lEye.x + rEye.x) / 2;
	m_X.y = (lEye.y + rEye.y) / 2;
	m_el.x = lEye.x - m_X.x;
	m_el.y = lEye.y - m_X.y;
	m_er.x = rEye.x - m_X.x;
	m_er.y = rEye.y - m_X.y;

}

CvPoint EyeTracker::MatchTemplate(IplImage *image, const CvPoint &center, int win_width, int win_height)
{
	CvRect ROI;
	CvPoint result = cvPoint(0, 0);

	// prepare ROI
	ROI.x = center.x - (win_width / 2);
	ROI.y = center.y - (win_height / 2);
	ROI.width = win_width;
	ROI.height = win_height;
	ROI.x = ROI.x < 0 ? 0 : ROI.x;
	ROI.y = ROI.y < 0 ? 0 : ROI.y;
//	ImgLib::ClipRect(ROI, image->width, image->height);
//	cvRectangle(image, cvPoint(ROI.x, ROI.y), cvPoint(ROI.x + ROI.width, ROI.y + ROI.height),
//		CV_RGB(255, 255, 255));
	cvSetImageROI(image, ROI);

	// check sizes
	if ( (image->roi->width - m_templImg->width <= 0)
		|| (image->roi->height - m_templImg->height <= 0) )
		return result;
	if ( (m_templImg->width <= 0) || (m_templImg->height <= 0) )
		return result;

	if (m_resultImg != NULL)
	{
		cvReleaseImage(&m_resultImg);
		m_resultImg = NULL;
	}
	m_resultImg = cvCreateImage(cvSize(image->roi->width - m_templImg->width + 1, image->roi->height - m_templImg->height + 1),
		IPL_DEPTH_32F,
		1);

	cvMatchTemplate(image, m_templImg, m_resultImg, CV_TM_SQDIFF_NORMED);
	cvMinMaxLoc(m_resultImg, NULL, NULL, &result, NULL);
	result.x += ROI.x + (m_templImg->width / 2);
	result.y += ROI.y + (m_templImg->height / 2);
	cvResetImageROI(image);
	cvReleaseImage(&m_resultImg);
	return result;

}

CvPoint EyeTracker::FindEye(IplImage *image, const CvPoint &center, int win_width, int win_height)
{
	int n = 5;
	double avg;
	double best = 255.0 * n * n;
	CvPoint result = cvPoint(0, 0);

	int x_lo = center.x - (win_width / 2);
	int x_hi = x_lo + win_width;

	int y_lo = center.y - (win_height / 2);
	int y_hi = y_lo + win_height;

	x_lo = __max(0, x_lo);
	y_lo = __max(0, y_lo);

	for (int x = x_lo; (x < x_hi) && (x < image->width); x++)
		for (int y = y_lo; (y < y_hi) && (y < image->height); y++)
		{
			cvSetImageROI(image, cvRect(x, y, n, n) );
			avg = cvAvg(image).val[0];
			if (avg < best)
			{
				best = avg;
				result.x = x;
				result.y = y;
			}
		}
	cvResetImageROI(image);
	return result;
}

void EyeTracker::PrepareTemplate(IplImage *img, CvPoint center)
{
	bool bCreate = false;
	CvRect ROI;

	if (m_templImg != NULL)
	{
		if ( (m_templImg->width != m_tmplW)
			|| (m_templImg->height != m_tmplH) )
		{
			cvReleaseImage(&m_templImg);
			bCreate = true;
		}
	}
	else
		bCreate = true;

	if (bCreate)
		m_templImg = cvCreateImage(cvSize(m_tmplW, m_tmplH),
			IPL_DEPTH_8U,
			1);

	ROI.x = center.x - (m_tmplW / 2);
	ROI.y = center.y - (m_tmplH / 2);
	ROI.width = m_tmplW;
	ROI.height = m_tmplH;

	ImgLib::CopyRect(img, m_templImg, ROI, cvPoint(0,0));
	ImgLib::CopyRect(m_templImg, img, cvRect(0, 0, m_templImg->width, m_templImg->height), cvPoint(0,0));

//	cvSetImageROI(img, ROI);

//	cvResetImageROI(img);

}