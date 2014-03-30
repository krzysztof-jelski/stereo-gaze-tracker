/** @file IrisFinderFit.h
 *  Interface for the IrisFinderFit class.
 */


#ifndef IrisFinderFit_H
#define IrisFinderFit_H

#include "cv.h"
#include "SizeData.h"
#include "IrisFinder.h"

class IrisFinderFit : public IrisFinder
{
public:
	IrisFinderFit();
	virtual ~IrisFinderFit();

	void PrepareImage(CvRect rect);
	virtual bool Find(IplImage* image, CvRect eyeROI);
protected:
    CvMemStorage* m_storage;
    CvSeq* m_contours;
	IplImage* m_eyeImg;

};

#endif // ifndef IrisFinderFit_H
