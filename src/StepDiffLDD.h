/** @file StepDiffLDD.h
 *  Interface for the StepDiffLDD class.
 */

#ifndef StepDiffLDD_H
#define StepDiffLDD_H

#include "StepDiff.h"

class StepDiffLDD : public StepDiff
{
public:
	StepDiffLDD();
	virtual ~StepDiffLDD();
	virtual IplImage* DoDiff(IplImage* src);
protected:
	void ReInit(IplImage *src);
	void Clear();
protected:
	IplImage *m_diffImg;
	IplImage *m_lastImg;

	// parameters
	long& m_LDDBoxSide;
	double& m_LDDThresh;

};

#endif // ifndef StepDiffLDD_H