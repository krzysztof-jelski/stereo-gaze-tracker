# Microsoft Developer Studio Project File - Name="OpenTracker" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OpenTracker - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenTracker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenTracker.mak" CFG="OpenTracker - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenTracker - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OpenTracker - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenTracker - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "$(WXWIN)\lib\msw" /I "$(WXWIN)\lib\vc_lib\msw" /I "$(OPENCV)\otherlibs\cvcam\include" /I "$(OPENCV)\cv\include" /I "$(OPENCV)\cxcore\include" /I "$(OPENCV)\cvaux\include" /I "$(WXWIN)\include\msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WXMSW__" /D "WXUSINGDLL" /YX"wxprec.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib winmm.lib advapi32.lib wsock32.lib cvaux.lib cv.lib cxcore.lib highgui.lib cvcam.lib wxbase26.lib wxmsw26_core.lib wxmsw26_gl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /libpath:"$(OPENCV)\lib" /libpath:"$(WXWIN)\lib\vc_dll"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "OpenTracker - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(WXWIN)\include" /I "D:\OpenCV\otherlibs\cvcam\include" /I "D:\OpenCV\cv\include" /I "D:\OpenCV\cxcore\include" /I "D:\OpenCV\cvaux\include" /I "$(WXWIN)\lib\msw" /I "$(WXWIN)\include\msvc" /I "$(WXWIN)\lib\vc_lib\msw" /I "$(OPENCV)\otherlibs\cvcam\include" /I "$(OPENCV)\cv\include" /I "$(OPENCV)\cxcore\include" /I "$(OPENCV)\cvaux\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__WXMSW__" /D "__WXDEBUG__" /FR /YX"wxprec.h" /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cvauxd.lib cvd.lib cxcored.lib highguid.lib cvcamd.lib wxbase26d.lib wxmsw26d_core.lib wxmsw26d_gl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib winmm.lib advapi32.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(OPENCV)\lib" /libpath:"$(WXWIN)\lib\vc_dll"
# SUBTRACT LINK32 /verbose

!ENDIF 

# Begin Target

# Name "OpenTracker - Win32 Release"
# Name "OpenTracker - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\3dModel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\AlgorithmsGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\src\AlgosPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\BlinkDetector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\BlinkDetectState.cpp
# End Source File
# Begin Source File

SOURCE=.\src\BTETrackState.cpp
# End Source File
# Begin Source File

SOURCE=.\src\CalibrationState.cpp
# End Source File
# Begin Source File

SOURCE=.\src\CameraInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\EyeCornersFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\EyeCornersFinderZhu.cpp
# End Source File
# Begin Source File

SOURCE=.\src\EyeTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FloatSpinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FloatSpinSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FrameDiff.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GazeTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GlobalConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GLView.cpp
# End Source File
# Begin Source File

SOURCE=.\src\HoughEllipseIrisFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ImgLib.cpp
# End Source File
# Begin Source File

SOURCE=.\src\InputController.cpp
# End Source File
# Begin Source File

SOURCE=.\src\InputControllerAbsolute.cpp
# End Source File
# Begin Source File

SOURCE=.\src\InputControllerRelative.cpp
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderFit.cpp
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderHoughCircle.cpp
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderHoughEllipse.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LandmarksFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LandmarksFinderGPF.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LandmarksFinderNull.cpp
# End Source File
# Begin Source File

SOURCE=.\src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MyTextCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\observable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\OptionPane.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ParametersGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ParamSpinSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\src\SizeData.cpp
# End Source File
# Begin Source File

SOURCE=.\src\SpinSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\src\spline.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepCheckCand.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepCheckCandKawato.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepCheckCandKawatoNoSymmetry.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepDiff.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepDiff1st.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepDiffLDD.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPrepr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprAdaptBin.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprBin.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprClean.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprCvAdaptBin.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprGray.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprHue.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprRed.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepSegmentate.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepSegmFFill.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepVerify.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StepVerKawato.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StereoCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TrackEventListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TrackRunner.cpp
# End Source File
# Begin Source File

SOURCE=.\src\WinTrackEventListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wxprec.cpp

!IF  "$(CFG)" == "OpenTracker - Win32 Release"

!ELSEIF  "$(CFG)" == "OpenTracker - Win32 Debug"

# ADD CPP /Yc"wxprec.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\3dModel.h
# End Source File
# Begin Source File

SOURCE=.\src\AlgoParameters.h
# End Source File
# Begin Source File

SOURCE=.\src\algorithmsgroup.h
# End Source File
# Begin Source File

SOURCE=.\src\AlgosPanel.h
# End Source File
# Begin Source File

SOURCE=.\src\BlinkDetector.h
# End Source File
# Begin Source File

SOURCE=.\src\BlinkDetectState.h
# End Source File
# Begin Source File

SOURCE=.\src\BTETrackState.h
# End Source File
# Begin Source File

