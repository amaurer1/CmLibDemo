//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// LeftDlg.h
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "CustomEdit.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CViewWnd;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftDlg
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CLeftDlg : public CDialog
{
// ELEMENT DATA
private:
	CListBox diagramColorModelLsb;
	CButton diagramIndex1Btn;
	CButton diagramIndex2Btn;
	CButton diagramIndex3Btn;
	TNumberEdit<int> diagramValueEdt;
	CButton contourEnabledCkb;
	CListBox contourColorModelLsb;
	CButton contourIndex1Btn;
	CButton contourIndex2Btn;
	CButton contourIndex3Btn;
	CViewWnd* p_viewWnd;

// DIALOG DATA
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_LEFT_DLG};
#endif

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CLeftDlg();

// ELEMENT FUNCTIONS
public:
	BOOL Create(CWnd*);
	void refreshDiagramValueEdt();
	void setViewWnd(CViewWnd* const p_w) {p_viewWnd = p_w;}

// OVERRIDES
public:
	virtual BOOL OnInitDialog() final;
	virtual void DoDataExchange(CDataExchange*) final;
	virtual void OnOK() final {return;}
	virtual void OnCancel() final {return;}

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnDiagramColorModelLsbSelchange();
	afx_msg void OnDiagramIndexRdbClick(UINT);
	afx_msg void OnDiagramValueEdtChange();
	afx_msg void OnContourEnabledCkbClick();
	afx_msg void OnContourColorModelLsbSelchange();
	afx_msg void OnContourIndexRdbClick(UINT);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedContourIndex1Rdb();
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftBar
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CLeftBar : public CDialogBar
{
// ELEMENT DATA
public:
	CLeftDlg leftDlg;

// DIALOG DATA
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_LEFT_BAR};
#endif

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CLeftBar();

// ELEMENT FUNCTIONS
public:
	BOOL Create(CWnd*);

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnSize(UINT, int, int);
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
