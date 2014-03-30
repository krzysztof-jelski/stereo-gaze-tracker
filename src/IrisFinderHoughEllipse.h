/** @file IrisFinderHough.h
 *  Interface for the IrisFinderHough class.
 */


#ifndef IrisFinderHough_H
#define IrisFinderHough_H

#include "cv.h"
#include "SizeData.h"
#include "IrisFinder.h"
#include <vector>

class IrisFinderHough : public IrisFinder
{
public:
	IrisFinderHough();
	virtual ~IrisFinderHough();

	void PrepareImage(CvRect rect);
	virtual bool Find(IplImage* image, CvRect eyeROI);
protected:
	int SignX(int x, int y)
	{
		return x > 0 ? 1 : -1;
	}
	int SignY(int x, int y)
	{
		return y > 0 ? 1 : -1;
	}
	bool ParametersValid();
protected:
	IplImage* m_eyeImg;
	double &m_accPrecision;
	long &m_minGradStrength;
	long &m_aMin, &m_aMax;
	long &m_bMin, &m_bMax;
	long &m_thetaMin, &m_thetaMax;
};

typedef struct HoughParam
{
	HoughParam(int amin, int amax)
	{
		min = amin;
		max = amax;
	}
	int min;
	int max;
} houghParam;

typedef std::vector<houghParam, std::allocator<houghParam> > PARVECT;
typedef std::vector<double, std::allocator<double> > DOUBLEVECT;

class HoughAccumulator
{
public:
	HoughAccumulator(float precision);
	~HoughAccumulator();
	void AddParam(int min, int max)
	{
		paramRanges.push_back(*(new houghParam(min, max)));
	}
	void Init();
	void Increment(const DOUBLEVECT& params);
	DOUBLEVECT FindBest();

protected:
	float precision;
	int *indices;
	PARVECT paramRanges;
//	CvSparseMat* acc;
	CvMatND* acc;
};
#endif // ifndef IrisFinderHough_H