SOURCE=.\src\CalibrationState.h
# End Source File
# Begin Source File

SOURCE=.\src\CameraInfo.h
# End Source File
# Begin Source File

SOURCE=.\src\EyeCornersFinder.h
# End Source File
# Begin Source File

SOURCE=.\src\EyeCornersFinderCanny.h
# End Source File
# Begin Source File

SOURCE=.\src\EyeCornersFinderZhu.h
# End Source File
# Begin Source File

SOURCE=.\src\EyeTracker.h
# End Source File
# Begin Source File

SOURCE=.\src\FloatSpinCtrl.h
# End Source File
# Begin Source File

SOURCE=.\src\FloatSpinSlider.h
# End Source File
# Begin Source File

SOURCE=.\src\FrameDiff.h
# End Source File
# Begin Source File

SOURCE=.\src\GazeTracker.h
# End Source File
# Begin Source File

SOURCE=.\src\GlobalConfig.h
# End Source File
# Begin Source File

SOURCE=.\src\GLView.h
# End Source File
# Begin Source File

SOURCE=.\src\HoughEllipseIrisFinder.h
# End Source File
# Begin Source File

SOURCE=.\src\ImgLib.h
# End Source File
# Begin Source File

SOURCE=.\src\InputController.h
# End Source File
# Begin Source File

SOURCE=.\src\InputControllerAbsolute.h
# End Source File
# Begin Source File

SOURCE=.\src\InputControllerRelative.h
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinder.h
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderFit.h
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderHough.h
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderHoughCircle.h
# End Source File
# Begin Source File

SOURCE=.\src\IrisFinderHoughEllipse.h
# End Source File
# Begin Source File

SOURCE=.\src\LandmarksFinder.h
# End Source File
# Begin Source File

SOURCE=.\src\LandmarksFinderGPF.h
# End Source File
# Begin Source File

SOURCE=.\src\LandmarksFinderNull.h
# End Source File
# Begin Source File

SOURCE=.\src\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\src\MyTextCtrl.h
# End Source File
# Begin Source File

SOURCE=.\src\observable.h
# End Source File
# Begin Source File

SOURCE=.\src\Observer.h
# End Source File
# Begin Source File

SOURCE=.\src\OptionPane.h
# End Source File
# Begin Source File

SOURCE=.\src\parameter.h
# End Source File
# Begin Source File

SOURCE=.\src\ParametersGroup.h
# End Source File
# Begin Source File

SOURCE=.\src\ParamSpinSlider.h
# End Source File
# Begin Source File

SOURCE=.\src\SizeData.h
# End Source File
# Begin Source File

SOURCE=.\src\SpinSlider.h
# End Source File
# Begin Source File

SOURCE=.\src\spline.H
# End Source File
# Begin Source File

SOURCE=.\src\StepCheckCand.h
# End Source File
# Begin Source File

SOURCE=.\src\StepCheckCandKawato.h
# End Source File
# Begin Source File

SOURCE=.\src\StepCheckCandKawatoNoSymmetry.h
# End Source File
# Begin Source File

SOURCE=.\src\StepDiff.h
# End Source File
# Begin Source File

SOURCE=.\src\StepDiff1st.h
# End Source File
# Begin Source File

SOURCE=.\src\StepDiffLDD.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPrepr.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprAdaptBin.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprBin.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprClean.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprCvAdaptBin.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprGray.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprHue.h
# End Source File
# Begin Source File

SOURCE=.\src\StepPreprRed.h
# End Source File
# Begin Source File

SOURCE=.\src\StepSegmentate.h
# End Source File
# Begin Source File

SOURCE=.\src\StepSegmFFill.h
# End Source File
# Begin Source File

SOURCE=.\src\StepVerify.h
# End Source File
# Begin Source File

SOURCE=.\src\StepVerKawato.h
# End Source File
# Begin Source File

SOURCE=.\src\StereoCallback.h
# End Source File
# Begin Source File

SOURCE=.\src\Timer.h
# End Source File
# Begin Source File

SOURCE=.\src\TrackerState.h
# End Source File
# Begin Source File

SOURCE=.\src\TrackEventListener.h
# End Source File
# Begin Source File

SOURCE=.\src\TrackRunner.h
# End Source File
# Begin Source File

SOURCE=.\src\WinTrackEventListener.h
# End Source File
# Begin Source File

SOURCE=.\src\wxprec.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\rc\wx\msw\blank.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\bullseye.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\cdrom.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\computer.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\cross.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\drive.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\file1.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\floppy.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\folder1.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\folder2.ico
# End Source File
# Begin Source File

SOURCE=.\rc\GazeTracker.rc
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\hand.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\magnif1.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\noentry.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\pbrush.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\pencil.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\pntleft.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\pntright.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\query.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\removble.ico
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\rightarr.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\roller.cur
# End Source File
# Begin Source File

SOURCE=.\rc\wx\msw\watch1.cur
# End Source File
# End Group
# End Target
# End Project
