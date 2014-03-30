/** @file Model.h
 *  Interface for the Model class.
 */

#ifndef Model_H
#define Model_H

#include "cvaux.h"

struct Vector3f
{
public:
	
	// A default constructor
	Vector3f() { x = 0.0; y = 0.0; z = 0.0; }

	// This is our constructor that allows us to initialize our data upon creating an instance
	Vector3f(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// Here we overload the + operator so we can add vectors together 
	Vector3f operator+(Vector3f vVector)
	{
		// Return the added vectors result.
		return Vector3f(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// Here we overload the - operator so we can subtract vectors 
	Vector3f operator-(Vector3f vVector)
	{
		// Return the subtracted vectors result
		return Vector3f(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	Vector3f operator*(float num)
	{
		// Return the scaled vector
		return Vector3f(x * num, y * num, z * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	Vector3f operator/(float num)
	{
		// Return the scale vector
		return Vector3f(x / num, y / num, z / num);
	}

	float x, y, z;						
};

class Model
{
public:
	Model();
	Vector3f GetPosition1();
	Vector3f GetPosition2();
	Vector3f GetOrigin();
	Vector3f GetCentre();
	Vector3f GetCam1Pos();
	Vector3f GetCam2Pos();
	void Init();
	void SetPosition1(Vector3f pos);
	void SetPosition1(float X, float Y, float Z);
	void SetPosition1(float x1, float y1, float x2, float y2);
	void SetPosition2(Vector3f pos);
	void SetPosition2(float X, float Y, float Z);
	void SetPosition2(float x1, float y1, float x2, float y2);
	bool Calibrate(IplImage* image1, IplImage* image2, CvSize etalon_size, float square_size);

protected:
	Vector3f m_pos1;
	Vector3f m_pos2;
	Vector3f m_orig;
	Cv3dTrackerCameraInfo * m_camInfo[2];
	Cv3dTrackerCameraIntrinsics* m_camIntr[2];
	bool m_camIntrDone;
	bool m_calibDone;
protected:
	Vector3f Find3dPosition(float x1, float y1, float x2, float y2);
	void SetCalibDone();
};

#endif // ifndef Model_H