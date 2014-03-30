/** @file StepPreprHue.h
 *  Interface for the StepPreprHue class.
 */

#ifndef StepPreprHue_H
#define StepPreprHue_H


#include "StepPrepr.h"

class StepPreprHue : public StepPrepr
{
public:
	StepPreprHue();
	virtual ~StepPreprHue();
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL);
protected:
	void PrepareImg(IplImage *src);
protected:
	IplImage *m_hsvImg;
};

#endif // ifndef StepPreprHue_H