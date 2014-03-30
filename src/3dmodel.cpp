/** @file Model.cpp
 *  Implementation of the Model class.
 */

#include "3dModel.h"
#include "stdio.h"
#include "GlobalConfig.h"

#define CAMERA_POS(c) (cvPoint3D32f((c).mat[3][0], (c).mat[3][1], (c).mat[3][2]))

Model::Model() :
	m_camIntrDone(false),
	m_calibDone(false)
	
{
	m_camIntr[0] = &GlobalConfig::GetInstance().GetCam1Intrinsics();
	m_camIntr[1] = &GlobalConfig::GetInstance().GetCam2Intrinsics();
	m_camInfo[0] = GlobalConfig::GetInstance().GetCam1Extrinsics();
	m_camInfo[1] = GlobalConfig::GetInstance().GetCam2Extrinsics();
	if (GlobalConfig::GetInstance().AreExtrValid())
		SetCalibDone();
}
Vector3f Model::GetPosition1()
{
	return m_pos1;
}

Vector3f Model::GetPosition2()
{
	return m_pos2;
}

Vector3f Model::GetOrigin()
{
	return m_orig;
}

Vector3f Model::GetCam1Pos()
{
	Vector3f ret;
	CvPoint3D32f pos = CAMERA_POS(*m_camInfo[0]);
	ret.x = pos.x;
	ret.y = pos.y;
	ret.z = pos.z;
	return ret;

}
Vector3f Model::GetCam2Pos()
{
	Vector3f ret;
	CvPoint3D32f pos = CAMERA_POS(*m_camInfo[1]);
	ret.x = pos.x;
	ret.y = pos.y;
	ret.z = pos.z;
	return ret;
}
void Model::SetPosition1(Vector3f pos)
{
	m_pos1 = pos;
}
void Model::SetPosition2(Vector3f pos)
{
	m_pos2 = pos;
}
void Model::SetPosition1(float X, float Y, float Z)
{
	m_pos1.x = X;
	m_pos1.y = Y;
	m_pos1.z = Z;
}
void Model::SetPosition2(float X, float Y, float Z)
{
	m_pos2.x = X;
	m_pos2.y = Y;
	m_pos2.z = Z;
}

void Model::SetPosition1(float x1, float y1, float x2, float y2)
{
	SetPosition1(Find3dPosition(x1, y1, x2, y2));
}
void Model::SetPosition2(float x1, float y1, float x2, float y2)
{
	SetPosition2(Find3dPosition(x1, y1, x2, y2));
}
bool Model::Calibrate(IplImage* image1, IplImage* image2, CvSize etalon_size, float square_size)
{
	IplImage* samples[2] = {image1, image2};
	Cv3dTrackerCameraIntrinsics camIntr[2];
	Cv3dTrackerCameraInfo camInfo[2];
	camInfo[0] = *m_camInfo[0];
	camInfo[1] = *m_camInfo[1];
	camIntr[0] = *m_camIntr[0];
	camIntr[1] = *m_camIntr[1];
	CvBool result = cv3dTrackerCalibrateCameras(2,
                     camIntr,
                     etalon_size,
                     square_size,
                     samples,
                     camInfo);
	if (result == false)
	{
		m_calibDone = false;
		return false;
	}
	* m_camInfo[0] = camInfo[0];
	* m_camInfo[1] = camInfo[1];
	SetCalibDone();

	GlobalConfig::GetInstance().SaveCamExtrinsics(0, *m_camInfo[0]);
	GlobalConfig::GetInstance().SaveCamExtrinsics(1, *m_camInfo[1]);
	return true;
}




Vector3f Model::Find3dPosition(float x1, float y1, float x2, float y2)
{
	Vector3f res_vect;
	Cv3dTracker2dTrackedObject points2d[2];

	if (!m_calibDone)
		return res_vect;

	points2d[0].id = 1;
	points2d[1].id = 1;
	points2d[0].p.x = x1;
	points2d[0].p.y = y1;
	points2d[1].p.x = x2;
	points2d[1].p.y = y2;
	Cv3dTrackerTrackedObject result[1];
	m_camInfo[0]->principal_point = m_camIntr[0]->principal_point;
	m_camInfo[1]->principal_point = m_camIntr[1]->principal_point;
	Cv3dTrackerCameraInfo camInfo[2];
	camInfo[0] = *m_camInfo[0];
	camInfo[1] = *m_camInfo[1];
	int res = cv3dTrackerLocateObjects(2,
					1,
					camInfo,
					points2d,
					result);
	if (res == 1)
	{
		res_vect.x = -result[0].p.x;
		// invert y coord (because it was inverted in 3dTracker to match image origin)
		res_vect.y =  -result[0].p.y;
		res_vect.z = result[0].p.z;
	}

	return res_vect;
}

void Model::SetCalibDone()
{
	m_calibDone = true;
	SizeData *sd = GlobalConfig::GetInstance().GetSizeData();
	m_orig.x = 0.0; m_orig.y = 0.0; m_orig.z = 0.0;
	SetPosition1(m_orig);
	SetPosition2(m_orig);
}

void Model::Init()
{
	// init origin with centre of eyes
	m_orig = GetCentre();
}

Vector3f Model::GetCentre()
{
	return (m_pos1 + m_pos2) / 2.0;
}