/** @file StepSegmFFill.h
 *  Interface for the StepSegmFFill class.
 */

#ifndef StepSegmFFill_H
#define StepSegmFFill_H

#include "StepSegmentate.h"
#include "SizeData.h"

class StepSegmFFill : public StepSegmentate
{
public:
	StepSegmFFill();
	virtual ~StepSegmFFill();
	virtual ArrayOfComponents& DoSegm(IplImage* src);
protected:
	void PrepareImg(IplImage *src);
protected:
	IplImage *m_mask8u;
	SizeData m_sizeData;
};

#endif // ifndef StepSegmFFill_H