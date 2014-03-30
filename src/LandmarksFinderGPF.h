/** @file LandmarksFinderGPF.h
 *  Interface for the LandmarksFinderGPF class.
 */


#ifndef LandmarksFinderGPF_H
#define LandmarksFinderGPF_H

#include "LandmarksFinder.h"
#include "cv.h"
#include "wxprec.h"

class LandmarksFinderGPF : public LandmarksFinder
{
public:
	LandmarksFinderGPF();
	virtual ~LandmarksFinderGPF();
	virtual bool Find(IplImage* image, CvRect eyeROI);
protected:
	bool CheckParams();
	bool FindNMaxWithThresh(double *der1st, double *der2nd, int arrCount, double thresh, int n, /*out*/ int **nMax);

protected:
	//parameters
	long &m_pfPrecision;
	double &m_alpha;
	double &m_pfVertThresh;
	double &m_pfHorizThresh;
	wxString m_winName;
	static int m_id;
};

#endif // ifndef LandmarksFinderGPF_H
