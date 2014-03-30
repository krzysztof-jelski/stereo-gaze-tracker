/** @file HoughEllipseIrisFinder.cpp
 *  Implementation of the HoughEllipseIrisFinder class.
 */

#include "HoughEllipseIrisFinder.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HoughEllipseIrisFinder::HoughEllipseIrisFinder()
{
}

HoughEllipseIrisFinder::~HoughEllipseIrisFinder()
{
}

bool HoughEllipseIrisFinder::Find(IplImage* image, CvRect eyeROI)
{
	m_irisCentreFound =	m_leftCornerFound =	m_rightCornerFound = false;
	if (m_irisFinder.Find(image, eyeROI) == true)
	{
		m_irisCentreFound = true;
		m_irisCentre = m_irisFinder.GetIrisCentre();
		return true;
	}
	return false;
}
