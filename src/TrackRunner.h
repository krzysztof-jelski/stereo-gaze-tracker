/** @file GazeCallback.h
 *  Interface for the GazeCallback class.
 */

#ifndef TRACKRUNNER_H
#define TRACKRUNNER_H

#include "wxprec.h"
#include "cv.h"
#include "opencv2\highgui\highgui.hpp"

typedef struct
{
    int width;
    int height;
    double framerate;
}VidFormat;
using namespace cv;
/**
 * The TrackRunner class.
 * 
 */
class TrackRunner  
{
public:

/**
 * The Run function.
 *
 * @param w1 a parameter of type const wxWindow *
 * @param w2 a parameter of type const wxWindow *
 */
	void Run(const wxWindow *w1, const wxWindow *w2, int cam1Num = 0, int cam2Num = 1);
	void Stop();
	void ShowCam1Prop();
	void ShowCam2Prop();
	void Pause();
	void Resume();
	void ChangeRes();
	void ApplyResFromConfig();
	bool isRunning();
	wxSize GetMinSize(){
		return wxSize(m_vidFormat.width, m_vidFormat.height);
	}
	TrackRunner();
	virtual ~TrackRunner();
protected:
	void UpdateConfigValues();
	void ApplyRes();
protected:
	VidFormat m_vidFormat;
	VideoCapture m_cam0;
	VideoCapture m_cam1;
	bool m_shouldStop;
	bool m_isPaused;
	bool m_isRunning;
};

#endif // ifndef TRACKRUNNER_H
