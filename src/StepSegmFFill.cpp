/** @file StepSegmFFill.cpp
 *  Implementation of the StepSegmFFill class.
 */

#include "StepSegmFFill.h"

StepSegmFFill::StepSegmFFill() :
	m_mask8u(NULL)
{

}
StepSegmFFill::~StepSegmFFill()
{
//	if (m_resultImg != NULL)
//		cvReleaseImage(&m_resultImg);
}

ArrayOfComponents& StepSegmFFill::DoSegm(IplImage* srcimg)
{
	if (m_sizeData.SizeChanged(srcimg))
		PrepareImg(srcimg);

//CvSeq* BlinkDetector::SegmentBinary(const CvArr* srcimg, CvArr* segmask, CvMemStorage* storage)
//{
//    CvSeq* components = 0;
//    CvMat* mask8u = 0;

    CvMat srcstub, *src = (CvMat*)srcimg;
    CvMat maskstub, *mask8u = (CvMat*)m_mask8u;
//    int comp_idx = 1;
    int x, y;

    src = cvGetMat( src, &srcstub );
    mask8u = cvGetMat( mask8u, &maskstub );

	m_arrComps.Clear();

    wxCHECK_MSG( (CV_MAT_TYPE( src->type ) == CV_8UC1 && CV_MAT_TYPE( mask8u->type ) == CV_8UC1),
        m_arrComps,
		"Array types mismatch!");

//    mask8u = cvCreateMat(src->rows + 2, src->cols + 2, CV_8UC1);
    cvZero(mask8u);
//    cvZero(mask);
//    components = cvCreateSeq( CV_SEQ_KIND_GENERIC, sizeof(CvSeq),
//                                       sizeof(CvConnectedComp), storage );

    for( y = 0; y < src->rows; y++ )
    {
        uchar* src_row = (uchar*)(src->data.ptr + y*src->step);
        uchar* mask8u_row = mask8u->data.ptr + (y+1)*mask8u->step + 1;

        for( x = 0; x < src->cols; x++ )
        {
            if( src_row[x] > 0 && mask8u_row[x] == 0 )
            {
                CvConnectedComp comp;
//                int x1, y1;
                CvScalar lo_diff = cvRealScalar(src_row[x] - 1.0);
				CvScalar up_diff = cvRealScalar(255 - src_row[x]);
                CvPoint seed = cvPoint(x,y);

                cvFloodFill( src, seed, cvRealScalar(0), lo_diff, up_diff,
                                      &comp, CV_FLOODFILL_MASK_ONLY + 2*256 + 8, mask8u );

//				if (CheckCandidate(comp))
//				{
//					for( y1 = 0; y1 < comp.rect.height; y1++ )
//					{
//						uchar* mask_row1 = (uchar*)(mask->data.ptr +
//										(comp.rect.y + y1)*mask->step) + comp.rect.x;
//						uchar* mask8u_row1 = mask8u->data.ptr +
//										(comp.rect.y + y1+1)*mask8u->step + comp.rect.x+1;

//						for( x1 = 0; x1 < comp.rect.width; x1++ )
//						{
//							if( mask8u_row1[x1] > 0 )
//							{
	//							mask8u_row1[x1] = 1;
//								mask_row1[x1] = comp_idx;
//							}
//						}
//					}
//					comp_idx++;
					m_arrComps.Add(comp);
//					cvSeqPush( components, &comp );
//				}
            }
        }
    }

//    cvReleaseMat( &mask8u );

    return m_arrComps;
	
}


void StepSegmFFill::PrepareImg(IplImage *src)
{
	if (m_mask8u != NULL)
		cvReleaseImage(&m_mask8u);
	m_mask8u = cvCreateImage(cvSize(m_sizeData.GetWidth() + 2, m_sizeData.GetHeight() + 2),
		IPL_DEPTH_8U,
		1);
}