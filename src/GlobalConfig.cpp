#include "wxprec.h"
#include "GlobalConfig.h"
#include "Parameter.h"
#include "GazeTracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GlobalConfig* GlobalConfig::pInstance = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GlobalConfig::GlobalConfig() :
	m_pFileConfig(NULL),
	m_extrValid(false)
{
	
}

GlobalConfig::~GlobalConfig()
{
	CleanUp();
}

void GlobalConfig::Destroy()
{
	if (pInstance != NULL)
	{
		delete pInstance;
		pInstance = NULL;
	}
}
GlobalConfig& GlobalConfig::GetInstance()
{
	if (pInstance == 0)
		Create();
	return *pInstance;
}
void GlobalConfig::Create()
{
	pInstance = new GlobalConfig();
}

ParametersGroupPtr& GlobalConfig::operator[](wxString key)
{
	if (groupHash.find(key) == groupHash.end())
		wxFAIL_MSG("Not found");
	return groupHash[key];
}

const wxString& GlobalConfig::GetAlgoName(const wxString& groupName) const
{
	AlgoHash::const_iterator i = algoHash.find(groupName);
	if (i != algoHash.end())
		return (i->second)->GetSelected();
	else
		return m_Empty;
}

SizeData * GlobalConfig::GetSizeData()
{
	return &m_SizeData;
}

int GlobalConfig::Read(const wxString& fileName)
{
	if ( !wxFileExists(fileName) )
		return -1;
	wxFileInputStream fileStream(fileName);

	CleanUp();

	m_pFileConfig = new wxFileConfig(fileStream);

	// enumeration variables
	wxString groupName, paramName, entryName;
	long dummy1;
	bool bMoreGroups;
	
	CreateAlgorithms();
	CreateIntrinsics();
	CreateExtrinsics();
	
	// enumerate all user groups
	m_pFileConfig->SetPath("/UserParameters");
	bMoreGroups = m_pFileConfig->GetFirstGroup(groupName, dummy1);
	while ( bMoreGroups )
	{
		m_pFileConfig->SetPath("/UserParameters/" + groupName);
		CreateParameters(groupName);

		m_pFileConfig->SetPath("/UserParameters");
		bMoreGroups = m_pFileConfig->GetNextGroup(groupName, dummy1);
	}
	m_pFileConfig->SetPath("/");
	return 1;
}
int GlobalConfig::Write()
{
	return 1;
}
int GlobalConfig::Write(const wxString& fileName)
{
	wxFileOutputStream fileStream(fileName);

	PrepareConfig();
	m_pFileConfig->Save(fileStream);
	return 1;
}
int GlobalConfig::PrepareConfig()
{
	if (m_pFileConfig == NULL)
		m_pFileConfig = new wxFileConfig();

	double d; long l;
	ParametersGroup* pg;
	Parameter* parameter;
	// values retrieved from config in memory
	wxString key;
	// param value to be written in config file
	wxString paramVal;
	// let's iterate through all param groups
	GroupHash::iterator i = groupHash.begin();
	while (i != groupHash.end())
	{
		// every group will be stored in another "directory"
		m_pFileConfig->SetPath("/UserParameters/" + i->first);
		pg = i->second;
		while (pg->HasNext() )
		{
			pg->GetNext(parameter, key);
			// set path to parameter
			m_pFileConfig->SetPath("/UserParameters/" + i->first + "/" + parameter->GetName());
			if (parameter->IsPercentModification())
			{
				m_pFileConfig->DeleteEntry("value");
				m_pFileConfig->Write("percValue", parameter->GetPercValue());
			}
			else
			{
				m_pFileConfig->DeleteEntry("percValue");
				if (parameter->GetType() == Parameter::LONG)
				{
					l = *(long *)parameter->GetValue();
					m_pFileConfig->Write("value", l);
				}
				else
				{
					d = *(double *)parameter->GetValue();
					m_pFileConfig->Write("value", d);
				}
			}
		}
		i++;

	}
	
	AlgoHash::iterator j = algoHash.begin();
	while (j != algoHash.end())
	{
		m_pFileConfig->SetPath("/Algorithms/" + j->first);
		m_pFileConfig->Write("selected", j->second->GetSelected());
		j++;
	}
	m_pFileConfig->SetPath("/");
	return 1;
}

