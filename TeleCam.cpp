// TeleCam.cpp

// lasy
// 2011.11.25

#include "stdafx.h"
#include "afxwinappex.h"

#include <list>
using namespace std;

#include <dshow.h>

#include "resource.h"

#include "Cam.h"
#include "CamManager.h"

#include "AboutDlg.h"
#include "CamView.h"
#include "OutputWnd.h"
#include "MainFrm.h"

#include "TeleCam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTeleCamApp theApp;

BEGIN_MESSAGE_MAP(CTeleCamApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CTeleCamApp::OnAppAbout)
END_MESSAGE_MAP()

CTeleCamApp::CTeleCamApp()
: CWinAppEx(TRUE)
, m_pCamManager(NULL)
{
}

CTeleCamApp::~CTeleCamApp()
{
	if (m_pCamManager != NULL) delete m_pCamManager;
}

BOOL CTeleCamApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	m_pCamManager = new CCamManager;

	if (!AfxSocketInit()) {
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	if (!AfxOleInit()) {
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("lasyard"));

	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	CMainFrame *pFrame = new CMainFrame;
	if (!pFrame) return FALSE;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);
	HINSTANCE hInst = AfxGetResourceHandle();
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

void CTeleCamApp::PreLoadState()
{
	CString strName;
	strName.LoadString(IDR_CAM_VIEW);
	GetContextMenuManager()->AddMenu(strName, IDR_CAM_VIEW);
}

void CTeleCamApp::LoadCustomState()
{
}

void CTeleCamApp::SaveCustomState()
{
}

void CTeleCamApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
