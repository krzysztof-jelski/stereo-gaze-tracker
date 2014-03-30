/** @file StepCheckCand.h
 *  Interface for the StepCheckCand class.
 */

#ifndef StepCheckCand_H
#define StepCheckCand_H

#include "cv.h"
#include "wxprec.h"
#include "SizeData.h"
#include "StepVerify.h"

class StepCheckCand  
{
public:
	StepCheckCand();
	virtual ~StepCheckCand();
	virtual int DoCheckSingle(const Candidate &cand)=0;
	virtual int DoCheckPair(const Candidate &cand1, const Candidate &cand2, IplImage *img = NULL)=0;

	static StepCheckCand* Create(wxString name);
	void PrepareImg(IplImage* src);
protected:
	IplImage* m_resultImg;
	SizeData m_sizeData;
};

#endif // ifndef StepCheckCand_H