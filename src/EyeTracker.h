/** @file EyeTracker.h
 *  Interface for the EyeTracker class.
 */


#ifndef EyeTracker_H
#define EyeTracker_H

#include "cv.h"
#include "StepCheckCand.h"
#include "SizeData.h"

class EyeTracker  
{
public:
	EyeTracker();
	virtual ~EyeTracker();

	CvPoint GetLeftEyeCenter();
	CvPoint GetRightEyeCenter();
	void SetEyePositions(CvPoint2D32f lEye, CvPoint2D32f rEye);
	void StartTracking(const CvPoint &lEye, const CvPoint &rEye, IplImage *img);

	bool Track(IplImage* image);
protected:
	CvPoint Predict();
	CvPoint MatchTemplate(IplImage *image, const CvPoint &center, int win_width, int win_height);
	CvPoint FindEye(IplImage *image, const CvPoint &center, int win_width, int win_height);
	void UpdateData(const CvPoint &lEye, const CvPoint &rEye);
	void PrepareImg(IplImage *img);
	void PrepareTemplate(IplImage *img, CvPoint center);
protected:
	// relative positions of eyes to the BTE center
	CvPoint m_el, m_er;
	// BTE center
	CvPoint m_X;
	// BTE center in previous frames
	CvPoint m_Xt_1, m_Xt_2;

	// check candidates algorithm
	StepCheckCand *m_pStepCheck;

	// BTE template
	IplImage *m_templImg;
	// template matching result
	IplImage *m_resultImg;

	// parameters
	long& m_tmplSearchH;
	long& m_tmplSearchW;
	long& m_tmplH;
	long& m_tmplW;
	long& m_eyeSearchW;
	long& m_eyeSearchH;


// size data
	SizeData m_sizeData;
};

#endif // ifndef EyeTracker_H
