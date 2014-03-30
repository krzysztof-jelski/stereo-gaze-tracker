// TrackRunner.cpp: implementation of the TrackRunner class.
//
//////////////////////////////////////////////////////////////////////

#include "TrackRunner.h"
#include "StereoCallback.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "GlobalConfig.h"

void __cdecl callback(IplImage* image1, IplImage* image2)
{
	StereoCallback::GetInstance()->StereoCallbackFunc(image1, image2);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TrackRunner::TrackRunner() 
{
	long width, height;
	GlobalConfig & config = GlobalConfig::GetInstance();
	
	width = *(long *)((*config["Camera"])["width"])->GetValue();
	height = *(long *)((*config["Camera"])["height"])->GetValue();
	m_vidFormat.width = width;
	m_vidFormat.height = height;
	m_vidFormat.framerate = 30.0;
	m_isRunning = false;
}

TrackRunner::~TrackRunner()
{

}

void TrackRunner::Run(const wxWindow *w1, const wxWindow *w2, int cam1Num, int cam2Num)
{
	void *h1, *h2;
	h1 = w1->GetHandle();
	h2 = w2->GetHandle();

	bool is0Opened = m_cam0.open(cam1Num);
	bool is1Opened = m_cam1.open(cam2Num);

	if (!is0Opened && !is1Opened)
		return;
	m_shouldStop = false;
	m_isRunning = true;
	for (;;) {
		if (m_isPaused) {
			continue;
		}
		m_cam0.grab();
		m_cam1.grab();
		Mat image1;
		Mat image2;
		m_cam0.retrieve(image1);
		m_cam0.retrieve(image2);
		IplImage* frame1 = cvCloneImage(&(IplImage)image1);
		IplImage* frame2 = cvCloneImage(&(IplImage)image2);
		StereoCallback::GetInstance()->StereoCallbackFunc(frame1, frame2);
		if (m_shouldStop) {
			return;
		}
	}

}

void TrackRunner::Stop()
{
	m_shouldStop = true;
}

void TrackRunner::ShowCam1Prop()
{
	// TODO: Investigate if possible with highgui
}
void TrackRunner::ShowCam2Prop()
{
	// TODO: Investigate if possible with highgui
}

void TrackRunner::ChangeRes()
{
	m_cam0.set(CV_CAP_PROP_FRAME_WIDTH, m_vidFormat.width);
	m_cam0.set(CV_CAP_PROP_FRAME_HEIGHT, m_vidFormat.height);
	m_cam1.set(CV_CAP_PROP_FRAME_WIDTH, m_vidFormat.width);
	m_cam1.set(CV_CAP_PROP_FRAME_HEIGHT, m_vidFormat.height);
	UpdateConfigValues();
}

void TrackRunner::Pause()
{
	m_isPaused = true;
}

void TrackRunner::Resume()
{
	m_isPaused = false;
}

bool TrackRunner::isRunning()
{
	return m_isRunning;
}

void TrackRunner::UpdateConfigValues()
{
	(*GlobalConfig::GetInstance()["Camera"])["width"]->SetActive(true);
	(*GlobalConfig::GetInstance()["Camera"])["height"]->SetActive(true);
	long w = (long) m_vidFormat.width;
	long h = (long) m_vidFormat.height;
	(*GlobalConfig::GetInstance()["Camera"])["width"]->SetValue(&w);
	(*GlobalConfig::GetInstance()["Camera"])["height"]->SetValue(&h);
}

void TrackRunner::ApplyResFromConfig()
{
	long width, height;
	GlobalConfig & config = GlobalConfig::GetInstance();
	
	width = *(long *)((*config["Camera"])["width"])->GetValue();
	height = *(long *)((*config["Camera"])["height"])->GetValue();
	if ((m_vidFormat.width != width) || (m_vidFormat.height != height))
	{
		m_vidFormat.width = width;
		m_vidFormat.height = height;

		ApplyRes();
	}
}

void TrackRunner::ApplyRes()
{
	m_cam0.set(CV_CAP_PROP_FRAME_WIDTH, m_vidFormat.width);
	m_cam0.set(CV_CAP_PROP_FRAME_HEIGHT, m_vidFormat.height);
	m_cam1.set(CV_CAP_PROP_FRAME_WIDTH, m_vidFormat.width);
	m_cam1.set(CV_CAP_PROP_FRAME_HEIGHT, m_vidFormat.height);
}