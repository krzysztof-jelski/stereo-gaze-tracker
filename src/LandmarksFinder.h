/** @file LandmarksFinder.h
 *  Interface for the LandmarksFinder class.
 */


#ifndef LandmarksFinder_H
#define LandmarksFinder_H

#include "cv.h"
#include "SizeData.h"
#include "EyeCornersFinder.h"
#include "IrisFinder.h"
#include "wxprec.h"

class LandmarksFinder  
{
public:
	LandmarksFinder();
	virtual ~LandmarksFinder();

	CvPoint2D32f GetIrisCentre() { return m_irisCentre; }
	CvPoint2D32f GetLeftCorner() { return m_leftCorner; }
	CvPoint2D32f GetRightCorner() { return m_rightCorner; }
	bool IsIrisCentreFound() { return m_irisCentreFound; }
	bool IsLeftCornerFound() { return m_leftCornerFound; }
	bool IsRightCornerFound() { return m_rightCornerFound; }
	// returns true if at least one landmark found
	virtual bool Find(IplImage* image, CvRect eyeROI) = 0;
	void SetIrisFinder(IrisFinder* irisFinder) { m_irisFinder = irisFinder; }
	void SetEyeCornersFinder(EyeCornersFinder* eyeCornersFinder) { m_eyeCornersFinder = eyeCornersFinder; }
	static LandmarksFinder *Create(const wxString &name);

protected:
	/// centre of iris
	CvPoint2D32f m_irisCentre;
	/// left corner of the eye
	CvPoint2D32f m_leftCorner;
	/// right corner of the eye
	CvPoint2D32f m_rightCorner;

	bool m_irisCentreFound; 
	bool m_leftCornerFound; 
	bool m_rightCornerFound;

	// size data
	SizeData m_sizeData;
protected:
	IrisFinder* m_irisFinder;
	EyeCornersFinder* m_eyeCornersFinder;
};

#endif // ifndef LandmarksFinder_H
