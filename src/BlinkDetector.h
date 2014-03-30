/** @file BlinkDetector.h
 *  Interface for the BlinkDetector class.
 */


#ifndef BLINKDETECTOR_H
#define BLINKDETECTOR_H

#include "cv.h"
#include "StepDiff.h"
#include "StepPrepr.h"
#include "StepSegmentate.h"
#include "StepVerify.h"

class BlinkDetector  
{
public:
	CvRect GetLeftEyeRect();
	CvRect GetRightEyeRect();
	CvPoint GetLeftEyeCenter();
	CvPoint GetRightEyeCenter();
	CvPoint GetCenter();
	bool Detect(IplImage* image);
	BlinkDetector();
	virtual ~BlinkDetector();
protected:
	CvConnectedComp m_leftEyeComp, m_rightEyeComp;
	IplImage* m_grayImg;
	IplImage* m_diffImg;
	IplImage* m_operImg;
	IplImage* m_rotatedImg;
	IplImage* m_currImg;
	StepDiff* m_pStepDiff;
	StepPrepr* m_pStepPrepr1;
	StepPrepr* m_pStepPrepr2;
	StepPrepr* m_pStepPrepr3;
	StepSegmentate* m_pStepSegm;
	StepVerify* m_pStepVer;

	long& m_MaxChangeArea;
	ArrayOfComponents m_arrComps;
	ArrayOfCandidates m_arrCands;
};

#endif // ifndef BLINKDETECTOR_H
