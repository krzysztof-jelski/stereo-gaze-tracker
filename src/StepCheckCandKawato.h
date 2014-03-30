/** @file StepCheckCandKawato.h
 *  Interface for the StepCheckCandKawato class.
 */

#ifndef StepCheckCandKawato_H
#define StepCheckCandKawato_H

#include "StepCheckCand.h"

class StepCheckCandKawato : public StepCheckCand
{
public:
	StepCheckCandKawato();
	virtual ~StepCheckCandKawato();
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

#endif // ifndef StepCheckCandKawato_H