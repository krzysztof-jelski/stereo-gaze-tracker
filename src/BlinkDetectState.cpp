// BlinkDetectState.cpp: implementation of the BlinkDetectState class.
//
//////////////////////////////////////////////////////////////////////

#include "BlinkDetectState.h"
#include "BTETrackState.h"
#include "cv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BlinkDetectState* BlinkDetectState::pInstance = NULL;

BlinkDetectState::BlinkDetectState()
{
}
void BlinkDetectState::Destroy()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
BlinkDetectState* BlinkDetectState::GetInstance()
{
	if (pInstance == NULL)
		Create();
	return pInstance;
}
void BlinkDetectState::Create()
{
	pInstance = new BlinkDetectState();
}

void BlinkDetectState::Track(GazeTracker& tracker)
{
	IplImage *image1 = tracker.GetImage1();
	IplImage *image2 = tracker.GetImage2();

	bool bBlink1 = m_blinkDetector1.Detect(image1);
	bool bBlink2 = m_blinkDetector2.Detect(image2);
	if (bBlink1 && bBlink2)
	{
		tracker.SetLEye1(m_blinkDetector1.GetLeftEyeCenter());
		tracker.SetREye1(m_blinkDetector1.GetRightEyeCenter());
		tracker.SetLEye2(m_blinkDetector2.GetLeftEyeCenter());
		tracker.SetREye2(m_blinkDetector2.GetRightEyeCenter());
		cvCircle(image1, m_blinkDetector1.GetLeftEyeCenter(), 5, CV_RGB(0, 0, 255), 5);
		cvCircle(image1, m_blinkDetector1.GetRightEyeCenter(), 5, CV_RGB(0, 0, 255), 5);
		cvCircle(image2, m_blinkDetector2.GetLeftEyeCenter(), 5, CV_RGB(0, 0, 255), 5);
		cvCircle(image2, m_blinkDetector2.GetRightEyeCenter(), 5, CV_RGB(0, 0, 255), 5);
		tracker.ChangeState(BTETrackState::GetInstance());
	}
}
