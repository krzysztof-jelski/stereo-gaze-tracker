/** @file IrisFinderHoughCircle.h
 *  Interface for the IrisFinderHoughCircle class.
 */


#ifndef IrisFinderHoughCircle_H
#define IrisFinderHoughCircle_H

#include "cv.h"
#include "SizeData.h"
#include "IrisFinder.h"
#include <vector>

class IrisFinderHoughCircle : public IrisFinder
{
public:
	IrisFinderHoughCircle();
	virtual ~IrisFinderHoughCircle();

	void PrepareImage(CvRect rect);
	virtual bool Find(IplImage* image, CvRect eyeROI);

protected:
	IplImage* m_eyeImg;

};

#endif
