#include "ImgLib.h"

void ImgLib::DrawComponent(const CvConnectedComp& comp, IplImage* image, int line_width)
{
    CvScalar color;
	color = CV_RGB(255,0,0);
	cvRectangle(image, cvPoint(comp.rect.x, comp.rect.y), cvPoint(comp.rect.x + comp.rect.width, comp.rect.y + comp.rect.height), color, line_width);
}

int ImgLib::CountNonZero(IplImage *image, CvRect rect)
{
	int result;
	cvSetImageROI(image, rect);
	result = cvCountNonZero(image);
	cvResetImageROI(image);
	return result;

}

double ImgLib::GetAngle(int x1, int y1, int x2, int y2)
{
	int xl = x1 < x2 ? x1 : x2;
	int xr = x1 < x2 ? x2 : x1;
	int yd = x1 < x2 ? y1 : y2;
	int yu = x1 < x2 ? y2 : y1;

	double rad = atan2((double)yu - yd, (double)xr - xl);
	return (360 * rad) / (2 * 3.1415926535);
}

void ImgLib::RotateImage(IplImage *src, IplImage *dst, int centerX, int centerY, float angle)
{
    float m[6];
	double factor = 1;
    CvMat M = cvMat(2, 3, CV_32F, m);
/*    m[0] = (float)(factor*cos(-angle*2*CV_PI/180.));
    m[1] = (float)(factor*sin(-angle*2*CV_PI/180.));
    m[2] = centerX;
    m[3] = -m[1];
    m[4] = m[0];
    m[5] = centerY;*/
	cv2DRotationMatrix( cvPoint2D32f(centerX, centerY), angle,
                           1.0, &M);
	cvWarpAffine(src, dst, &M);
//    cvGetQuadrangleSubPix(image, m_rotatedImg, &M, 1, cvScalarAll(0));
}

int ImgLib::SymmetryTest(IplImage *src, CvRect rect, int max_diff)
{
	int ret = 1;
	ClipRect(rect, src->width, src->height);
	if ( (rect.width < 1) || (rect.height < 1) )
		return -1;
	CvRect half1 = cvRect(rect.x, rect.y, rect.width / 2, rect.height);
	CvRect half2 = cvRect(rect.x + half1.width, rect.y, rect.width - half1.width, rect.height);
	//CvMat *colMat = cvCreateMatHeader(rect.height, 1, CV_8UC1);
	CvMat colMat;
	int i;
	cvSetImageROI(src, half1);
	double sum1 = cvSum(src).val[0];
	double *profile1 = new double[half1.width];
	double *profile2 = new double[half2.width];

	for (i = 0; i < half1.width; i++)
	{
		cvGetCol(src, &colMat, i);
		profile1[i] = cvSum(&colMat).val[0] / sum1;
	}


	cvSetImageROI(src, half2);
	double sum2 = cvSum(src).val[0];

	for (i = 0; i < half2.width; i++)
	{
		cvGetCol(src, &colMat, i);
		profile2[i] = cvSum(&colMat).val[0] / sum2;
	}

	for (i = 0; i < half1.width - 3; i += 3)
	{
		int j = half2.width - i - 1;
		sum1 = profile1[i] + profile1[i + 1] + profile1[i + 2];
		sum2 = profile2[j] + profile2[j - 1] + profile2[j - 2];
		if ( abs( (sum1 - sum2) * 100.0 ) > max_diff)
		{
			ret = -1;
			break;
		}
	}

	cvResetImageROI(src);

	delete profile1;
	delete profile2;
	return ret;
}

void ImgLib::CopyRect(IplImage *src, IplImage *dst, CvRect srcRect, CvPoint dstPoint)
{
	ClipRect(srcRect, src->width, src->height);
	if ( (srcRect.width < 1) || (srcRect.height < 1) )
		return;
	CvMat mat;
	IplImage *img,  temp;
	cvGetSubRect(src, &mat, srcRect);
	img = cvGetImage(&mat, &temp);

	cvSetImageROI(dst, cvRect(dstPoint.x,
		dstPoint.y,
		srcRect.width,
		srcRect.height) );
//	cvCvtColor(img, dst, CV_GRAY2BGR);
	IntelligentCopy(img, dst);
	cvResetImageROI(dst);
}

void ImgLib::ClipRect(CvRect& rect, int width, int height)
{
	rect.x = rect.x < 0 ? 0 : rect.x;
	rect.y = rect.y < 0 ? 0 : rect.y;
	rect.width = rect.x + rect.width > width ? width - rect.x : rect.width;
	rect.height = rect.y + rect.height > height ? height - rect.y : rect.height;
}

void ImgLib::IntelligentCopy(IplImage *src, IplImage *dst)
{
//	if (!CV_ARE_SIZES_EQ(src, dst))
//		return;
	if (src->nChannels == dst->nChannels)
		cvCopy(src, dst);
	else if ( (src->nChannels == 1) && (dst->nChannels == 3) )
		cvCvtColor(src, dst, CV_GRAY2BGR);
	else if ( (src->nChannels == 3) && (dst->nChannels == 1) )
		cvCvtColor(src, dst, CV_BGR2GRAY);

}

void ImgLib::DrawCross(IplImage *image,
		const CvPoint &center,
		const int width,
		const int height,
		CvScalar color,
		int thickness)
{
	cvLine(image, cvPoint(center.x, center.y - (height / 2)),
		cvPoint(center.x, center.y + (height / 2)),
		color, thickness);
	cvLine(image, cvPoint(center.x - (width / 2), center.y),
		cvPoint(center.x + (width / 2), center.y),
		color, thickness);
}