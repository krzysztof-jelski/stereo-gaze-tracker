// StereoCallback.cpp: implementation of the StereoCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "StereoCallback.h"

StereoCallback* StereoCallback::pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StereoCallback::StereoCallback()
{
}

StereoCallback::~StereoCallback()
{
	GazeTracker::Destroy();
}

void StereoCallback::Destroy()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
StereoCallback* StereoCallback::GetInstance()
{
	if (pInstance == NULL)
		Create();
	return pInstance;
}
void StereoCallback::Create()
{
	pInstance = new StereoCallback();
}

void StereoCallback::StereoCallbackFunc(IplImage *image1, IplImage *image2)
{
	GazeTracker::GetInstance()->Track(image1, image2);
}
