/** @file StepPrepr.h
 *  Interface for the StepPrepr class.
 */

#ifndef StepPrepr_H
#define StepPrepr_H

#include "cv.h"
#include "wxprec.h"
#include "SizeData.h"

class StepPrepr  
{
public:
	StepPrepr();
	virtual ~StepPrepr();
	virtual IplImage* DoPrepr(IplImage *src1, IplImage *src2 = NULL)=0;
	static StepPrepr* Create(wxString name);
	void PrepareImg(IplImage* src);
protected:
	IplImage* m_resultImg;
	SizeData m_sizeData;
};

#endif // ifndef StepPrepr_H