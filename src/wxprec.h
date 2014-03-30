#ifndef WXPREC_H
#define WXPREC_H

#include <wx/wxprec.h>
// additional headers
#include <wx/image.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/dynarray.h>
#include <wx/confbase.h>
#include <wx/fileconf.h>
#include <wx/stream.h>
#include <wx/wfstream.h>
#include <wx/regex.h>
#include <wx/glcanvas.h>
#include <wx/tglbtn.h>
#include <wx/notebook.h>
#include <wx/tooltip.h>
#include <wx/tokenzr.h>
#include <wx/timer.h>
#include <wx/splash.h>

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif


#ifdef __BORLANDC__
     #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#endif // ifndef WXPREC_H