/**
 * @file SizeData.cpp
 * Implementation of SizeData class
 */

#include "SizeData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SizeData::SizeData() :
	width(1),
	height(1),
	ref_width(320),
	ref_height(240)
{
}

SizeData::~SizeData()
{
}

bool SizeData::SizeChanged(IplImage* image)
{
	bool ret = (image->width != width) || (image->height != height);
	width = image->width;
	height = image->height;
	if (ret)
		NotifyObservers();
	return ret;
}

bool SizeData::SizeChanged(const CvRect& rect)
{
	bool ret = (rect.width != width) || (rect.height != height);
	width = rect.width;
	height = rect.height;
	if (ret)
		NotifyObservers();
	return ret;
}

//float SizeData::GetScale() const
//{
//	return (float) width / (float) ref_width;
//}