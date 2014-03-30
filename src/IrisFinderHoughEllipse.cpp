/** @file IrisFinderHough.cpp
 *  Implementation of the IrisFinderHough class.
 */

#include "IrisFinderHoughEllipse.h"
#include "ImgLib.h"
#include "math.h"
#include "Timer.h"
#include "GlobalConfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IrisFinderHough::IrisFinderHough() :
	m_eyeImg(NULL),
		m_accPrecision(*(double *)((*GlobalConfig::GetInstance()["Features"])["accPrecision"])->GetValue()),
		m_minGradStrength(*(long *)((*GlobalConfig::GetInstance()["Features"])["minGradStrength"])->GetValue()),
		m_aMin(*(long *)((*GlobalConfig::GetInstance()["Features"])["aMin"])->GetValue()),
		m_aMax(*(long *)((*GlobalConfig::GetInstance()["Features"])["aMax"])->GetValue()),
		m_bMin(*(long *)((*GlobalConfig::GetInstance()["Features"])["bMin"])->GetValue()),
		m_bMax(*(long *)((*GlobalConfig::GetInstance()["Features"])["bMax"])->GetValue()),
		m_thetaMin(*(long *)((*GlobalConfig::GetInstance()["Features"])["thetaMin"])->GetValue()),
		m_thetaMax(*(long *)((*GlobalConfig::GetInstance()["Features"])["thetaMax"])->GetValue())
{
}

IrisFinderHough::~IrisFinderHough()
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
}

void IrisFinderHough::PrepareImage(CvRect rect)
{
	if (m_eyeImg != NULL)
		cvReleaseImage(&m_eyeImg);
	m_eyeImg = cvCreateImage(cvSize(rect.width, rect.height), IPL_DEPTH_8U, 1);
}


bool IrisFinderHough::Find(IplImage* image, CvRect eyeROI)
{
	if (!ParametersValid())
		return false;
	if (m_sizeData.SizeChanged(eyeROI))
		PrepareImage(eyeROI);
	// some helper imgs
	IplImage* imgSobelH = cvCreateImage(cvSize(eyeROI.width, eyeROI.height), IPL_DEPTH_16S, 1);
	IplImage* imgSobelV = cvCreateImage(cvSize(eyeROI.width, eyeROI.height), IPL_DEPTH_16S, 1);

	// copy roi to internal image
	ImgLib::CopyRect(image, m_eyeImg, eyeROI, cvPoint(0, 0));
	cvSobel(m_eyeImg, imgSobelH, 1, 0, 3);
	cvSobel(m_eyeImg, imgSobelV, 0, 1, 3);
	
	double angle;
	double dx, dy;
	double thetaRad;
	double xPrim, yPrim;
	double xsi;
	double max_e = 2.2;

	HoughAccumulator acc(m_accPrecision);

	acc.AddParam(0, m_eyeImg->width);	// x0
	acc.AddParam(0, m_eyeImg->height);	// x1
	acc.AddParam(m_thetaMin, m_thetaMax);		// theta
	acc.AddParam(m_aMin, m_aMax);				// a
	acc.AddParam(m_bMin, m_bMax);				// b
	acc.Init();

	DOUBLEVECT indices;
	indices.resize(5);


	cvSmooth(m_eyeImg, m_eyeImg);
	cvCanny(m_eyeImg, m_eyeImg, 250, 100);


	for(int y = 0; y < m_eyeImg->height; y++)
    {
        short* sh_row = (short*)(imgSobelH->imageData + y * imgSobelH->widthStep);
		short* sv_row = (short*)(imgSobelV->imageData + y * imgSobelV->widthStep);
		uchar* canny_row = (uchar *)(m_eyeImg->imageData + y * m_eyeImg->widthStep);
		double x0, y0;
		double a, b, theta=0;

        for (int x = 0; x < m_eyeImg->width; x++)
        {
			if (canny_row[x] == 0)
				continue;
			short dX = sh_row[x];
			short dY = sv_row[x];
			if ( (abs(dX) + abs(dY)) < m_minGradStrength)
			{
				cvLine(m_eyeImg, cvPoint(x,y),cvPoint(x,y),CV_RGB(0,0,0));
				continue;
			}
			
			for (a = m_aMin; a < m_aMax; a+= (1 / m_accPrecision))
				for (b = m_bMin; b < m_bMax; b+= (1 / m_accPrecision))
				{
					double e = a / b;
					if (e < 1)
						e = b / a;
					if (e > max_e)
						continue;
					for (theta = m_thetaMin; theta < m_thetaMax; theta += (1 / m_accPrecision))
					{
						angle = atan2((float)dY, (float)dX);
						thetaRad = 2 * CV_PI * theta / 360.0;
						angle -= (thetaRad + CV_PI / 2.0);
						xsi = tan(angle);
						//xsi = (float) dY / (float) dX;
						dx = -SignX(dX, dY) * a / sqrt(1 + (b * b) / (a * a * xsi * xsi));
						dy = -SignY(dX, dY) * b / sqrt(1 + (a * a * xsi * xsi) / (b * b));
						// rotate by theta
						xPrim = cos(thetaRad) * dx - sin(thetaRad) * dy;
						yPrim = sin(thetaRad) * dx + cos(thetaRad) * dy;
						dx = xPrim; dy = yPrim;
						x0 = x + dx;
						y0 = y + dy;
						indices[0] = x0;
						indices[1] = y0;
						indices[2] = theta;
						indices[3] = a;
						indices[4] = b;
						acc.Increment(indices);
					}
				}
        }
    }

	indices = acc.FindBest();


	if (indices.size() > 0)
	{
		cvEllipse(image,
			cvPoint(indices[0] + eyeROI.x, indices[1] + eyeROI.y),
			cvSize(indices[3], indices[4]),
			-indices[2],
	//		90,
			0,
			360,
			CV_RGB(255, 0, 0));
		m_irisCentre.x = indices[0] + eyeROI.x;
		m_irisCentre.y = indices[1] + eyeROI.y;
		return true;
	}
	return false;
}

