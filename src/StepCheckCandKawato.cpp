/** @file StepCheckCandKawato.cpp
 *  Implementation of the StepCheckCandKawato class.
 */

#include "StepCheckCandKawato.h"
#include "ImgLib.h"
#include "GlobalConfig.h"


StepCheckCandKawato::StepCheckCandKawato() : 
	m_rotatedImg(NULL),
	m_minEyeChange(* (long *) ((*GlobalConfig::GetInstance()["Eye"])["minEyeChange"])->GetValue()),
	m_eyesWidth(* (long *) ((*GlobalConfig::GetInstance()["EyePair"])["eyesWidth"])->GetValue()),
	m_eyesHeight(* (long *) ((*GlobalConfig::GetInstance()["EyePair"])["eyesHeight"])->GetValue()),
	m_maxSymDiff(* (long *) ((*GlobalConfig::GetInstance()["EyePair"])["maxSymDiff"])->GetValue()),
	m_minDist(* (long *) ((*GlobalConfig::GetInstance()["EyePair"])["minDist"])->GetValue()),
	m_maxDist(* (long *) ((*GlobalConfig::GetInstance()["EyePair"])["maxDist"])->GetValue()),
	m_maxAngle(* (long *) ((*GlobalConfig::GetInstance()["EyePair"])["maxAngle"])->GetValue())
{
	
}
StepCheckCandKawato::~StepCheckCandKawato()
{
}

void StepCheckCandKawato::PrepareImg(IplImage *src)
{
	StepCheckCand::PrepareImg(src);
	if (m_rotatedImg != NULL)
		cvReleaseImage(&m_rotatedImg);
	m_rotatedImg = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
}

int StepCheckCandKawato::DoCheckPair(const Candidate &cand1, const Candidate &cand2, IplImage *grayImg)
{
	int x1 = cand1.x, y1 = cand1.y;
	int x2 = cand2.x, y2 = cand2.y;
	int mid_x = (x1 + x2) / 2;
	int mid_y = (y1 + y2) / 2;
	int xDist = abs(x1 - x2);

	if ( m_sizeData.SizeChanged(grayImg) )
		PrepareImg(grayImg);
	cvZero(m_resultImg);

	// check the distance between eye centres
	if ( (xDist < m_minDist) || (xDist > m_maxDist) )
	{
		wxLogDebug("[Rej:] odleg³oœæ (%d)", xDist);
		return -1;
	}

	// check angle between eye centres
	double deg = ImgLib::GetAngle(x1, y1, x2, y2);
	if (abs(deg)  > m_maxAngle)
	{
		wxLogDebug("[Rej:] k¹t (%f)", deg);
		return -1;
	}
	
	// perform symmetry test
	ImgLib::RotateImage(grayImg, m_rotatedImg, mid_x, mid_y, deg);
	CvRect rect = cvRect(mid_x - (m_eyesWidth / 2),
		mid_y - (m_eyesHeight / 2),
		m_eyesWidth,
		m_eyesHeight);
	ImgLib::CopyRect(m_rotatedImg, m_resultImg, rect, cvPoint(0, 0));
	if (ImgLib::SymmetryTest(m_rotatedImg, rect, m_maxSymDiff) < 0)
	{
		wxLogDebug("[Rej:] Symmetry");
		return -1;
	}

	// whew!... Accepted
	wxLogDebug("[Accepted]");
	return 1;
}

int StepCheckCandKawato::DoCheckSingle(const Candidate &cand)
{
	// check if amount of change in eye ROI is enough
	if  (cand.changeSum < m_minEyeChange)
	{
		wxLogDebug("[Rej:] wielkoœci zmian (%d)", cand.changeSum);
		return -1;
	}
	return 1;
}
