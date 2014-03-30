/** @file CameraInfo.h
 *  Interface for the CameraInfo class.
 */


#ifndef CameraInfo_H
#define CameraInfo_H

#include "wxprec.h"
#include "Observer.h"
#include "SizeData.h"
#include "cv.h"
#include "cvaux.h"

class CameraInfo : public Observer
{
public:
	CameraInfo(){}
	CameraInfo(int initialWidth, int initialHeight, SizeData *pSizeData);
	void Create(int initialWidth, int initialHeight, SizeData *pSizeData);
	virtual ~CameraInfo();
	int Read(const char *filename);
	Cv3dTrackerCameraIntrinsics& Get();
	virtual void Update(Observable *observable);
protected:
	void Scale();
protected:
	Cv3dTrackerCameraIntrinsics m_intr;
	Cv3dTrackerCameraIntrinsics m_scaledIntr;
//	Cv3dTrackerCameraInfo m_extr;
	SizeData *m_pSizeData;
	int m_initialWidth, m_initialHeight;
};

#endif // #ifndef CameraIntrinsics_H
