// FrameDiff.cpp: implementation of the FrameDiff class.
//
//////////////////////////////////////////////////////////////////////

#include "FrameDiff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FrameDiff::FrameDiff() :
	m_nAccDepth(1),
	m_pLastImage(NULL),
	m_pDiffAcc(NULL),
	m_bInitDone(false)
{
}

FrameDiff::~FrameDiff()
{
	Clear();
}

void FrameDiff::SetAccDepth(int nFrames)
{
	m_nAccDepth = nFrames;
}

IplImage* FrameDiff::GetDiff(IplImage *pNewImage)
{
	if (!m_bInitDone)
	{
		Init(pNewImage);
		m_pLastImage = cvCloneImage(pNewImage);
		return m_pDiffAcc;
	}

	cvAbsDiff(m_pLastImage, pNewImage, m_pDiffAcc);
//	cvReleaseData(m_pLastImage);
	cvCopy(pNewImage, m_pLastImage);
	return m_pDiffAcc;
}

IplImage* FrameDiff::GetDiff2nd(IplImage *pNewImage)
{
	return NULL;
}

void FrameDiff::Init(IplImage *pImage)
{
	Clear();
	CvSize size = cvSize(pImage->width, pImage->height);
	m_pDiffAcc = cvCreateImage(size, IPL_DEPTH_8U, 1);
	cvZero(m_pDiffAcc);
	m_bInitDone = true;
}

void FrameDiff::Clear()
{
	if (m_pLastImage != NULL)
	{
		cvReleaseImage(&m_pLastImage);
		m_pLastImage = NULL;
	}
//	if (m_pDiffAcc != NULL)
//	{
//		cvReleaseImage(&m_pDiffAcc);
//		m_pDiffAcc = NULL;
//	}
}