/** @file GLView.cpp
 *  Implementation of the GLView class.
 */
#include "GLView.h"
#include <glut.h>

const wxEventType wxEVT_GLVIEWCHANGED = wxNewEventType();

BEGIN_EVENT_TABLE(GLView, wxGLCanvas)
    EVT_SIZE(GLView::OnSize)
    EVT_PAINT(GLView::OnPaint)
    EVT_ERASE_BACKGROUND(GLView::OnEraseBackground)
    EVT_ENTER_WINDOW( GLView::OnEnterWindow )
	EVT_LEFT_DOWN(GLView::OnLeftMouseButtonDown)
	EVT_LEFT_UP(GLView::OnLeftMouseButtonUp)
	EVT_RIGHT_DOWN(GLView::OnRightMouseButtonDown)
	EVT_RIGHT_UP(GLView::OnRightMouseButtonUp)
	EVT_MOTION(GLView::OnMouseMove)
END_EVENT_TABLE()

GLView::GLView(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
    : wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size, style, name ),
	m_baseAlpha(30.0),
	m_baseBeta(30.0),
	m_baseScale(1.0),
	m_scale(0.0),
	m_alpha(0.0),
	m_beta(0.0)

{
    m_init = false;
    m_gllist = 0;
}

GLView::GLView(wxWindow *parent, const GLView &other,
    wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
    const wxString& name )
    : wxGLCanvas(parent, other.GetContext(), id, pos, size, style, name),
	m_baseAlpha(30.0),
	m_baseBeta(30.0),
	m_baseScale(1.0),
	m_scale(0.0),
	m_alpha(0.0),
	m_beta(0.0)
{
    m_init = false;
    m_gllist = other.m_gllist; // share display list
}

GLView::~GLView()
{
}

