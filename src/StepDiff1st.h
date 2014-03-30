/** @file StepDiff1st.h
 *  Interface for the StepDiff1st class.
 */

#ifndef StepDiff1st_H
#define StepDiff1st_H

#include "StepDiff.h"
#include "FrameDiff.h"

class StepDiff1st : public StepDiff
{
public:
	StepDiff1st(){};
	virtual IplImage* DoDiff(IplImage* src);
protected:
	FrameDiff m_Diff;

};

#endif // ifndef StepDiff1st_H