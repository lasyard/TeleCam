// TeleCam.h

// lasy
// 2011.11.25

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

class CTeleCamApp: public CWinAppEx
{
public:
	CTeleCamApp();
	virtual ~CTeleCamApp();

	CCamManager *m_pCamManager;

	virtual BOOL InitInstance();
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnAppAbout();
};

extern CTeleCamApp theApp;
