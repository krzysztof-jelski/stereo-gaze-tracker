/** @file StepPreprCvAdaptBin.h
 *  Interface for the StepPreprCvAdaptBin class.
 */

#ifndef StepPreprCvAdaptBin_H
#define StepPreprCvAdaptBin_H

#include "StepPrepr.h"

class StepPreprCvAdaptBin : public StepPrepr
{
public:
	StepPreprCvAdaptBin();
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:
	// parameters
	long &m_binThresh;

};

#endif // ifndef StepPreprCvAdaptBin_H