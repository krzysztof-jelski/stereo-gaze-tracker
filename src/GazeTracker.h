/** @file GazeTracker.h
 *  Interface for the GazeTracker class.
 */

#ifndef GazeTracker_H
#define GazeTracker_H

#include "cv.h"
#include "SizeData.h"
#include "cvaux.h"
#include "Observable.h"

class TrackerState;
struct Vector3f;


class GazeTracker : public Observable
{
protected:
	GazeTracker();
public:
	void Track(IplImage* image1, IplImage* image2);
	void StereoCallback(IplImage* image1, IplImage* image2);
	virtual ~GazeTracker();
	static GazeTracker* GetInstance();
	static void Create();
	static void Destroy();
	static void Reinitialize();

	CvPoint GetLEye1(){ return m_lEye1; }
	CvPoint GetREye1(){ return m_rEye1; }
	void SetLEye1(CvPoint l) { m_lEye1 = l; }
	void SetREye1(CvPoint r) { m_rEye1 = r; }
	CvPoint GetLEye2(){ return m_lEye2; }
	CvPoint GetREye2(){ return m_rEye2; }
	void SetLEye2(CvPoint l) { m_lEye2 = l; }
	void SetREye2(CvPoint r) { m_rEye2 = r; }
	IplImage* GetImage1() { return m_image1; }
	IplImage* GetImage2() { return m_image2; }
	void* GetGLWindow() { return m_pGLWindow; }
	void SetGLWindow(void* pGLWindow);
	float GetFPS() { return m_fps; }
	//Vector3f GetPosition();

	bool HasStateChanged() { bool ret = m_bStateChange; m_bStateChange = false; return ret; }
	TrackerState* ChangeState(TrackerState* newState);
protected:
	void CalcFPS(long uSecElapsed, long framesElapsed);
protected:
	static GazeTracker* pInstance;
	TrackerState* m_pState;
	bool m_bStateChange;
	void *m_pGLWindow;
	Cv3dTrackerCameraIntrinsics& m_intr1;
	Cv3dTrackerCameraIntrinsics& m_intr2;
	CvPoint m_lEye1, m_rEye1;
	CvPoint m_lEye2, m_rEye2;
	IplImage *m_image1, *m_image2;
	IplImage *m_corrected1, *m_corrected2;
	wxLongLong m_uLastCalcTime;
	float m_fps;
	long m_framesElapsed;
};

#endif // ifndef GazeTracker_H