void GlobalConfig::CreateParameter(const wxString& groupName,
								   const wxString& paramName,
								   const wxString& type,
								   const wxString& value,
								   const wxString& min,
								   const wxString& max,
								   const wxString& percValue,
								   const wxString& percType,
								   const wxString& step,
								   const wxString& info)
{
	ParameterPtr pParam;
	double temp;

	if (type.IsEmpty())
		return;
	if (type.IsSameAs("double"))
		pParam = new DoubleParameter();
	else if (type.IsSameAs("long"))
		pParam = new LongParameter();
	else
		wxFAIL_MSG("Unknown parameter type");

	pParam->SetActive(false);
	pParam->SetName(paramName);
	pParam->SetInfo(info);
	pParam->SetSizeData(GetSizeData());
	pParam->SetPercType(percType);
	
	pParam->SetValue(value);
	pParam->SetMin(min);
	pParam->SetMax(max);
	pParam->SetStep(step);
	if (percValue.ToDouble(&temp))
		pParam->SetPercValue(temp);


	(*this)[groupName]->AddParam(pParam);
}


void GlobalConfig::CreateParameters(const wxString& groupName)
{
	long dummy2, dummy3;
	bool bMoreParams, bMoreEntries;
	wxString val, temp;
	wxString paramName, entryName;

	wxString type, value, min, max, percType, percValue, step, info;

	// we are in a parameters group
	// create group if needed
	if (groupHash.find(groupName) == groupHash.end())
	{
		GroupHash::value_type t(groupName, new ParametersGroup(groupName));
		groupHash.insert(t);
	}
	// enum all params inside
	bMoreParams = m_pFileConfig->GetFirstGroup(paramName, dummy3);
	while (bMoreParams)
	{
		m_pFileConfig->SetPath("/UserParameters/" + groupName + "/" + paramName);
		bMoreEntries = m_pFileConfig->GetFirstEntry(entryName, dummy2);
		// param starts
		type = value = min = max = percType = percValue = step = info = "";
		while ( bMoreEntries )
		{
			m_pFileConfig->Read(entryName, &val);
			if (entryName.IsSameAs("type"))
			{
				type = val;
			}
			else if (entryName.IsSameAs("value"))
			{
				value = val;
			}
			else if (entryName.IsSameAs("min"))
			{
				min = val;
			}
			else if (entryName.IsSameAs("max"))
			{
				max = val;
			}
			else if (entryName.IsSameAs("percType"))
			{
				percType = val;
			}
			else if (entryName.IsSameAs("percValue"))
			{
				percValue = val;
			}
			else if (entryName.IsSameAs("step"))
			{
				step = val;
			}
			else if (entryName.IsSameAs("info"))
			{
				info = val;
			}

			bMoreEntries = m_pFileConfig->GetNextEntry(entryName, dummy2);
		}
		// parameter info ends
		CreateParameter(groupName,
			paramName,
			type,
			value,
			min,
			max,
			percValue,
			percType,
			step,
			info);
		m_pFileConfig->SetPath("/UserParameters/" + groupName);
		bMoreParams = m_pFileConfig->GetNextGroup(paramName, dummy3);
	}
}

void GlobalConfig::CreateAlgorithms()
{
	wxString stepName;
	bool bMoreSteps;
	long dummy3;
	wxString available, selected;
	wxString algoName;
	
	m_pFileConfig->SetPath("/Algorithms");
	// enum all steps
	bMoreSteps = m_pFileConfig->GetFirstGroup(stepName, dummy3);
	while (bMoreSteps)
	{
		m_pFileConfig->SetPath("/Algorithms/" + stepName);
		AlgorithmsGroup * group = new AlgorithmsGroup(stepName);
		m_pFileConfig->Read("available", &available);
		m_pFileConfig->Read("selected", &selected);
		
		do
		{
			algoName = available.BeforeFirst(' ');
			available = available.AfterFirst(' ');
			group->AddAvailable(algoName);
		} while (!available.IsEmpty());

 		group->SetSelected(selected);
		algoHash[stepName] = group;
		m_pFileConfig->SetPath("/Algorithms");
		bMoreSteps = m_pFileConfig->GetNextGroup(stepName, dummy3);
	}
	m_pFileConfig->SetPath("/");
}

