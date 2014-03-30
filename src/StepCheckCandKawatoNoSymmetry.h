/** @file StepCheckCandKawatoNoSymmetry.h
 *  Interface for the StepCheckCandKawatoNoSymmetry class.
 */

#ifndef StepCheckCandKawatoNoSymmetry_H
#define StepCheckCandKawatoNoSymmetry_H

#include "StepCheckCand.h"

class StepCheckCandKawatoNoSymmetry : public StepCheckCand
{
public:
	StepCheckCandKawatoNoSymmetry();
	virtual ~StepCheckCandKawatoNoSymmetry();
	virtual int DoCheckSingle(const Candidate &cand);
	virtual int DoCheckPair(const Candidate &cand1, const Candidate &cand2, IplImage *img=NULL);
protected:
	void PrepareImg(IplImage *src);
protected:

// parameters
	long& m_minEyeChange;
	long& m_eyesWidth;
	long& m_eyesHeight;
	long& m_maxSymDiff;
	long& m_minDist;
	long& m_maxDist;
	long& m_maxAngle;

	IplImage *m_rotatedImg;
};

#endif // ifndef StepCheckCandKawatoNoSymmetry_H