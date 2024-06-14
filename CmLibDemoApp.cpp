//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CmLibDemoApp.cpp
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2019-2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "pch.h"
#include "framework.h"
#include "CmLibDemoApp.h"
#include "MainFrame.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CAboutDlg
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CAboutDlg - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CAboutDlg::CAboutDlg() : 
	CDialog(IDD_ABOUT_DLG)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CAboutDlg - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCmLibDemoApp
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCmLibDemoApp - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCmLibDemoApp::CCmLibDemoApp() : 
	CWinApp()
{
	SetAppID(L"ColorModel.AppID.NoVersion");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCmLibDemoApp - OVERRIDES
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CCmLibDemoApp::InitInstance()
{
	CWinApp::InitInstance();
	CFrameWnd* p_mf = new CMainFrame;
	if (p_mf->LoadFrame(IDR_MAIN_FRAME, WS_OVERLAPPEDWINDOW))
	{
		HICON h_i = LoadIcon(IDR_MAIN_FRAME);
		p_mf->SetIcon(h_i, TRUE);
		p_mf->SetIcon(h_i, FALSE);
		p_mf->ShowWindow(SW_SHOWMAXIMIZED);
		p_mf->UpdateWindow();
		m_pMainWnd = p_mf;
		return TRUE;
	}
	return FALSE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCmLibDemoApp - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CCmLibDemoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCmLibDemoApp::OnAppAbout)
END_MESSAGE_MAP()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CCmLibDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CCmLibDemoApp theApp;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