bool IrisFinderHough::ParametersValid()
{
	if (m_aMin >= m_aMax)
		return false;
	if (m_bMin >= m_bMax)
		return false;
	if (m_thetaMin >= m_thetaMax)
		return false;
	// accept values of m_accPrecision such that m_accPrecion = n or m_accPrecision = 1 / n,
	// n = 1, 2, 3 ...
	if (m_accPrecision > 1)
	{
		if (fmod(m_accPrecision, 1.0) != 0.0)
			return false;
	}
	else if (m_accPrecision < 1)
	{
		if (m_accPrecision == 0.0)
			return false;
		if (fmod(1 / m_accPrecision, 1.0) > 0.01)
			return false;
	}
	return true;
}
HoughAccumulator::HoughAccumulator(float precision) :
	precision(precision)
{

}

HoughAccumulator::~HoughAccumulator()
{
//	cvReleaseSparseMat(&acc);
	cvReleaseMatND(&acc);
	delete[] indices;
}
void HoughAccumulator::Init()
{
	int* sizes = new int[paramRanges.size()];
	for (unsigned int i = 0; i < paramRanges.size(); i++)
		sizes[i] = (paramRanges[i].max - paramRanges[i].min) * precision;
	
//	acc = cvCreateSparseMat( paramRanges.size(), sizes, CV_8UC1);
	acc = cvCreateMatND(paramRanges.size(), sizes, CV_8UC1);
	cvZero(acc);
	indices = new int[paramRanges.size()];
	delete[] sizes;
}

void HoughAccumulator::Increment(const DOUBLEVECT &params)
{
	if (paramRanges.size() != params.size())
		return;
	
	for (unsigned int i = 0; i < params.size(); i++)
	{
		indices[i] = (int) ((params[i] - (double)paramRanges[i].min) * precision);
		if ((indices[i] < 0) || (indices[i] >= acc->dim[i].size))
		{
			return;
		}
	}
	uchar *ptr =  cvPtrND(acc, indices);
	(*ptr)++;
	
}

DOUBLEVECT HoughAccumulator::FindBest()
{
	DOUBLEVECT v;
	CvMat temp;
	CvMat* locMat = cvGetMat(acc, &temp, NULL, 1);

//	int rowsize = 4 * ((acc->dims / 4) + 
//		((acc->dims % 4 > 0) ? 1 : 0));
	double max_val;
	CvPoint max_loc;
	cvMinMaxLoc(locMat, NULL, &max_val, NULL, &max_loc, NULL);
	int indraw = max_loc.x + max_loc.y * locMat->step;
	uchar* pValue = cvPtr2D(locMat, max_loc.y, max_loc.x);
	if (*pValue < 10)
		return v;
	indices[0] = indraw / acc->dim[0].step;
	indices[acc->dims - 1] = indraw % acc->dim[acc->dims - 2].step;
	for (int i = 1; i < acc->dims - 1; i ++)
		indices[i] = (indraw % acc->dim[i - 1].step) / acc->dim[i].step;

	for (int j = 0; j < acc->dims; j++)
	{
		double d = indices[j] / (float)precision + paramRanges[j].min;
		v.push_back(d);
	}
	return v;
}

/**/	

/*	int* idx;// = new int[paramRanges.size()];
	int* bestindices;
	int bestvalue = 0;
	
	
    int dims = cvGetDims(acc);
    CvSparseMatIterator mat_iterator;
    CvSparseNode* node = cvInitSparseMatIterator( acc, &mat_iterator );

    for( ; node != 0; node = cvGetNextSparseNode( &mat_iterator ))
    {
        idx = CV_NODE_IDX( acc, node ); 
		uchar val = *(uchar*)CV_NODE_VAL( acc, node );
		if ((idx[3] < 5) || (idx[4] < 5))
			continue;

		if (val > bestvalue)
		{
			bestvalue = val;
			bestindices = idx;
		}
    }

	// nothing found
	if (bestvalue == 0)
		return v;
*/