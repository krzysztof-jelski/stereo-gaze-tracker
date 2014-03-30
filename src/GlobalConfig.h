/** @file GlobalConfig.h
 *  Interface for the GlobalConfig class.
 */

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include "wxprec.h"
#include "ParametersGroup.h"
#include "AlgorithmsGroup.h"
#include "CameraInfo.h"

typedef ParametersGroup* ParametersGroupPtr;

class GlobalConfig
{
protected:
	GlobalConfig();
public:
	virtual ~GlobalConfig();
	static GlobalConfig& GetInstance();
	static void Create();
	static void Destroy();

	ParametersGroupPtr& operator[](wxString key);
	const wxString& GetAlgoName(const wxString& groupName) const;
	AlgorithmsGroup* GetAlgoGroup(const wxString& groupName) const;
	wxArrayString GetAlgosGroupsNames() const;
	int Read(const wxString& fileName);
	int Write();
	int Write(const wxString& fileName);
	void DeactivateParameters();
	Cv3dTrackerCameraIntrinsics& GetCam1Intrinsics();
	Cv3dTrackerCameraIntrinsics& GetCam2Intrinsics();
	Cv3dTrackerCameraInfo * GetCam1Extrinsics();
	Cv3dTrackerCameraInfo * GetCam2Extrinsics();
	void SaveCamExtrinsics(int camNum, const Cv3dTrackerCameraInfo &camInfo);
	bool LoadCamExtrinsics(int camNum, Cv3dTrackerCameraInfo &camInfo);
	SizeData * GetSizeData();
	bool AreExtrValid() { return m_extrValid; }
	WX_DECLARE_STRING_HASH_MAP(ParametersGroup*, GroupHash);
	WX_DECLARE_STRING_HASH_MAP(AlgorithmsGroup*, AlgoHash);
protected:
	void CleanUp();
	int PrepareConfig();
	void CreateParameters(const wxString& groupName);
	void CreateAlgorithms();
	void CreateIntrinsics();
	void CreateExtrinsics();
	void CreateParameter(const wxString& groupName,
								   const wxString& paramName,
								   const wxString& type,
								   const wxString& value,
								   const wxString& min,
								   const wxString& max,
								   const wxString& percValue,
								   const wxString& percType,
								   const wxString& step,
								   const wxString& info);

	static GlobalConfig* pInstance;
	bool m_extrValid;
	GroupHash groupHash;
	AlgoHash algoHash;
	wxFileConfig* m_pFileConfig;
	wxString m_Empty;
	SizeData m_SizeData;
	CameraInfo m_camIntr[2];
	Cv3dTrackerCameraInfo m_camExtr[2];
};

#endif // ifndef GLOBALCONFIG_H