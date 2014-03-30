/** @file IrisFinder.h
 *  Interface for the IrisFinder class.
 */


#ifndef IrisFinder_H
#define IrisFinder_H

#include "cv.h"
#include "SizeData.h"
#include "wxprec.h"

class IrisFinder  
{
public:
	IrisFinder() {};
	virtual ~IrisFinder() {};

	CvPoint2D32f GetIrisCentre() { return m_irisCentre; }

	static IrisFinder* Create(wxString name);
	
	virtual bool Find(IplImage* image, CvRect eyeROI) = 0;
protected:
	/// centre of iris
	CvPoint2D32f m_irisCentre;
	/// size data
	SizeData m_sizeData;

};

#endif // ifndef IrisFinder_H
