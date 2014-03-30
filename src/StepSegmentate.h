/** @file StepSegmentate.h
 *  Interface for the StepSegmentate class.
 */

#ifndef StepSegmentate_H
#define StepSegmentate_H

#include "cv.h"
#include "wxprec.h"
#include "SizeData.h"

// we define array of connected components
WX_DECLARE_OBJARRAY(CvConnectedComp, ArrayOfComponents);

class StepSegmentate  
{
public:
	StepSegmentate();
	virtual ~StepSegmentate();
	virtual ArrayOfComponents& DoSegm(IplImage* src)=0;
	static StepSegmentate* Create(wxString name);
protected:
//	void PrepareImg(IplImage* src);
protected:
//	IplImage* m_resultImg;
	ArrayOfComponents m_arrComps;
//	SizeData m_sizeData;
};

#endif // ifndef StepSegmentate_H