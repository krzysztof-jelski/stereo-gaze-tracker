/** @file StepPreprMedian.cpp
 *  Implementation of the StepPreprMedian class.
 */

#include "StepPreprClean.h"
#include "GlobalConfig.h"

StepPreprClean::StepPreprClean() :
	m_filterSide(* (long *) (*GlobalConfig::GetInstance()["Preprocessing"])["filterSide"]->GetValue()),
	m_filterValue(* (long *) (*GlobalConfig::GetInstance()["Preprocessing"])["filterValue"]->GetValue())
{

}

IplImage* StepPreprClean::DoPrepr(IplImage *src1, IplImage *src2)
{
	if (m_sizeData.SizeChanged(src1))
		PrepareImg(src1);

	cvCopy(src1, m_resultImg);
	CleanBinary(m_resultImg, m_filterSide, m_filterSide, m_filterValue);

	return m_resultImg;
}

void StepPreprClean::CleanBinary(IplImage* imageimg, int win_w, int win_h, int med_value)
{
	int x,y;
	int nonblack;
	CvMat image_stub, *image;// = (CvMat *)imageimg;
	CvMat* result = cvCreateMat(imageimg->height, imageimg->width, CV_8UC1);
	image = cvGetMat(imageimg, &image_stub);
	int win_w_half = win_w / 2;
	int win_h_half = win_h / 2;

	cvZero(result);


    for(y = win_h_half; y < image->rows - win_h_half; y++)
    {
        uchar* row = (uchar*)(image->data.ptr + y * image->step);
		uchar* result_row = (uchar*)(result->data.ptr + y * result->step);
        for (x = win_w_half; x < image->cols - win_w_half; x++)
        {
			nonblack = 0;
			for (int i = -win_w_half; i < win_w_half + 1; i++)
				for (int j = -win_h_half; j < win_h_half + 1; j++)
					if (((uchar *)(image->data.ptr + (y + j) * image->step))[x + i] > 0)
						nonblack++;
			if (nonblack > med_value)
				result_row[x] = 255;
        }
    }
	
	cvCopy(result, image);
	cvReleaseMat(&result);
}

