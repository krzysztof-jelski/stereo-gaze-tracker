/** @file HoughEllipseIrisFinder.h
 *  Interface for the HoughEllipseIrisFinder class.
 */


#ifndef HoughEllipseIrisFinder_H
#define HoughEllipseIrisFinder_H

#include "cv.h"
#include "LandmarksFinder.h"
#include "IrisFinderHoughEllipse.h"

class HoughEllipseIrisFinder : public LandmarksFinder
{
public:
	HoughEllipseIrisFinder();
	virtual ~HoughEllipseIrisFinder();

	virtual bool Find(IplImage* image, CvRect eyeROI);
protected:
	IrisFinderHough m_irisFinder;
};

#endif // ifndef HoughEllipseIrisFinder_H
