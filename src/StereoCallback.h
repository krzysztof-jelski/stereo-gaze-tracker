/** @file StereoCallback.h
 *  Interface for the StereoCallback class.
 */

#ifndef StereoCallback_H
#define StereoCallback_H

#include "cv.h"
#include "GazeTracker.h"

class StereoCallback  
{
protected:
	StereoCallback();
public:
	void StereoCallbackFunc(IplImage* image1, IplImage* image2);
	virtual ~StereoCallback();
	static StereoCallback* GetInstance();
	static void Create();
	static void Destroy();
protected:
	static StereoCallback* pInstance;
};

#endif // ifndef StereoCallback_H