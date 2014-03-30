/** @file BTETrackState.h
 *  Interface for the BTETrackState class.
 */

#ifndef BTETrackState_H
#define BTETrackState_H

#include "TrackerState.h"
#include "EyeTracker.h"
#include "StepPreprGray.h"
#include "GLView.h"
#include "LandmarksFinder.h"
#include "IrisFinder.h"
#include "EyeCornersFinder.h"
#include "InputController.h"

class BTETrackState : public TrackerState
{
protected:
	BTETrackState();
public:
	virtual ~BTETrackState();
	static void Destroy();
	static BTETrackState* GetInstance();
	static void Create();

	virtual void Track(GazeTracker& tracker);
protected:
	static BTETrackState* pInstance;

	EyeTracker m_eyeTracker1, m_eyeTracker2;
	IplImage *m_grayImg1, *m_grayImg2;
	StepPreprGray m_stepGray1, m_stepGray2;
//	GLView m_glView;
	LandmarksFinder *m_landmarksFinder1;
	LandmarksFinder *m_landmarksFinder2;
	LandmarksFinder *m_landmarksFinder3;
	LandmarksFinder *m_landmarksFinder4;
	InputController *m_inputController;
	// parameters
	long& m_eyeWidth;
	long& m_eyeHeight;
};

#endif // ifndef BTETrackState_H