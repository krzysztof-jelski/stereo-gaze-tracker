/** @file StepPreprAdaptBin.h
 *  Interface for the StepPreprAdaptBin class.
 */

#ifndef StepPreprAdaptBin_H
#define StepPreprAdaptBin_H

#include "StepPrepr.h"

class StepPreprAdaptBin : public StepPrepr
{
public:
	StepPreprAdaptBin();
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:
	// parameters
	long& m_binThresh;
	long& m_adaptThreshSide ;
	
};

#endif // ifndef StepPreprAdaptBin_H