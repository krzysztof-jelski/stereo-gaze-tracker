// GazeTracker.cpp: implementation of the GazeCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "wxprec.h"
#include "GazeTracker.h"
#include "BlinkDetectState.h"
#include "BTETrackState.h"
#include "TrackerState.h"
#include "CalibrationState.h"
#include "GlobalConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GazeTracker* GazeTracker::pInstance = NULL;

const wxEventType wxEVT_FPS = wxNewEventType();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GazeTracker::GazeTracker():
	m_pState(BlinkDetectState::GetInstance()),
	m_intr1(GlobalConfig::GetInstance().GetCam1Intrinsics()),
	m_intr2(GlobalConfig::GetInstance().GetCam2Intrinsics()),
	m_corrected1(NULL),
	m_corrected2(NULL),
	m_uLastCalcTime(wxGetLocalTimeMillis()),
	m_framesElapsed(0)
{
	BTETrackState::Create();
	CalibrationState::Create();
}

GazeTracker::~GazeTracker()
{
	BlinkDetectState::Destroy();
	BTETrackState::Destroy();
	CalibrationState::Destroy();
	if (m_corrected1 != NULL)
		cvReleaseImage(&m_corrected1);
	if (m_corrected2 != NULL)
		cvReleaseImage(&m_corrected2);
}

void GazeTracker::Destroy()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
GazeTracker* GazeTracker::GetInstance()
{
	if (pInstance == NULL)
		Create();
	return pInstance;
}
void GazeTracker::Create()
{
	pInstance = new GazeTracker();
}


TrackerState* GazeTracker::ChangeState(TrackerState* newState)
{
	TrackerState *oldState = m_pState;
	m_pState = newState;
	m_bStateChange = true;
	return oldState;
}


void GazeTracker::Track(IplImage *image1, IplImage *image2)
{
	wxLongLong elapsed, now;

	m_image1 = image1;
	m_image2 = image2;

	if (GlobalConfig::GetInstance().GetSizeData()->SizeChanged(image1))
	{
		if (m_corrected1 != NULL)
		{
			cvReleaseImage(&m_corrected1);
			m_corrected1 = NULL;
		}
		if (m_corrected2 != NULL)
		{
			cvReleaseImage(&m_corrected2);
			m_corrected2 = NULL;
		}
	}
	if (m_corrected1 == NULL)
		m_corrected1 = cvCreateImage(cvSize(image1->width, image2->height), IPL_DEPTH_8U, 3);
	if (m_corrected2 == NULL)
		m_corrected2 = cvCreateImage(cvSize(image1->width, image2->height), IPL_DEPTH_8U, 3);		
	
	
	float A1[] = {	m_intr1.focal_length[0], 0, m_intr1.principal_point.x,
					0,	m_intr1.focal_length[1], m_intr1.principal_point.y,
					0, 0, 1 };

	float A2[] = {	m_intr2.focal_length[0], 0, m_intr2.principal_point.x,
					0,	m_intr2.focal_length[1], m_intr2.principal_point.y,
					0, 0, 1 };

	CvMat A1Mat, A2Mat, d1Mat, d2Mat;
	
	cvInitMatHeader(&A1Mat, 3, 3, CV_32F, A1);
	cvInitMatHeader(&A2Mat, 3, 3, CV_32F, A2);
	cvInitMatHeader(&d1Mat, 4, 1, CV_32F, m_intr1.distortion);
	cvInitMatHeader(&d2Mat, 4, 1, CV_32F, m_intr2.distortion);

	cvUndistort2(m_image1, m_corrected1, &A1Mat, &d1Mat);
	cvCopy(m_corrected1, m_image1);
	cvUndistort2(m_image2, m_corrected2, &A2Mat, &d2Mat);
	cvCopy(m_corrected2, m_image2);

	m_pState->Track(*this);

	now = wxGetLocalTimeMillis();
	elapsed = now - m_uLastCalcTime;
	m_framesElapsed++;
	// wait at leas 1 sec with calculations
	if (elapsed >= 1000)
	{
		m_uLastCalcTime = now;
		CalcFPS(elapsed.ToLong(), m_framesElapsed);
		m_framesElapsed = 0;
		NotifyObservers();
	}

}

void GazeTracker::SetGLWindow(void *pWindow)
{
	m_pGLWindow = pWindow;
}

//Vector3f GazeTracker::GetPosition()
//{
//	GLView* view = (GLView *) m_pGLWindow;
//	Model* model = view->GetModel();
//	return model->GetPosition();
//}

void GazeTracker::Reinitialize()
{
	void *glWindow = pInstance->GetGLWindow();
	ArrayOfObservers observers = pInstance->m_observers;
	Destroy();
	Create();
	pInstance->SetGLWindow(glWindow);
	pInstance->m_observers = observers;
	
}

void GazeTracker::CalcFPS(long uSecElapsed, long framesElapsed)
{
	m_fps = framesElapsed / ((float) uSecElapsed / 1000.0);
}