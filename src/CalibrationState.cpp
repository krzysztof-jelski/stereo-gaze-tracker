// CalibrationState.cpp: implementation of the CalibrationState class.
//
//////////////////////////////////////////////////////////////////////

#include "CalibrationState.h"
#include "cv.h"
#include "BlinkDetectState.h"
#include "ImgLib.h"
#include "GLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CalibrationState* CalibrationState::pInstance = NULL;

CalibrationState::CalibrationState()
{
}
void CalibrationState::Destroy()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
CalibrationState* CalibrationState::GetInstance()
{
	if (pInstance == NULL)
		Create();
	return pInstance;
}
void CalibrationState::Create()
{
	pInstance = new CalibrationState();
}

void CalibrationState::Track(GazeTracker& tracker)
{
	IplImage *image1 = tracker.GetImage1();
	IplImage *image2 = tracker.GetImage2();
	GLView *view = (GLView  *) tracker.GetGLWindow();
	Model *model = view->GetModel();
	bool result = model->Calibrate(image1, image2, cvSize(3, 6), 3.75);
	if (result == true)
	{
		view->Refresh();
		tracker.ChangeState(BlinkDetectState::GetInstance());
	}
}

