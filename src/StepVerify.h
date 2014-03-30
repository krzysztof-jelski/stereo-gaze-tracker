/** @file StepVerify.h
 *  Interface for the StepVerify class.
 */

#ifndef StepVerify_H
#define StepVerify_H

#include "cv.h"
#include "wxprec.h"
#include "SizeData.h"
#include "StepSegmentate.h"

struct Candidate
{
	CvConnectedComp* pComp;
	long changeSum;
	int x;
	int y;
};

// we define array of candidates
WX_DECLARE_OBJARRAY(Candidate, ArrayOfCandidates);

class StepVerify  
{
public:
	StepVerify();
	virtual ~StepVerify();
	virtual ArrayOfCandidates& DoVerify(ArrayOfComponents &arrComps,
		IplImage *grayImg = NULL,
		IplImage *binImg = NULL,
		IplImage *curImg = NULL)=0;
	virtual IplImage* GetImage() { return m_resultImg; }
	static StepVerify* Create(wxString name);
	void PrepareImg(IplImage* src);
protected:
	IplImage* m_resultImg;
	SizeData m_sizeData;
	ArrayOfCandidates m_arrCands;
};

#endif // ifndef StepVerify_H