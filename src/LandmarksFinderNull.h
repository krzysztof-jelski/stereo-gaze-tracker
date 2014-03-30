/** @file LandmarksFinderNull.h
 *  Interface for the LandmarksFinderNull class.
 */


#ifndef LandmarksFinderNull_H
#define LandmarksFinderNull_H

#include "LandmarksFinder.h"

class LandmarksFinderNull : public LandmarksFinder
{
public:
	LandmarksFinderNull();
	virtual ~LandmarksFinderNull();

	virtual bool Find(IplImage* image, CvRect eyeROI);
};

#endif // ifndef LandmarksFinderNull_H
