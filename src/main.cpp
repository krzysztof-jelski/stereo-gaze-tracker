// -*- C++ -*- generated by wxGlade 0.3.5.1 on Mon Mar 07 12:36:05 2005

#include "wxprec.h"
#include "MainFrame.h"
#include "GlobalConfig.h"
#include "StereoCallback.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class GazeTrackerApp: public wxApp {
public:
    bool OnInit();
	virtual int OnExit();
protected:
	wxLogNull noLog;
};

IMPLEMENT_APP(GazeTrackerApp)

bool GazeTrackerApp::OnInit()
{
//	wxLog::SetTraceMask(wxTraceMemAlloc);
//	wxLog::SetLogLevel(wxLOG_Trace);
//_CrtSetBreakAlloc(3730);
	wxToolTip::Enable(true);
	wxToolTip::SetDelay(300);
	wxBitmap bitmap;
	wxSplashScreen* splash = NULL;
	if (bitmap.LoadFile("..\\ico\\splashscreen.bmp", wxBITMAP_TYPE_ANY))
	{
		splash = new wxSplashScreen(bitmap,
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT,
          0, NULL, -1);
	}
	GlobalConfig& config = GlobalConfig::GetInstance();
	config.Read("default.conf");
	GazeTracker::Create();
	wxInitAllImageHandlers();
	MainFrame* mainFrame = new MainFrame(0, -1, "");
	SetTopWindow(mainFrame);
	if (splash != NULL)
		splash->Destroy();
	mainFrame->Show();

	return true;
}


int GazeTrackerApp::OnExit()
{
	StereoCallback::Destroy();
	GlobalConfig::Destroy();
	return true;
}