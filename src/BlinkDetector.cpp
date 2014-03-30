/** @file BlinkDetector.cpp
 *  Implementation of the BlinkDetector class.
 */
#include "wxprec.h"
#include "BlinkDetector.h"
#include "GlobalConfig.h"
#include "ImgLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BlinkDetector::BlinkDetector():
	m_grayImg(NULL),
	m_diffImg(NULL),
	m_operImg(NULL),
	m_rotatedImg(NULL),
	m_currImg(NULL),
	m_MaxChangeArea(*(long *)((*GlobalConfig::GetInstance()["Preprocessing"])["maxChangeArea"])->GetValue())
{
	GlobalConfig& config = GlobalConfig::GetInstance();

	m_pStepDiff = StepDiff::Create(config.GetAlgoName("StepDiff"));
	m_pStepPrepr1 = StepPrepr::Create(config.GetAlgoName("StepPrepr1"));
	m_pStepPrepr2 = StepPrepr::Create(config.GetAlgoName("StepPrepr2"));
	m_pStepPrepr3 = StepPrepr::Create(config.GetAlgoName("StepPrepr3"));
	m_pStepSegm = StepSegmentate::Create(config.GetAlgoName("StepSegm"));
	m_pStepVer = StepVerify::Create(config.GetAlgoName("StepVer"));
	m_pStepVer = StepVerify::Create("StepVerKawato");
	
//	ConfigStructures::GetInstance().RegisterParameter("Preprocessing", "maxChangeArea");
	


}

BlinkDetector::~BlinkDetector()
{
	if (m_pStepDiff != NULL)
		delete m_pStepDiff;
	if (m_pStepPrepr1 != NULL)
		delete m_pStepPrepr1;
	if (m_pStepPrepr2 != NULL)
		delete m_pStepPrepr2;
	if (m_pStepPrepr3 != NULL)
		delete m_pStepPrepr3;
	if (m_pStepSegm != NULL)
		delete m_pStepSegm;
	if (m_pStepVer != NULL)
		delete m_pStepVer;
}


bool BlinkDetector::Detect(IplImage *image)
{
	bool bFound = false;

	m_currImg = image;

	// first pre-processing step
	m_grayImg = m_pStepPrepr1->DoPrepr(image);

//	m_currImg = m_grayImg;

	// creating a difference image
	m_diffImg = m_pStepDiff->DoDiff(m_grayImg);
//	m_currImg = m_diffImg;

	// second pre-processing step
	m_operImg = m_pStepPrepr2->DoPrepr(m_diffImg, m_grayImg);
//	m_currImg = m_operImg;
	
	// and the third pre-processing step
	m_operImg = m_pStepPrepr3->DoPrepr(m_operImg);
//	m_currImg = m_operImg;
	// check for change size
	int d = cvCountNonZero(m_operImg);
	if (d >= m_MaxChangeArea)
	{
 		wxLogDebug("[Rej:] za du¿o zmian (%d)", d);
		ImgLib::IntelligentCopy(m_currImg, image);
		return bFound;
	}
	
	// segmentation step
	m_arrComps = m_pStepSegm->DoSegm(m_operImg);

	// verification step
	m_arrCands = m_pStepVer->DoVerify(m_arrComps,
		m_grayImg,
		m_operImg,
		m_currImg);
//	m_currImg = m_pStepVer->GetImage();

	// ok, have we got something?
	if (m_arrCands.GetCount() >= 2)
	{
		if (m_arrCands[0].x < m_arrCands[1].x)
		{
			m_leftEyeComp = *(m_arrCands[0].pComp);
			m_rightEyeComp = *(m_arrCands[1].pComp);
		}
		else
		{
			m_leftEyeComp = *(m_arrCands[1].pComp);
			m_rightEyeComp = *(m_arrCands[0].pComp);
		}
		ImgLib::DrawComponent(m_leftEyeComp, m_currImg, 4);
		ImgLib::DrawComponent(m_rightEyeComp, m_currImg, 4);
		bFound = true;
	}

	// draw all the components - looks cool :-)
	for (unsigned int i = 0; i < m_arrComps.GetCount(); i++)
		ImgLib::DrawComponent(m_arrComps[i], m_currImg, 1);
	
	// and finally let's show we've done something
	ImgLib::IntelligentCopy(m_currImg, image);

//	return false;
	return bFound;

}

CvRect BlinkDetector::GetRightEyeRect()
{
	return m_rightEyeComp.rect;
}

CvRect BlinkDetector::GetLeftEyeRect()
{
	return m_leftEyeComp.rect;
}

CvPoint BlinkDetector::GetLeftEyeCenter()
{
	CvPoint ret;
	CvRect rect = GetLeftEyeRect();
	ret.x = rect.x + (rect.width / 2);
	ret.y = rect.y + (rect.height / 2);
	return ret;
}
CvPoint BlinkDetector::GetRightEyeCenter()
{
	CvPoint ret;
	CvRect rect = GetRightEyeRect();
	ret.x = rect.x + (rect.width / 2);
	ret.y = rect.y + (rect.height / 2);
	return ret;
}
CvPoint BlinkDetector::GetCenter()
{
	CvPoint left = GetLeftEyeCenter();
	CvPoint right = GetRightEyeCenter();
	return cvPoint( (left.x + right.x) / 2, (left.y + right.y) / 2);
}