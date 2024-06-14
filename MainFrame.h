//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// MainFrame.h
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2019-2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "LeftDlg.h"
#include "ViewWnd.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CMainFrame
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CMainFrame : public CFrameWnd
{
// STATIC DATA
private:
	static const std::array<UINT, 1> indicatorArray;

// ELEMENT DATA
private:
	CStatusBar statusBar;
	CLeftBar leftBar;
	CViewWnd viewWnd;

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// OVERRIDES
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT&) final;
	virtual BOOL OnCmdMsg(UINT, int, void*, AFX_CMDHANDLERINFO*) final;

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnSetFocus(CWnd*);
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
