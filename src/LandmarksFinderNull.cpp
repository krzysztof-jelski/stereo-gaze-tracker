/** @file LandmarksFinderNull.cpp
 *  Implementation of the LandmarksFinderNull class.
 */

#include "LandmarksFinderNull.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LandmarksFinderNull::LandmarksFinderNull()
{
}

LandmarksFinderNull::~LandmarksFinderNull()
{
}

bool LandmarksFinderNull::Find(IplImage* image, CvRect eyeROI)
{
	m_irisCentreFound =	m_leftCornerFound =	m_rightCornerFound = false;
	return false;
}
