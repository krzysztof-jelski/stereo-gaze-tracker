// BTETrackState.cpp: implementation of the BTETrackState class.
//
//////////////////////////////////////////////////////////////////////

#include "BTETrackState.h"
#include "cv.h"
#include "BlinkDetectState.h"
#include "ImgLib.h"
#include "GlobalConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BTETrackState* BTETrackState::pInstance = NULL;

BTETrackState::BTETrackState() : 
	m_landmarksFinder1(NULL),
	m_landmarksFinder2(NULL),
	m_landmarksFinder3(NULL),
	m_landmarksFinder4(NULL),
	m_inputController(NULL),
	m_eyeWidth(* (long *) (*GlobalConfig::GetInstance()["Eye"])["eyeWidth"]->GetValue()),
	m_eyeHeight(* (long *) (*GlobalConfig::GetInstance()["Eye"])["eyeHeight"]->GetValue())

{
	GlobalConfig & config = GlobalConfig::GetInstance();
	m_landmarksFinder1 = LandmarksFinder::Create(config.GetAlgoName("LandmarksFinder"));
	m_landmarksFinder2 = LandmarksFinder::Create(config.GetAlgoName("LandmarksFinder"));
	m_landmarksFinder3 = LandmarksFinder::Create(config.GetAlgoName("LandmarksFinder"));
	m_landmarksFinder4 = LandmarksFinder::Create(config.GetAlgoName("LandmarksFinder"));
	m_inputController = InputController::Create(config.GetAlgoName("InputController"));
	
}
BTETrackState::~BTETrackState()
{
	if (m_landmarksFinder1 != NULL)
		delete m_landmarksFinder1;
	if (m_landmarksFinder2 != NULL)
		delete m_landmarksFinder2;
	if (m_landmarksFinder3 != NULL)
		delete m_landmarksFinder3;
	if (m_landmarksFinder4 != NULL)
		delete m_landmarksFinder4;
	if (m_inputController != NULL)
		delete m_inputController;
}
void BTETrackState::Destroy()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
BTETrackState* BTETrackState::GetInstance()
{
	if (pInstance == NULL)
		Create();
	return pInstance;
}
void BTETrackState::Create()
{
	pInstance = new BTETrackState();
}

void BTETrackState::Track(GazeTracker& tracker)
{
	IplImage *image1 = tracker.GetImage1();
	IplImage *image2 = tracker.GetImage2();
	GLView *view =NULL;
	Model *model = NULL;
	view = (GLView  *) tracker.GetGLWindow();
	if (view)
		model = view->GetModel();

	m_grayImg1 = m_stepGray1.DoPrepr(image1);
	m_grayImg2 = m_stepGray2.DoPrepr(image2);

	bool bTracked1 = false, bTracked2 = false;
	bool bStateChanged = tracker.HasStateChanged();

	if (bStateChanged)
	{
		m_eyeTracker1.StartTracking(tracker.GetLEye1(), tracker.GetREye1(), m_grayImg1);
		m_eyeTracker2.StartTracking(tracker.GetLEye2(), tracker.GetREye2(), m_grayImg2);
	}
	bTracked1 = m_eyeTracker1.Track(m_grayImg1);
	bTracked2 = m_eyeTracker2.Track(m_grayImg2);
	if (! (bTracked1 && bTracked2) )
	{
		tracker.ChangeState(BlinkDetectState::GetInstance());
		return;
	}
	CvPoint lEye1 = m_eyeTracker1.GetLeftEyeCenter();
	CvPoint rEye1 = m_eyeTracker1.GetRightEyeCenter();

	CvPoint lEye2 = m_eyeTracker2.GetLeftEyeCenter();
	CvPoint rEye2 = m_eyeTracker2.GetRightEyeCenter();

	///////////////////////////////////////////////////////////////////////////
	// find the features
	///////////////////////////////////////////////////////////////////////////
	bool bFound1L, bFound1R, bFound2L, bFound2R;

	CvRect lEye1ROI = cvRect(lEye1.x - m_eyeWidth / 2, lEye1.y - m_eyeHeight / 2, m_eyeWidth, m_eyeHeight);
	CvRect rEye1ROI = cvRect(rEye1.x - m_eyeWidth / 2, rEye1.y - m_eyeHeight / 2, m_eyeWidth, m_eyeHeight);
	CvRect lEye2ROI = cvRect(lEye2.x - m_eyeWidth / 2, lEye2.y - m_eyeHeight / 2, m_eyeWidth, m_eyeHeight);
	CvRect rEye2ROI = cvRect(lEye2.x - m_eyeWidth / 2, lEye2.y - m_eyeHeight / 2, m_eyeWidth, m_eyeHeight);
	ImgLib::ClipRect(lEye1ROI, m_grayImg1->width, m_grayImg1->height);
	ImgLib::ClipRect(rEye1ROI, m_grayImg1->width, m_grayImg1->height);
	ImgLib::ClipRect(lEye2ROI, m_grayImg1->width, m_grayImg1->height);
	ImgLib::ClipRect(rEye2ROI, m_grayImg1->width, m_grayImg1->height);
	bFound1L = m_landmarksFinder1->Find(image1, lEye1ROI);
	bFound1R = m_landmarksFinder2->Find(image1, rEye1ROI);
	bFound2L = m_landmarksFinder3->Find(image2, lEye2ROI);
	bFound2R = m_landmarksFinder4->Find(image2, rEye2ROI);

	if ( (m_landmarksFinder1->IsIrisCentreFound()) && (m_landmarksFinder2->IsIrisCentreFound()) )
		m_eyeTracker1.SetEyePositions(m_landmarksFinder1->GetIrisCentre(), m_landmarksFinder2->GetIrisCentre());
	if ( (m_landmarksFinder3->IsIrisCentreFound()) && (m_landmarksFinder4->IsIrisCentreFound()) )
		m_eyeTracker2.SetEyePositions(m_landmarksFinder3->GetIrisCentre(), m_landmarksFinder4->GetIrisCentre());
	///////////////////////////////////////////////////////////////////////////
	// draw something more
	///////////////////////////////////////////////////////////////////////////
	ImgLib::DrawCross(image1, lEye1, 16, 16, CV_RGB(255, 255, 255));
	ImgLib::DrawCross(image1, rEye1, 16, 16, CV_RGB(255, 255, 255));


	ImgLib::DrawCross(image2, lEye2, 16, 16, CV_RGB(255, 255, 255));
	ImgLib::DrawCross(image2, rEye2, 16, 16, CV_RGB(255, 255, 255));



	if (model)
	{
		model->SetPosition1( lEye1.x,
			lEye1.y,
			lEye2.x,
			lEye2.y);
		model->SetPosition2( rEye1.x,
			rEye1.y,
			rEye2.x,
			rEye2.y);
		Vector3f pos1 = model->GetPosition1();
		Vector3f pos2 = model->GetPosition2();
		if (bStateChanged)
		{
			model->Init();
			m_inputController->Init(pos1.x, pos1.y, pos1.z);
			m_inputController->On();
		}
		else
		{
			m_inputController->Process(pos1.x, pos1.y, pos1.z);
		}
		if (m_inputController->IsMouseDown())
		{
			cvRectangle(image1, cvPoint(0, 0), cvPoint(image1->width, image1->height),
				CV_RGB(255, 0, 0), 3);
			cvRectangle(image2, cvPoint(0, 0), cvPoint(image1->width, image1->height),
				CV_RGB(255, 0, 0), 3);
		}
		view->Refresh();
	}


}

