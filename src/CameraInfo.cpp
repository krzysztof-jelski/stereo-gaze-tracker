// CameraInfo.cpp: implementation of the CameraInfo class.
//
//////////////////////////////////////////////////////////////////////
#include "CameraInfo.h"
#include "GlobalConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CameraInfo::CameraInfo(int initialWidth, int initialHeight, SizeData *pSizeData)
{
	Create(initialWidth, initialHeight, pSizeData);
}

void CameraInfo::Create(int initialWidth, int initialHeight, SizeData *pSizeData)
{
	m_initialWidth = initialWidth;
	m_initialHeight = initialHeight;
	m_pSizeData = pSizeData;

	if (m_pSizeData != NULL)
	{
		m_pSizeData->AddObserver(this);
		Scale();
	}
}

CameraInfo::~CameraInfo()
{
}

//----------------------
// Read the intrinsics information for all of the from a list of files.
// The following is an example of the format that the file is reading.
// The top left 2 diagonal elements of the matrix are the horizontal and 
// vertical focal lengths and the top 2 elements in the last column 
// indicate the image center coordinates, x in the top row, y in the second.
// 
// The Distortion parameters indicate the radial and barrel distortion of the lens.
//
// All of these results are further discussed in the documentation concerning 
// the CalibFilter.
//----------------------

/*
Camera Matrix:
M[0.0]=         401.3238525M[0.1]=           0.0000000M[0.2]=         135.9540710
M[1.0]=           0.0000000M[1.1]=         403.9630737M[1.2]=         116.6698456
M[2.0]=           0.0000000M[2.1]=           0.0000000M[2.2]=           1.0000000


Distortion:
D[0]=-0.011825
D[1]=0.241698
D[2]=0.001189
D[3]=0.003923
*/

int CameraInfo::Read(const char *filename)
{
    // read camera intrinsics: focal length[2], principal_point.x&y, distortion[4]

	Cv3dTrackerCameraIntrinsics &camera = m_intr;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return -1;

#define BUF_SIZE 500
    char buffer[BUF_SIZE+1];
    int sz = fread( buffer, 1, BUF_SIZE, file );
	fclose(file);
    buffer[sz] = '\0';

    int i, j, k;
    float camera_matrix[3][3];
    char* ptr = buffer;
    /* read matrix */
    for( k = 0; k < 9; k++ )
    {
        ptr = strstr( ptr, "M[" );
        if( ptr )
        {
            int s = 0;
            ptr += 2;
            if( sscanf( ptr, "%d%*[.,]%d%n", &i, &j, &s ) == 2 && i == k/3 && j == k%3 )
            {
                ptr += s;
                ptr = strstr( ptr, "=" );
                if( ptr )
                {
                    s = 0;
                    ptr++;
                    if( sscanf( ptr, "%f%n", &camera_matrix[i][j], &s ) == 1 )
                    {
                        ptr += s;
                        continue;
                    }
                }
            }
        }

        return -1;
    }

    camera.focal_length[0] = camera_matrix[0][0];
    camera.focal_length[1] = camera_matrix[1][1];

    camera.principal_point.x = camera_matrix[0][2];
    camera.principal_point.y = camera_matrix[1][2];

    /* read distortion */
    for( k = 0; k < 4; k++ )
    {
        ptr = strstr( ptr, "D[" );
        if( ptr )
        {
            int s = 0;
            ptr += 2;
            if( sscanf( ptr, "%d%n", &i, &s ) == 1 && i == k )
            {
                ptr += s;
                ptr = strstr( ptr, "=" );
                if( ptr )
                {
                    s = 0;
                    ptr++;
                    if( sscanf( ptr, "%f%n", &camera.distortion[k], &s ) == 1 )
                    {
                        ptr += s;
                        continue;
                    }
                }
            }
        }

        return -1;
    }
	return 1;

}

void CameraInfo::Update(Observable *observable)
{
	Scale();
}

void CameraInfo::Scale()
{
	if (m_pSizeData == NULL)
		return;
	float scaleX = (float) m_pSizeData->GetWidth() / (float) m_initialWidth;
	float scaleY = (float) m_pSizeData->GetHeight() / (float) m_initialHeight;
	m_scaledIntr.focal_length[0] = m_intr.focal_length[0] * scaleX;
	m_scaledIntr.focal_length[1] = m_intr.focal_length[1] * scaleY;
	m_scaledIntr.principal_point.x = m_intr.principal_point.x * scaleX;
	m_scaledIntr.principal_point.y = m_intr.principal_point.y * scaleY;
	// just copy the distortion coefficients
	m_scaledIntr.distortion[0] = m_intr.distortion[0];
	m_scaledIntr.distortion[1] = m_intr.distortion[1];
	m_scaledIntr.distortion[2] = m_intr.distortion[2];
	m_scaledIntr.distortion[3] = m_intr.distortion[3];

}

Cv3dTrackerCameraIntrinsics& CameraInfo::Get()
{
	return m_scaledIntr;
}