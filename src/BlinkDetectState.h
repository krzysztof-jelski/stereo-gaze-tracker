/** @file BlinkDetectState.h
 *  Interface for the BlinkDetectState class.
 */

#ifndef BlinkDetectState_H
#define BlinkDetectState_H

#include "BlinkDetector.h"
#include "TrackerState.h"

class BlinkDetectState : public TrackerState
{
protected:
	BlinkDetectState();
public:
	static void Destroy();
	static BlinkDetectState* GetInstance();
	static void Create();

	virtual void Track(GazeTracker& tracker);
protected:
	static BlinkDetectState* pInstance;

	BlinkDetector m_blinkDetector1;
	BlinkDetector m_blinkDetector2;

};

#endif // ifndef BlinkDetectState_H