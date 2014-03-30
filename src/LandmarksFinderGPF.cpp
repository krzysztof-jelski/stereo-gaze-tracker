#include "LandmarksFinderGPF.h"
#include "spline.H"
#include "highgui.h"
#include "ImgLib.h"
#include "GlobalConfig.h"

int LandmarksFinderGPF::m_id = 1;

LandmarksFinderGPF::LandmarksFinderGPF() :
		m_pfPrecision(*(long *)((*GlobalConfig::GetInstance()["Features"])["pfPrecision"])->GetValue()),
		m_alpha(*(double *)((*GlobalConfig::GetInstance()["Features"])["alpha"])->GetValue()),
		m_pfVertThresh(*(double *)((*GlobalConfig::GetInstance()["Features"])["pfVertThresh"])->GetValue()),
		m_pfHorizThresh(*(double *)((*GlobalConfig::GetInstance()["Features"])["pfHorizThresh"])->GetValue())
{
	m_winName.Printf("GPF %d", m_id++);
	cvNamedWindow(m_winName, CV_WINDOW_AUTOSIZE);
}

LandmarksFinderGPF::~LandmarksFinderGPF()
{
	cvDestroyWindow(m_winName);
}
bool LandmarksFinderGPF::Find(IplImage* image, CvRect eyeROI)
{
	if (!CheckParams())
		return false;
	m_irisCentreFound =	m_leftCornerFound =	m_rightCornerFound = false;

	int SHOW_FACTOR = 4;
	IplImage *grey = cvCreateImage(cvSize(eyeROI.width, eyeROI.height), IPL_DEPTH_8U, 1);
	IplImage *resampled = cvCreateImage(cvSize(eyeROI.width * m_pfPrecision, eyeROI.height * m_pfPrecision), IPL_DEPTH_8U, 3);
	IplImage *toshow = cvCreateImage(cvSize(eyeROI.width * SHOW_FACTOR, eyeROI.height * SHOW_FACTOR), IPL_DEPTH_8U, 3);
	IplImage *temp = cvCreateImage(cvSize(eyeROI.width, eyeROI.height), IPL_DEPTH_8U, 3);
	
	ImgLib::CopyRect(image, grey, eyeROI, cvPoint(0, 0));
	ImgLib::CopyRect(image, temp, eyeROI, cvPoint(0, 0));
	cvResize(temp, resampled);
	CvMat colMat;
	double *vpf = new double[grey->width];
	double max = 0;

	double VPF_SCALING_FACTOR = 255 * grey->height;
	double IPF_SCALING_FACTOR = grey->height;
	int i, j;
	double vpf_cur;

	for (i = 0; i < grey->width; i++)
	{
		cvGetCol(grey, &colMat, i);
		double Vm = cvSum(&colMat).val[0];
		Vm /= IPF_SCALING_FACTOR;
		vpf[i] = 0;
		vpf_cur = 0;
		for (j = 0; j < grey->height; j++)
		{
			uchar value = * (cvPtr1D(&colMat, j, CV_8UC1));
			vpf_cur += pow(((double) value) - Vm, 2) / VPF_SCALING_FACTOR;
		}
		vpf[i] = (1 - m_alpha) * Vm + m_alpha * vpf_cur;
		if (vpf[i] > max)
			max = vpf[i];
	}

	for (i = 0; i < grey->width; i++)
	{
		vpf[i] = vpf[i] * (resampled->height - 1) / max;
		cvCircle(resampled,
			cvPoint(i * m_pfPrecision, vpf[i]),
			1,
			CV_RGB(255,0,0));
		//cvLine(resampled, cvPoint(i * m_pfPrecision, resampled->height - 1 - vpf[i]), cvPoint(i * m_pfPrecision, resampled->height - 1 - vpf[i]), CV_RGB(255, 0, 0));
	}

	double *knots = new double[grey->width];
	double *gpfInterpolated = new double[resampled->width];
	double *gpfDer = new double[resampled->width];
	double *gpfDer2nd = new double[resampled->width];

	for (i = 0; i < grey->width; i++)
		knots[i] = i;
	double *ypp = spline_cubic_set
		(grey->width, knots, vpf, 0, 0, 0, 0);
	double value1, value2;
	double ypval1, yppval1, ypval2, yppval2;
	double gpfMax = 0.0, gpfDerMax = 0.0;
	value2 = spline_cubic_val (grey->width, knots, (double)(0) / m_pfPrecision, vpf, 
		ypp, &ypval2, &yppval2);
	for (i = 0; i < resampled->width - 1; i++)
	{
		gpfInterpolated[i] = value2;
		gpfDer[i] = ypval2;
		gpfDer2nd[i] = yppval2;
		if (value2 > gpfMax)
			gpfMax = value2;
		if (ypval2 > gpfDerMax)
			gpfDerMax = ypval2;
		value1 = value2;
		ypval1 = ypval2;
		yppval1 = yppval2;
		value2 = spline_cubic_val (grey->width, knots, (double)(i+1) / m_pfPrecision, vpf, 
			ypp, &ypval2, &yppval2);
		
	}

	gpfInterpolated[resampled->width - 1] = value2;
	gpfDer[resampled->width - 1] = ypval2;
	gpfDer2nd[i] = yppval2;
	if (value2 > gpfMax)
		gpfMax = value2;
	if (ypval2 > gpfDerMax)
		gpfDerMax = ypval2;

	double iypval1, iypval2;
	for (i = 0; i < resampled->width - 1; i++)
	{
		iypval1 = gpfDer[i] * (resampled->height - 1) / gpfDerMax;
		iypval2 = gpfDer[i + 1] * (resampled->height - 1) / gpfDerMax;
		cvLine(resampled, cvPoint(i, gpfInterpolated[i]), cvPoint(i + 1, gpfInterpolated[i + 1]), CV_RGB(0, 0, 255));
		cvLine(resampled, cvPoint(i, abs(iypval1)), cvPoint(i + 1, abs(iypval2)), CV_RGB(255, 0, 255));
	}

	
	int *indexes = 0;
	double thresh = gpfDerMax * (m_pfVertThresh / 100.0);
	cvLine(resampled, cvPoint(0, thresh * (resampled->height) / gpfDerMax), cvPoint(resampled->width - 1, thresh * (resampled->height) / gpfDerMax), CV_RGB(255, 255, 255));
	bool bFound = FindNMaxWithThresh(gpfDer, gpfDer2nd, resampled->width, thresh, 4, &indexes);
	if (bFound)
	{
		cvLine(resampled, cvPoint(indexes[0], 0), cvPoint(indexes[0], resampled->height), CV_RGB(255, 255, 255));
		cvLine(resampled, cvPoint(indexes[1], 0), cvPoint(indexes[1], resampled->height), CV_RGB(255, 255, 255));
		cvLine(resampled, cvPoint(indexes[2], 0), cvPoint(indexes[2], resampled->height), CV_RGB(255, 255, 255));
		cvLine(resampled, cvPoint(indexes[3], 0), cvPoint(indexes[3], resampled->height), CV_RGB(255, 255, 255));
	}
	delete[] indexes;
	delete[] knots;
	delete[] gpfInterpolated;
	delete[] gpfDer;
	delete[] gpfDer2nd;
	delete[] vpf;
	delete[] ypp;

	cvResize(resampled, toshow, CV_INTER_AREA);
	cvConvertImage(toshow, toshow, CV_CVTIMG_FLIP);
	cvShowImage(m_winName, toshow);
	cvReleaseImage(&grey);
	cvReleaseImage(&resampled);
	cvReleaseImage(&toshow);
	cvReleaseImage(&temp);
	

	return false;
	
}

bool LandmarksFinderGPF::CheckParams()
{
	if ((m_pfPrecision < 1) || (m_pfPrecision > 8))
		return false;
	return true;
}

bool LandmarksFinderGPF::FindNMaxWithThresh(double *der1st, double *der2nd, int arrCount, double thresh, int n, /*out*/ int **nMax)
{
	(*nMax) = new int[n];

	double EPSILON = 1;
	int nFound = 0;

	for (int i = 0; i < arrCount; i++)
	{
		if (abs(der1st[i]) < thresh) continue;
		if (abs(der2nd[i]) < EPSILON)
		{
			if (nFound < n)
				(*nMax)[nFound] = i;
			nFound++;
		}
	}

	return (nFound == n);
	return false;

}