/** @file StepDiff.h
 *  Interface for the StepDiff class.
 */

#ifndef StepDiff_H
#define StepDiff_H

#include "cv.h"
#include "wxprec.h"
#include "SizeData.h"

class StepDiff  
{
public:
	StepDiff(){};
	virtual IplImage* DoDiff(IplImage* src)=0;
	static StepDiff* Create(wxString name);
protected:
	SizeData m_sizeData;
};

#endif // ifndef StepDiff_H