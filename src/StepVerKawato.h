/** @file StepVerKawato.h
 *  Interface for the StepVerKawato class.
 */

#ifndef StepVerKawato_H
#define StepVerKawato_H

#include "StepVerify.h"
#include "StepCheckCand.h"

class StepVerKawato : public StepVerify
{
public:
	StepVerKawato();
	virtual ~StepVerKawato();
	virtual ArrayOfCandidates& DoVerify(ArrayOfComponents &arrComps,
		IplImage *grayImg = NULL,
		IplImage *binImg = NULL,
		IplImage *curImg = NULL);
protected:
	void FindBest(ArrayOfComponents &arrComps, IplImage *binImg);
	int CheckCandidatePair(const Candidate &cand1, const Candidate &cand2, IplImage *grayImg);
	void PrepareImg(IplImage *src);
protected:
	ArrayOfCandidates m_arrTemp;
	IplImage *m_rotatedImg;
	StepCheckCand *m_pStepCheck;
	// parameters
	long& m_eyeWidth;
	long& m_eyeHeight;

};

#endif // ifndef StepVerKawato_H