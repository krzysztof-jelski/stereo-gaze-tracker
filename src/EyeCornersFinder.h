/** @file EyeCornersFinder.h
 *  Interface for the EyeCornersFinder class.
 */


#ifndef EyeCornersFinder_H
#define EyeCornersFinder_H

#include "cv.h"
#include "SizeData.h"
#include "wxprec.h"

class EyeCornersFinder  
{
public:
	EyeCornersFinder() {};
	virtual ~EyeCornersFinder() {};

	CvPoint2D32f GetLeftCorner() { return m_leftCorner; }
	CvPoint2D32f GetRightCorner() { return m_rightCorner; }
	static EyeCornersFinder* Create(wxString name);
	virtual bool Find(IplImage* image, CvRect eyeROI, CvPoint2D32f irisCentre) = 0;
protected:
	/// left corner of the eye
	CvPoint2D32f m_leftCorner;
	/// right corner of the eye
	CvPoint2D32f m_rightCorner;
	// size data
	SizeData m_sizeData;
};

#endif // ifndef EyeCornersFinder_H
