/** @file StepPreprGray.h
 *  Interface for the StepPreprGray class.
 */

#ifndef StepPreprGray_H
#define StepPreprGray_H


#include "StepPrepr.h"

class StepPreprGray : public StepPrepr
{
public:
	StepPreprGray(){};
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:

};

#endif // ifndef StepPreprGray_H