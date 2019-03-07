/*	[FTEasyGL]
	OpenGLä»à’ëÄçÏÉNÉâÉX
 	1998.02.12-  F/T
*/

#include "stdafx.h"
#include <afxwin.h>
#include "FTEasyGL.h"

FTEasyGL::FTEasyGL()
{
	Init();
}

FTEasyGL::~FTEasyGL()
{
	Release();
}


void FTEasyGL::Init()
{
	m_dwFlag = GLMODE_LIGHTING;

	m_hRC = NULL;

	m_dwPFDFlag = 
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | 
		PFD_DOUBLEBUFFER |
		PFD_TYPE_RGBA;

	SetDrawWindow();
}


void FTEasyGL::SetDrawWindow( CWnd* pWnd  )
{
	if ( pWnd ) {
		m_pWndGL = pWnd;
	} else {
		m_pWndGL = CWnd::GetDesktopWindow();
	}
}


void FTEasyGL::Create( CWnd* pWnd )
{
	Release();

	if ( pWnd ) SetDrawWindow( pWnd );
	
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		m_dwPFDFlag,
		24,
		0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		32,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	CClientDC dc(m_pWndGL);
	int nPixelFormat = ChoosePixelFormat( dc.m_hDC , &pfd );
	BOOL fStat = SetPixelFormat( dc.m_hDC , nPixelFormat , &pfd );

	m_hRC = wglCreateContext( dc.m_hDC );

}

void FTEasyGL::SetWindowSize( int nX , int nY )
{
	CClientDC dc(m_pWndGL);
	wglMakeCurrent( dc.m_hDC , m_hRC );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -1.0 , 1.0 , -1.0 , 1.0 , 1.0 , 15.0 );
	glViewport(0,0,nX,nY);

	wglMakeCurrent( NULL, NULL );
}

void FTEasyGL::DrawBegin(CDC* pDC)
{
	wglMakeCurrent( pDC->m_hDC , m_hRC );
}

void FTEasyGL::DrawEnd(CDC* pDC)
{
	glFlush();
	if ( m_dwPFDFlag & PFD_DOUBLEBUFFER ) {
		SwapBuffers( pDC->m_hDC);
	}
	wglMakeCurrent( pDC->m_hDC , NULL );
}

void FTEasyGL::Draw(CDC* pDC)
{
	DrawBegin( pDC );

	// Something to Draw

	DrawEnd( pDC );
}




void FTEasyGL::Release()
{
	if ( m_hRC ) {	
		wglDeleteContext( m_hRC );
		m_hRC = NULL;
	}
}
