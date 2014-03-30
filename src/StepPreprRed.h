/** @file StepPreprRed.h
 *  Interface for the StepPreprRed class.
 */

#ifndef StepPreprRed_H
#define StepPreprRed_H


#include "StepPrepr.h"

class StepPreprRed : public StepPrepr
{
public:
	StepPreprRed(){};
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:

};

#endif // ifndef StepPreprRed_H