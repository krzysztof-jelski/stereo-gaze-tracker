/** @file SizeData.h
 *  Interface for the SizeData class.
 */


#ifndef SIZEDATA_H
#define SIZEDATA_H

#include "cv.h"
#include "Observable.h"

class SizeData : public Observable
{
public:
	SizeData();
	~SizeData();
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetArea() const { return width * height; }
	bool SizeChanged(IplImage* image);
	bool SizeChanged(const CvRect& rect);
//	float GetScale() const;
protected:
	int width;
	int height;
	int ref_width;
	int ref_height;
};

#endif // ifndef SIZEDATA_H
