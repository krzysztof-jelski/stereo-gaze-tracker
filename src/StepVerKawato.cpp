/** @file StepVerKawato.cpp
 *  Implementation of the StepVerKawato class.
 */

#include "StepVerKawato.h"
#include "ImgLib.h"
#include "GlobalConfig.h"

int compare(  Candidate **arg1,  Candidate **arg2 )
{
	return ((*arg2)->changeSum - (*arg1)->changeSum);
}


StepVerKawato::StepVerKawato() : 
	m_rotatedImg(NULL),
	m_pStepCheck(NULL),
	m_eyeWidth(* (long *) (*GlobalConfig::GetInstance()["Eye"])["eyeWidth"]->GetValue()),
	m_eyeHeight(* (long *) (*GlobalConfig::GetInstance()["Eye"])["eyeHeight"]->GetValue())
{
	m_pStepCheck = StepCheckCand::Create("StepCheckCandKawato");
}
StepVerKawato::~StepVerKawato()
{
	if (m_pStepCheck != NULL)
		delete m_pStepCheck;
}

void StepVerKawato::PrepareImg(IplImage *src)
{
	StepVerify::PrepareImg(src);
	if (m_rotatedImg != NULL)
		cvReleaseImage(&m_rotatedImg);
	m_rotatedImg = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
}
ArrayOfCandidates& StepVerKawato::DoVerify(ArrayOfComponents &arrComps,
		IplImage *grayImg,
		IplImage *binImg,
		IplImage *curImg)
{
	// clear candidates array
	m_arrCands.Clear();

	// check input
	if ((grayImg == NULL) || (binImg == NULL))
		return m_arrCands;

	// check image size
	if (m_sizeData.SizeChanged(grayImg))
		PrepareImg(grayImg);

	// prepare resulting image
	cvZero(m_resultImg);
	if (curImg != NULL)
		ImgLib::IntelligentCopy(curImg, m_resultImg);
	if (arrComps.GetCount() < 2)
		return m_arrCands;

	// prepare candidates
	FindBest(arrComps, binImg);

	// check if we found enough
	if (m_arrTemp.GetCount() < 2)
		return m_arrCands;

	// sort candidates
	m_arrTemp.Sort(compare);

	// check two best candidates
	if (m_pStepCheck->DoCheckPair(m_arrTemp[0], m_arrTemp[1], grayImg) > 0)
	{
		m_arrCands.Add(m_arrTemp[0]);
		m_arrCands.Add(m_arrTemp[1]);
	}

	// return what we've got here
	return m_arrCands;
}

void StepVerKawato::FindBest(ArrayOfComponents &arrComps, IplImage *binImg)
{
	Candidate cand;
	CvRect eyeRoi;

	m_arrTemp.Clear();
	for(unsigned int i = 0; i < arrComps.GetCount(); i++)
	{
		CvConnectedComp &comp = arrComps[i];
		cand.x = comp.rect.x + comp.rect.width / 2;
		cand.y = comp.rect.y + comp.rect.height / 2;
		eyeRoi.x = cand.x - (m_eyeWidth / 2);
		eyeRoi.y = cand.y - (m_eyeHeight / 2);
		eyeRoi.width = m_eyeWidth;
		eyeRoi.height = m_eyeHeight;
		cand.changeSum = ImgLib::CountNonZero(binImg, eyeRoi);
		cand.pComp = &comp;
		if (m_pStepCheck->DoCheckSingle(cand) > 0)
			m_arrTemp.Add(cand);
	}

}