void GlobalConfig::CleanUp()
{
	GroupHash::iterator i = groupHash.begin();
	while (i != groupHash.end())
	{
		delete i->second;
		i++;
	}
	groupHash.clear();
	AlgoHash::iterator j = algoHash.begin();
	while (j != algoHash.end())
	{
		delete j->second;
		j++;
	}
	algoHash.clear();
	if (m_pFileConfig != NULL)
	{
		delete m_pFileConfig;
		m_pFileConfig = NULL;
	}

}

wxArrayString GlobalConfig::GetAlgosGroupsNames() const
{
	wxArrayString names;

	AlgoHash::const_iterator i = algoHash.begin();
	while (i != algoHash.end())
	{
		names.Add(i->first);
		i++;
	}
	return names;
}

AlgorithmsGroup* GlobalConfig::GetAlgoGroup(const wxString& groupName) const
{
	AlgoHash::const_iterator i = algoHash.find(groupName);
	if (i != algoHash.end())
		return i->second;
	else
		return NULL;
}

void GlobalConfig::DeactivateParameters()
{
	Parameter *p;
	GroupHash::iterator i = groupHash.begin();
	while (i != groupHash.end())
	{
		while (i->second->HasNext())
		{
			i->second->GetNext(p);
			p->SetActive(false);
		}
		i++;
	}
}

void GlobalConfig::CreateIntrinsics()
{
	wxString camIntrFile1, camIntrFile2;
	long width, height;
	m_pFileConfig->SetPath("/CameraCalibration");
	m_pFileConfig->Read("camIntrFile1", &camIntrFile1);
	m_pFileConfig->Read("camIntrFile2", &camIntrFile2);
	m_pFileConfig->Read("camIntrResW", &width);
	m_pFileConfig->Read("camIntrResH", &height);
	m_camIntr[0].Create(width, height, GetSizeData());
	m_camIntr[1].Create(width, height, GetSizeData());
	int ret1 = m_camIntr[0].Read(camIntrFile1.c_str());
	int ret2 = m_camIntr[1].Read(camIntrFile2.c_str());
	if ((ret1 < 0) || (ret2 < 0))
		wxFAIL_MSG("Error reading camera intrinsics");
	m_pFileConfig->SetPath("/");
}

void GlobalConfig::CreateExtrinsics()
{
	bool ok1 = LoadCamExtrinsics(0, m_camExtr[0]);
	bool ok2 = LoadCamExtrinsics(1, m_camExtr[1]);
	if (ok1 && ok2)
		m_extrValid = true;
	else
		m_extrValid = false;
}
Cv3dTrackerCameraIntrinsics& GlobalConfig::GetCam1Intrinsics()
{
	return m_camIntr[0].Get();
}

Cv3dTrackerCameraIntrinsics& GlobalConfig::GetCam2Intrinsics()
{
	return m_camIntr[1].Get();
}

void GlobalConfig::SaveCamExtrinsics(int camNum, const Cv3dTrackerCameraInfo &camInfo)
{
	if (camNum > 1)
		return;
	wxString matrixString, tempString, paramString;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			tempString.Printf("%.3g ", camInfo.mat[i][j]);
			matrixString.Append(tempString);
		}
	paramString.Printf("camExtrMatrix%d", camNum);
	m_pFileConfig->Write("CameraCalibration/" + paramString, matrixString);
	m_extrValid = true;
}
bool GlobalConfig::LoadCamExtrinsics(int camNum, Cv3dTrackerCameraInfo &camInfo)
{
	double value;
	bool bConv;
	if (camNum > 1)
		return false;
	wxString matrixString;
	m_pFileConfig->Read(wxString::Format("CameraCalibration/camExtrMatrix%d", camNum), &matrixString);
	wxStringTokenizer tkz(matrixString, wxT(" "));
	if (tkz.CountTokens() < 16)
		return false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			bConv = tkz.GetNextToken().ToDouble(&value);
			if (!bConv) return false;
			camInfo.mat[i][j] = value;
		}
	camInfo.principal_point = m_camIntr[camNum].Get().principal_point;
	camInfo.valid = 1;
	return true;
}

Cv3dTrackerCameraInfo * GlobalConfig::GetCam1Extrinsics()
{
	return &m_camExtr[0];
}
Cv3dTrackerCameraInfo * GlobalConfig::GetCam2Extrinsics()
{
	return &m_camExtr[1];
}