void GLView::Render()
{
    wxPaintDC dc(this);

#ifndef __WXMOTIF__
    if (!GetContext()) return;
#endif

    SetCurrent();
    // Init OpenGL once, but after SetCurrent
    if (!m_init)
    {
        InitGL();
        m_init = true;
    }

	glLoadIdentity();
	/* viewing transformations */
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(m_baseBeta + m_beta, 1.0f, 0.0f, 0.0f);
	glRotatef(m_baseAlpha + m_alpha, 0.0f, 1.0f, 0.0f);
	float scale = m_baseScale + m_scale;
	glScalef(scale, scale, scale);

	/* clear color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vector3f pos1 = m_model.GetPosition1();
	Vector3f pos2 = m_model.GetPosition2();
	Vector3f cam1 = m_model.GetCam1Pos();
	Vector3f cam2 = m_model.GetCam2Pos();
	DrawVersors(10);
	///
	/// tracked object 1
	///
	glPushMatrix();
	// model transformations
	glTranslatef(pos1.x, pos1.y, pos1.z);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(1.0f, 8, 8);
	glPopMatrix();
	///
	/// tracked object 2
	///
	glPushMatrix();
	// model transformations
	glTranslatef(pos2.x, pos2.y, pos2.z);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(1.0f, 8, 8);
	glPopMatrix();
	///
	/// camera1
	///
	glPushMatrix();
	glTranslatef(cam1.x, cam1.y, cam1.z);
	glColor3f(0.0f, 1.0f, 0.0f);
	DrawCube(2.0);
	glPopMatrix();
	///
	/// camera2
	///
	glPushMatrix();
	glTranslatef(cam2.x, cam2.y, cam2.z);
	glColor3f(0.0f, 1.0f, 1.0f);
	DrawCube(2.0);
	glPopMatrix();
	///
	/// declination
	///
	glColor3f(0.9, 0.6, 0.4);
	//glColor3f(1.0, 1.0, 1.0);
	Vector3f from = m_model.GetOrigin();
	Vector3f to = m_model.GetCentre();
	DrawVector(from, to);
    glFlush();
    SwapBuffers();
	SendChangedEvent(pos1, pos2);
}

void GLView::DrawCube(float side_length)
{
	static GLuint glCubeList;
	glPushMatrix();
	glScalef(side_length, side_length, side_length);

    if( !glIsList(glCubeList) )
    {
        glCubeList = glGenLists(1);

        glNewList( glCubeList, GL_COMPILE_AND_EXECUTE );
        /* draw six faces of a cube */

        glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f,-0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);

			glNormal3f( 0.0f, 0.0f,-1.0f);
			glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
			glVertex3f( 0.5f, 0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);

			glNormal3f( 0.0f, 1.0f, 0.0f);
			glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);
			glVertex3f(-0.5f, 0.5f,-0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);

			glNormal3f( 0.0f,-1.0f, 0.0f);
			glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f( 0.5f,-0.5f,-0.5f);
			glVertex3f( 0.5f,-0.5f, 0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);

			glNormal3f( 1.0f, 0.0f, 0.0f);
			glVertex3f( 0.5f, 0.5f, 0.5f); glVertex3f( 0.5f,-0.5f, 0.5f);
			glVertex3f( 0.5f,-0.5f,-0.5f); glVertex3f( 0.5f, 0.5f,-0.5f);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f,-0.5f);
        glEnd();
        glEndList();
    }
    else
    {
        glCallList(glCubeList);
    }

	glPopMatrix();


}
void GLView::DrawVersors(int units)
{
	static GLuint glVersorsList;

	GLfloat mat_emm[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat mat_emm_def[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, 
            mat_emm);

	if ( !glIsList(glVersorsList) )
	{
		glVersorsList = glGenLists(1);

        glNewList(glVersorsList, GL_COMPILE_AND_EXECUTE );
			glBegin(GL_LINES);
				///////////
				// x - axis
				///////////
				glColor3f(1.0f, 0.0f, 0.0f);
				// axis
				glNormal3f(1.0, 0.0, 0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(units * 1.0f + 0.3f, 0.0f, 0.0f);
				// arrow
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(units * 1.0f + 0.3f, 0.0f, 0.0f);
				glVertex3f(units * 1.0f + 0.1f, 0.1f, 0.0f);
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(units * 1.0f + 0.3f, 0.0f, 0.0f);
				glVertex3f(units * 1.0f + 0.1f, -0.1f, 0.0f);
				// scale
				for (int x = 1; x <= units; x++)
				{
					glVertex3f(x * 1.0f, -0.1f, -0.0f);
					glVertex3f(x * 1.0f, 0.1f, -0.0f);
				}
				///////////
				// y - axis
				///////////
				glColor3f(1.0f, 1.0f, 0.0f);
				// axis
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, units * 1.0f + 0.3f, 0.0f);
				// arrow
				glVertex3f(0.0f, units * 1.0f + 0.3f, 0.0f);
				glVertex3f(0.0f, units * 1.0f + 0.1f, 0.1f);
				glVertex3f(0.0f, units * 1.0f + 0.3f, 0.0f);
				glVertex3f(0.0f, units * 1.0f + 0.1f, -0.1f);
				// scale
				for (int y = 1; y <= units; y++)
				{
					glVertex3f(0.0f, y * 1.0f, -0.1f);
					glVertex3f(0.0f, y * 1.0f, 0.1f);
				}
				///////////
				// z - axis
				///////////
				glColor3f(0.0f, 1.0f, 1.0f);
				// axis
				glNormal3f(0.0, 0.0, -1.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, units * 1.0f + 0.3f);
				// arrow
				glVertex3f(0.0f, 0.0f, units * 1.0f + 0.3f);
				glVertex3f(0.0f, 0.1f, units * 1.0f + 0.1f);
				glVertex3f(0.0f, 0.0f, units * 1.0f + 0.3f);
				glVertex3f(0.0f, -0.1f, units * 1.0f + 0.1f);
				// scale
				for (int z = 1; z <= units; z++)
				{
					glVertex3f(0.0f, -0.1f, z * 1.0f);
					glVertex3f(0.0f, 0.1f, z * 1.0f);
				}
			glEnd();

		glEndList();
	}
	else
	{
		glCallList(glVersorsList);
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, 
            mat_emm_def);
}

void GLView::DrawVector(Vector3f from, Vector3f to)
{
	

	//glBegin(GL_LINES);
	//	glColor3f(1.0f, 0.0f, 0.0f);
	//	// axis
	//	glNormal3f(1.0, 0.0, 0.0);
	//	glVertex3f(from.x, from.y, from.z);
	//	glVertex3f(to.x, to.y, to.z);
	//	
	//glEnd();
	Vector3f len = to - from;
	float scale = sqrt(len.x * len.x + len.y * len.y + len.z * len.z);
	float xylen = sqrt(len.x * len.x + len.y * len.y);
	float alpha = atan2(len.y, len.x);
	float gamma = atan2(len.z, xylen);
	// find degrees
	alpha = (360 * alpha) / (2 * CV_PI);
	gamma = (360 * gamma) / (2 * CV_PI);
	glPushMatrix();
	glTranslatef(from.x, from.y, from.z);
	glRotatef(alpha, 0, 0, 1);
	glRotatef(-gamma, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
//	glScalef(scale, scale, scale);
	glScalef(1, 1, scale);
	glutSolidCone(2.0, 1.0, 10, 10);
	glPopMatrix();


}
void GLView::OnEnterWindow( wxMouseEvent& WXUNUSED(event) )
{
    SetFocus();
}

void GLView::OnLeftMouseButtonDown(wxMouseEvent& event)
{
	event.GetPosition(&m_iniX, &m_iniY);
	event.Skip();
}
void GLView::OnLeftMouseButtonUp(wxMouseEvent& event)
{
	m_baseAlpha += m_alpha;
	m_baseBeta += m_beta;
	m_alpha = 0.0f;
	m_beta = 0.0f;
}
void GLView::OnRightMouseButtonDown(wxMouseEvent& event)
{
	long unused;
	event.GetPosition(&unused, &m_rIniY);
	event.Skip();
}
void GLView::OnRightMouseButtonUp(wxMouseEvent& event)
{
	m_baseScale += m_scale;
	m_scale = 0.0f;
}
void GLView::OnMouseMove(wxMouseEvent& event)
{
	long x, y;
	int w, h;
	long dx, dy;
	if (event.LeftIsDown())
	{
		event.GetPosition(&x, &y);
		GetClientSize(&w, &h);
		dx = m_iniX - x;
		dy = m_iniY - y;
		m_alpha = 360.0f * ((float)dx / w);
		m_beta = 360.0f * ((float)dy / w);
	}
	if (event.RightIsDown())
	{
		event.GetPosition(&x, &y);
		GetClientSize(&w, &h);
		dy = m_rIniY - y;
		m_scale = ((float)dy / w);
	}
}
void GLView::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    Render();
}

void GLView::OnSize(wxSizeEvent& event)
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);
#ifndef __WXMOTIF__
    if (GetContext())
