/** @file GLView.h
 *  Interface for the GLView class.
 */

#ifndef GLView_H
#define GLView_H

#include "wxprec.h"
#include "glut.h"
#include "3dModel.h"

extern const wxEventType wxEVT_GLVIEWCHANGED;

class GLView : public wxGLCanvas
{
public:
	GLView( wxWindow *parent, wxWindowID id = wxID_ANY,
	const wxPoint& pos = wxDefaultPosition,
	const wxSize& size = wxDefaultSize,
	long style = 0, const wxString& name = _T("TestGLCanvas"));

	GLView( wxWindow *parent, const GLView &other,
		wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
		const wxString& name = _T("TestGLCanvas"));

	~GLView();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnLeftMouseButtonDown(wxMouseEvent& event);
	void OnLeftMouseButtonUp(wxMouseEvent& event);
	void OnRightMouseButtonDown(wxMouseEvent& event);
	void OnRightMouseButtonUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);

	void Render();
	void InitGL();

	Model* GetModel() { return &m_model; }
protected:
	void DrawCube(float side_length);
	void DrawVersors(int units);
	void DrawVector(Vector3f from, Vector3f to);
	void SendChangedEvent(Vector3f pos1, Vector3f pos2);
protected:
	bool   m_init;
    GLuint m_gllist;
	Model m_model;
	// scaling & rotating
	float m_baseScale, m_scale;
	long m_iniX, m_iniY;
	long m_rIniY;
	float m_baseAlpha, m_baseBeta;
	float m_alpha, m_beta;

DECLARE_EVENT_TABLE()
};

#endif // ifndef GLView_H