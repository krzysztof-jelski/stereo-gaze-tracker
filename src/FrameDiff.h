/** @file FrameDiff.h
 *  Interface for the FrameDiff class.
 */


#ifndef FRAMEDIFF_H
#define FRAMEDIFF_H

#include "cv.h"

class FrameDiff  
{
public:
	IplImage* GetDiff2nd(IplImage *pNewImage);
	IplImage* GetDiff(IplImage *pNewImage);
	void SetAccDepth(int nFrames);
	FrameDiff();
	virtual ~FrameDiff();
	void ReInit() { m_bInitDone = false; }
protected:
	void Init(IplImage *pImage);
	void Clear();
	bool m_bInitDone;
	IplImage* m_pLastImage;
	IplImage* m_pDiffAcc;
	int m_nAccDepth;
};

#endif // ifndef FRAMEDIFF_H