#endif
    {
//        SetCurrent();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
//		glFrustum(-5.0f, 5.0f, -5.0f, 5.0f, 1.0f, 20.0f);
		float left		=	-30.0f;
		float right		=	30.0f;
		float bottom	=	-30.0f;
		float top		=	30.0f;
		float near_pos	=	-200.0f;
		float far_pos	=	200.0f;
		if (w <= h) 
			glOrtho (left, right, bottom*(GLfloat)h/(GLfloat)w, 
				top*(GLfloat)h/(GLfloat)w, near_pos, far_pos);
		else 
			glOrtho (left*(GLfloat)w/(GLfloat)h, 
				right*(GLfloat)w/(GLfloat)h, bottom, top, near_pos, far_pos);
		glMatrixMode(GL_MODELVIEW);

        glViewport(0, 0, (GLint) w, (GLint) h);
    }
}

void GLView::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
  // Do nothing, to avoid flashing.
}

void GLView::InitGL()
{
    SetCurrent();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.4, 0.4, 0.4, 0.0); 
    GLfloat mat_ambient_and_diffuse[] = { 1.0, 0.2, 0.2, 1.0 };
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);

	glEnable(GL_NORMALIZE);

	GLfloat light_position[] = { 0.0f, 0.0f, 2.0f, 0.0f };
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void GLView::SendChangedEvent(Vector3f pos1, Vector3f pos2)
{
	wxCommandEvent event(wxEVT_GLVIEWCHANGED, GetId());
	event.SetEventObject(this);
	// Give it some contents

	event.SetString(wxString::Format("1:\nx = %.3f\ny = %.3f\nz = %.3f\n2:\nx = %.3f\ny = %.3f\nz = %.3f\n", pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z));
	GetEventHandler()->ProcessEvent( event );
}