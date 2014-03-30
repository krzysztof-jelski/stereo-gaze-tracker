// -*- C++ -*- generated by wxGlade 0.3.5.1 on Fri Mar 18 17:43:25 2005
#include "wxprec.h"
#include "MainFrame.h"
#include "GlobalConfig.h"
#include "GazeTracker.h"
#include "CalibrationState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TOGGLEBUTTON (wxID_OPTIONS, MainFrame::OnOptionsToggle)
	EVT_BUTTON (wxID_CALIB, MainFrame::OnCalibrate)
	EVT_MENU (wxID_EXIT, MainFrame::OnExit)
	EVT_CLOSE (MainFrame::OnClose)
	EVT_TOOL (wxID_CAM1PROP, MainFrame::OnCam1Prop)
	EVT_TOOL (wxID_CAM2PROP, MainFrame::OnCam2Prop)
	EVT_TOOL (wxID_RES, MainFrame::OnRes)
	EVT_TOOL (wxID_LOAD, MainFrame::OnLoad)
	EVT_TOOL (wxID_SAVE, MainFrame::OnSave)
	EVT_TOOL (wxID_LOG, MainFrame::OnLogToggle)
	EVT_COMMAND (-1, wxEVT_GLVIEWCHANGED, MainFrame::OnGLChanged)
	EVT_SHOW (MainFrame::OnShow)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE),
	m_mainSizer(NULL),
	m_glCanvas(NULL)
{
	m_pTrackRunner = new TrackRunner();

	///////////////////////////////////////////////////////////////////////////
	// main panels
	///////////////////////////////////////////////////////////////////////////
	m_mainPanel = new wxPanel(this, -1);
	m_options = new wxNotebook(m_mainPanel, -1, wxDefaultPosition, wxDefaultSize, /*0 */wxNB_BOTTOM);
	m_prefs = new wxNotebook(m_options, -1, wxDefaultPosition, wxDefaultSize, 0);
	m_fpsTextCtrl = new wxTextCtrl(m_mainPanel, -1, "");
	///////////////////////////////////////////////////////////////////////////
	// menu bar
	///////////////////////////////////////////////////////////////////////////
    m_menubar = new wxMenuBar();
    SetMenuBar(m_menubar);
    wxMenu* File = new wxMenu();
	File->Append(wxID_EXIT, _("Exit"), _("Exit Application"), wxITEM_NORMAL);
	wxMenu* Help = new wxMenu();
	Help->Append(wxID_ABOUT, _("About"), _("Show application information"), wxITEM_NORMAL);
    m_menubar->Append(File, _("File"));
	m_menubar->Append(Help, _("Help"));

	///////////////////////////////////////////////////////////////////////////
	// status bar
	///////////////////////////////////////////////////////////////////////////
    m_statusbar = CreateStatusBar(2, 0);

	///////////////////////////////////////////////////////////////////////////
	// toolbar
	///////////////////////////////////////////////////////////////////////////
    m_mainToolbar = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_NODIVIDER);
    SetToolBar(m_mainToolbar);
    m_mainToolbar->SetToolBitmapSize(wxSize(16, 15));
    m_mainToolbar->SetToolPacking(1);
    m_mainToolbar->SetToolSeparation(5);
	m_mainToolbar->AddTool(wxID_LOAD, _("Load config"), wxBitmap(wxT("../ico/open.xpm"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, _("Load configuration file"), _("Load configuration file"));
	m_mainToolbar->AddTool(wxID_SAVE, _("Save config"), wxBitmap(wxT("../ico/save.xpm"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, _("Save current configuration"), _("Save current configuration"));
	m_mainToolbar->AddSeparator();
    m_mainToolbar->AddTool(wxID_CAM1PROP, _("Camera 1 Properties"), wxBitmap(wxT("../ico/cam1.xpm"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, _("Cam. 1 property page"), _("Change camera 1 properties"));
    m_mainToolbar->AddTool(wxID_CAM2PROP, _("Camera 2 Properties"), wxBitmap(wxT("../ico/cam2.xpm"), wxBITMAP_TYPE_ANY), wxNullBitmap,  wxITEM_NORMAL, _("Cam. 2 property page"), _("Change camera 2 properties"));
	m_mainToolbar->AddTool(wxID_RES, _("Change resolution"), wxBitmap(wxT("../ico/bda.bmp"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, _("Change resolution"), _("Change cameras resolution"));
	m_mainToolbar->AddTool(wxID_LOG, _("Choose devices"), wxBitmap(wxT("../ico/input.xpm"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, _("Choose devices"), _("Show device selection dialog"));
//	m_mainToolbar->AddCheckTool(wxID_PREFS, _("Show preferences"), wxBitmap(wxT("../ico/help.xpm"), wxBITMAP_TYPE_ANY), wxNullBitmap, _("Show preferences panel"), _("Show preferences panel"));
	
    m_mainToolbar->Realize();

	///////////////////////////////////////////////////////////////////////////
	// camera windows
	///////////////////////////////////////////////////////////////////////////
    m_leftCameraView = new wxPanel(m_mainPanel, -1);
    m_rightCameraView = new wxPanel(m_mainPanel, -1);

	///////////////////////////////////////////////////////////////////////////
	// parameters
	///////////////////////////////////////////////////////////////////////////
   	m_panes.Add(new OptionPane(GlobalConfig::GetInstance()["Eye"], m_prefs, -1));
   	m_panes.Add(new OptionPane(GlobalConfig::GetInstance()["Preprocessing"], m_prefs, -1));
   	m_panes.Add(new OptionPane(GlobalConfig::GetInstance()["EyePair"], m_prefs, -1));
	m_panes.Add(new OptionPane(GlobalConfig::GetInstance()["Tracking"], m_prefs, -1));
	m_panes.Add(new OptionPane(GlobalConfig::GetInstance()["Features"], m_prefs, -1));
	m_panes.Add(new OptionPane(GlobalConfig::GetInstance()["Mouse"], m_prefs, -1));

	///////////////////////////////////////////////////////////////////////////
	// algos
	///////////////////////////////////////////////////////////////////////////
	m_algosPanel = new AlgosPanel(m_pTrackRunner, m_options, -1);
	m_algosPanel->AddObserver(this);
	///////////////////////////////////////////////////////////////////////////
	// opengl window
	///////////////////////////////////////////////////////////////////////////
	int attribList[5] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 32, 0};
	m_glCanvas = new GLView(m_mainPanel, -1, wxDefaultPosition, wxSize(200, 240), 0, "GLCanvas");
	m_pos3dTextCtrl = new wxTextCtrl(m_mainPanel,
		-1,
		"",
		wxDefaultPosition,
		wxDefaultSize,
		wxTE_MULTILINE | wxTE_READONLY);
	///////////////////////////////////////////////////////////////////////////
	// buttons
	///////////////////////////////////////////////////////////////////////////
    m_tglbtnOptions = new wxToggleButton(m_mainPanel, wxID_OPTIONS, _("Options>>"));
	m_tglbtnOptions->SetValue(false);
	m_btnCalibrate = new wxButton(m_mainPanel, wxID_CALIB, _("Calibrate"));

	///////////////////////////////////////////////////////////////////////////
	// initialize
	///////////////////////////////////////////////////////////////////////////
    set_properties();
    do_layout();

	InitTracker();

	//m_glCanvas->SetCurrent();
	///////////////////////////////////////////////////////////////////////////
	// cleanup
	///////////////////////////////////////////////////////////////////////////

}

MainFrame::~MainFrame()
{
	if (m_pTrackRunner != NULL)
		delete m_pTrackRunner;

}
void MainFrame::set_properties()
{
    // begin wxGlade: MainFrame::set_properties
    SetTitle(_("Open Tracker"));
//    SetSize(wxSize(828, 642));
    int m_statusbar_widths[] = { -1, 100 };
    m_statusbar->SetStatusWidths(2, m_statusbar_widths);
    const wxString m_statusbar_fields[] = {
        _("Welcome to Open Tracker Application!"),
        wxT("")
    };
    for(int i = 0; i < m_statusbar->GetFieldsCount(); ++i) {
        m_statusbar->SetStatusText(m_statusbar_fields[i], i);
    }
    m_leftCameraView->SetSize(m_pTrackRunner->GetMinSize());
	m_leftCameraView->SetMinSize(m_pTrackRunner->GetMinSize());
//    m_leftCameraView->SetBackgroundColour(wxColour(58, 148, 255));
    m_rightCameraView->SetSize(m_pTrackRunner->GetMinSize());
	m_rightCameraView->SetMinSize(m_pTrackRunner->GetMinSize());
//    m_rightCameraView->SetBackgroundColour(wxColour(204, 50, 50));
//    m_prefs->SetSize(wxSize(200, -1));
//	m_prefs->SetSizeHints(
//		wxSize(200, 20),
//		wxSize(600, 1000));
	//m_options->SetSize(wxSize(200, -1));
	m_options->SetMinSize(wxSize(350, -1));
	m_fpsTextCtrl->SetSize(wxSize(40, -1));
	//m_options->SetSizeHints(
	//	wxSize(350, -1),
	//	wxSize(350, -1));
	//wxSize size = m_pTrackRunner->GetMinSize();
	//m_leftCameraView->SetSizeHints(
	//	size,
	//	wxSize(640, 480));
	//m_rightCameraView->SetSizeHints(
	//	size,
	//	wxSize(640, 480));

	//m_glCanvas->SetSizeHints(wxSize(200, 240),
	//	wxSize(400,480)
	//	);
	m_pos3dTextCtrl->SetMinSize(wxSize(50,50));
    // end wxGlade
}


void MainFrame::do_layout()
{
    // begin wxGlade: MainFrame::do_layout
	m_frameSizer = new wxBoxSizer(wxHORIZONTAL);
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
	m_middleSizer = new wxBoxSizer(wxVERTICAL);
	m_camWindowsSizer = new wxBoxSizer(wxHORIZONTAL);
	m_buttonsPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_trackResultsSizer = new wxBoxSizer(wxHORIZONTAL);
		
	// notebooks
	for (unsigned int i = 0; i < m_panes.GetCount(); i++)
	    m_prefs->AddPage(m_panes.Item(i), m_panes.Item(i)->GetName());
	m_options->AddPage(m_prefs, "Parameters");
	m_options->AddPage(m_algosPanel, "Algorithms");

	//////////////////
	// camera windows
	//////////////////
	m_camWindowsSizer->Add(m_leftCameraView,
		0,
		wxFIXED_MINSIZE | wxALL,
		1);
	m_camWindowsSizer->Add(m_rightCameraView,
		0,
		wxFIXED_MINSIZE | wxALL,
		1);
	//////////////////
	// buttons
	//////////////////
	m_buttonsPanelSizer->Add(m_btnCalibrate,
		0,
		wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE);
	m_buttonsPanelSizer->Add(m_tglbtnOptions,
		0,
		wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE);
	// and a small text ctrl ;-)
	m_buttonsPanelSizer->Add(new wxStaticText(m_mainPanel, -1, "FPS:"),
		0,
		wxALIGN_CENTER_VERTICAL | wxFIXED_MINSIZE | wxLEFT | wxRIGHT,
		5);
	m_buttonsPanelSizer->Add(m_fpsTextCtrl,
		0,
		wxFIXED_MINSIZE);
	//////////////////
	// track results
	//////////////////
	m_trackResultsSizer->Add(m_glCanvas,
		3,
		wxEXPAND | wxALL,
		8);
	m_trackResultsSizer->Add(m_pos3dTextCtrl,
		1,
		wxEXPAND | wxALL,
		2);
	// sizers

	m_middleSizer->Add(m_camWindowsSizer,
		0,
		wxALL,
		1);
	m_middleSizer->Add(m_buttonsPanelSizer,
		0,
		wxALL,
		1);
	m_middleSizer->Add(m_trackResultsSizer,
		1,
		wxALL | wxEXPAND,
		1);

	m_mainSizer->Add(m_middleSizer, 2, wxEXPAND | wxALL, 3);
	m_mainSizer->Add(m_options, 0, wxEXPAND);
	m_mainSizer->Show(m_options, m_tglbtnOptions->GetValue());

	m_mainPanel->SetAutoLayout(true);
	m_mainPanel->SetSizerAndFit(m_mainSizer);
	m_mainSizer->SetSizeHints(m_mainPanel);
	
	m_frameSizer->Add(m_mainPanel, 1, wxEXPAND);


	SetAutoLayout(true);
	SetSizerAndFit(m_frameSizer);
	m_frameSizer->SetSizeHints(this);
	Layout();
//	UpdateLayout();

}

void MainFrame::InitTracker()
{
//	m_pTrackRunner->Run(m_leftCameraView, m_rightCameraView);
	GazeTracker::GetInstance()->SetGLWindow(m_glCanvas);
	GazeTracker::GetInstance()->AddObserver(this);
//	for (unsigned int i = 0; i < m_panes.GetCount(); i++)
//		m_panes[i]->Populate();

}

void MainFrame::OnShow(wxShowEvent& event)
{
	if (m_pTrackRunner->isRunning())
		return;
	m_pTrackRunner->Run(m_leftCameraView, m_rightCameraView);
}

void MainFrame::OnOptionsToggle(wxCommandEvent& event)
{
	m_mainSizer->Show(m_options, event.IsChecked());
	UpdateLayout();
}
void MainFrame::OnLogToggle(wxCommandEvent& event)
{
	
}

void MainFrame::OnCalibrate(wxCommandEvent& event)
{
	GazeTracker::GetInstance()->ChangeState(CalibrationState::GetInstance());
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnClose(wxCloseEvent& event)
{
	wxLogNull nolog;
	m_pTrackRunner->Stop();
	CalibrationState::Destroy();
	Destroy();
}
void MainFrame::OnCam1Prop(wxCommandEvent& event)
{
	m_pTrackRunner->ShowCam1Prop();
}
void MainFrame::OnCam2Prop(wxCommandEvent& event)
{
	m_pTrackRunner->ShowCam2Prop();
}
void MainFrame::OnRes(wxCommandEvent& event)
{
	wxLogNull nolog;
	m_pTrackRunner->ChangeRes();
	UpdateCameraWindows();
}

void MainFrame::OnLoad(wxCommandEvent& event)
{
	wxLogNull nolog;
	wxFileDialog *loadDialog
		= new wxFileDialog(this, "Open", "", "", "Config files (*.conf)|*.conf|All files|*.*", wxFD_OPEN | wxFD_CHANGE_DIR);
	if (loadDialog->ShowModal() == wxID_OK)
	{
		m_pTrackRunner->Pause();
		GlobalConfig::GetInstance().Read(loadDialog->GetPath());
		GazeTracker::Reinitialize();
		m_pTrackRunner->ApplyResFromConfig();
		UpdateCameraWindows();
		UpdatePanes();
		m_algosPanel->Update();
		m_pTrackRunner->Resume();
		UpdateLayout();
	}
	loadDialog->Destroy();
}

void MainFrame::OnSave(wxCommandEvent& event)
{
	wxLogNull nolog;
	wxFileDialog *saveDialog
		= new wxFileDialog(this, "Save as", "", "", "Config files (*.conf)|*.conf|All files|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	if (saveDialog->ShowModal() == wxID_OK)
	{
		GlobalConfig::GetInstance().Write(saveDialog->GetPath());
	}
	saveDialog->Destroy();
}

void MainFrame::OnGLChanged(wxCommandEvent& event)
{
	m_pos3dTextCtrl->SetValue(event.GetString());
}



void MainFrame::UpdatePanes()
{
	for (unsigned int i = 0; i < m_panes.GetCount(); i++)
		m_panes[i]->Update();

}

void MainFrame::Update(Observable *observable)
{
	// gaze tracker is notifying
	if (observable == GazeTracker::GetInstance())
	{
		float fps = GazeTracker::GetInstance()->GetFPS();
		m_fpsTextCtrl->SetValue(wxString::Format("%.2f", fps));
	}
	else // algospanel notifying
	{
		wxLogNull nolog;
		m_pTrackRunner->Pause();
		GlobalConfig::GetInstance().DeactivateParameters();
		GazeTracker::Reinitialize();
		UpdatePanes();
		UpdateLayout();
		m_pTrackRunner->Resume();
	}
	
}

void MainFrame::UpdateCameraWindows()
{
	wxSize size = m_pTrackRunner->GetMinSize();
	m_leftCameraView->SetSize(size);
	m_rightCameraView->SetSize(size);
	m_leftCameraView->SetMinSize(size);
	m_rightCameraView->SetMinSize(size);
	UpdateLayout();
}

void MainFrame::UpdateLayout()
{
	m_mainSizer->Layout();
	m_options->Layout();
	m_mainSizer->SetSizeHints(this);
	m_frameSizer->Fit(this);
	Layout();
}