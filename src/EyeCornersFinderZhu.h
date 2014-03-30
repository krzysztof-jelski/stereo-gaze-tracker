/** @file EyeCornersFinderZhu.h
 *  Interface for the EyeCornersFinderZhu class.
 */


#ifndef EyeCornersFinderZhu_H
#define EyeCornersFinderZhu_H

#include "cv.h"
#include "SizeData.h"
#include "EyeCornersFinder.h"

class EyeCornersFinderZhu : public EyeCornersFinder 
{
public:
	EyeCornersFinderZhu();
	virtual ~EyeCornersFinderZhu();

	virtual bool Find(IplImage* image, CvRect eyeROI, CvPoint2D32f irisCentre);
protected:
	void PrepareImage(const CvRect& rect);
protected:
	IplImage* m_eyeImg;

};

#endif // ifndef EyeCornersFinderZhu_H
