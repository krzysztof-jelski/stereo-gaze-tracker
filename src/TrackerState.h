/** @file TrackerState.h
 *  Interface for the TrackerState class.
 */

#ifndef TrackerState_H
#define TrackerState_H

#include "GazeTracker.h"

class TrackerState  
{
public:
	TrackerState(){};
	virtual void Track(GazeTracker& tracker)=0;
protected:
};

#endif // ifndef TrackerState_H