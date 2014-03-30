/** @file CalibrationState.h
 *  Interface for the CalibrationState class.
 */

#ifndef CalibrationState_H
#define CalibrationState_H

#include "TrackerState.h"

class CalibrationState : public TrackerState
{
protected:
	CalibrationState();
public:
	static void Destroy();
	static CalibrationState* GetInstance();
	static void Create();

	virtual void Track(GazeTracker& tracker);
protected:
	static CalibrationState* pInstance;

};

#endif // ifndef CalibrationState_H