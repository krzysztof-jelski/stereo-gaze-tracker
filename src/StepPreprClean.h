/** @file StepPreprMedian.h
 *  Interface for the StepPreprMedian class.
 */

#ifndef StepPreprMedian_H
#define StepPreprMedian_H

#include "StepPrepr.h"

class StepPreprClean : public StepPrepr
{
public:
	StepPreprClean();
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:
	void CleanBinary(IplImage* imageimg, int win_w, int win_h, int med_value);
protected:
	// parameters
	long& m_filterSide;
	long& m_filterValue;

};

#endif // ifndef StepPreprMedian_H