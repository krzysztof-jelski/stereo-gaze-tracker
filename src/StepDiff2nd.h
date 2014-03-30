/** @file StepDiff2nd.h
 *  Interface for the StepDiff2nd class.
 */

#ifndef StepDiff2nd_H
#define StepDiff2nd_H

#include "StepDiff.h"
#include "FrameDiff.h"

class StepDiff2nd : public StepDiff
{
public:
	StepDiff2nd();
	virtual ~StepDiff2nd();
	virtual IplImage* DoDiff(IplImage* src);
protected:
	void ReInit(IplImage *src);
	void Clear();
protected:
	IplImage *m_lastImg;
	IplImage *m_lastDiffImg;
	IplImage *m_diffImg;
	IplImage *m_2ndDiffImg;
};

#endif // ifndef StepDiff2nd_H