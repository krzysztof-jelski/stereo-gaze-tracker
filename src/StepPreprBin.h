/** @file StepPreprBin.h
 *  Interface for the StepPreprBin class.
 */

#ifndef StepPreprBin_H
#define StepPreprBin_H

#include "StepPrepr.h"

class StepPreprBin : public StepPrepr
{
public:
	StepPreprBin();
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:
	// parameters
	long &m_binThresh;

};

#endif // ifndef StepPreprBin_H