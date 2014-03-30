/** @file ImgLib.h
 *  Interface for the ImgLib class.
 */

#ifndef ImgLib_H
#define ImgLib_H

#include "cv.h"

class ImgLib
{
public:

/**
 * The DrawComponent function.
 * Draws a rectangle corresponding to comp on image
 *
 * @param comp connected component
 * @param image image on which to draw the rectangle
 * @param line_width rectangle line width
 */
	static void DrawComponent(const CvConnectedComp& comp, IplImage* image, int line_width);

/**
 * The CountNonZero function.
 * Count non-zero pixels in image, which fall into rect
 *
 * @param image a parameter of type IplImage *
 * @param rect a parameter of type CvRect
 *
 * @return number of pixels
 */
	static int CountNonZero(IplImage *image, CvRect rect);
/**
 * Find the angle between two points.
 *
 * @param x1 x coord of first point
 * @param y1 y coord of first point
 * @param x2 x coord of second point
 * @param y2 y coord of second point
 *
 * @return angle in degrees
 */
	static double GetAngle(int x1, int y1, int x2, int y2);
/**
 * Rotate an image.
 *
 * @param src source image
 * @param dst destination image
 * @param centerX x coord of rotation centre
 * @param centerY y coord of rotation centre
 * @param angle rotation angle in degrees
 *
 */
	static void RotateImage(IplImage *src, IplImage *dst, int centerX, int centerY, float angle);
/**
 * Test symmetry of a given image region.
 *
 * @param src source image
 * @param rect image ROI
 * @param max_diff maximum allowed difference in percent
 *
 * @return positive value if test passed
 */
	static int SymmetryTest(IplImage *src, CvRect rect, int max_diff);
/**
 * Pastes a rectangle from one image into another.
 *
 * @param src source image 
 * @param dst destination image
 * @param srcRect source rectangle
 * @param dstPoint upper-left corner of pasted rectangle on destination image
 *
 */
	static void CopyRect(IplImage *src, IplImage *dst, CvRect srcRect, CvPoint dstPoint);
/**
 * Clip a rectangle.
 * Clips a rectangle, so that it does not exceed (0,0) and (width, height) points
 *
 * @param rect rectangle to clip
 * @param width width of outer rect
 * @param height height of outer rect
 *
 */
	static void ClipRect(CvRect& rect, int width, int height);

/**
 * Copies src into dst, converting colours when needed
 *
 * @param src source image
 * @param dst destination image
 *
 * @return static void
 */
	static void IntelligentCopy(IplImage *src, IplImage *dst);

	static void DrawCross(IplImage *img,
		const CvPoint &center,
		const int width,
		const int height,
		CvScalar color,
		int thickness CV_DEFAULT(1));
};
#endif // #ifndef ImgLib_H
