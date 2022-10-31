//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// LeftDlg.cpp
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2022 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "pch.h"
#include "framework.h"
#include "LeftDlg.h"
#include "ViewWnd.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftDlg
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftDlg - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CLeftDlg::CLeftDlg() : 
	CDialog(), 
	diagramColorModelLsb(), 
	diagramIndex1Btn(), 
	diagramIndex2Btn(), 
	diagramIndex3Btn(), 
	diagramValueEdt(0, 255, 16, 8), 
	contourEnabledCkb(), 
	contourColorModelLsb(), 
	contourIndex1Btn(), 
	contourIndex2Btn(), 
	contourIndex3Btn(), 
	p_viewWnd(nullptr)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftDlg - ELEMENT FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CLeftDlg::Create(CWnd* p_pw)
{
	return CDialog::Create(IDD_LEFT_DLG, p_pw);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::refreshDiagramValueEdt()
{
	const double v = p_viewWnd->getDiagramValue();
	switch (p_viewWnd->getDiagramIndex())
	{
		case 0:
		{
			if (p_viewWnd->getDiagramColorModel() == ColorModel::rgb)
			{
				diagramValueEdt.setLimits(0, 255);
				diagramValueEdt.setIncrements(16, 8);
				diagramValueEdt.setNumber(ama::round(v * 255.0));
			}
			else
			{
				diagramValueEdt.setLimits(0, 360);
				diagramValueEdt.setIncrements(15, 5);
				diagramValueEdt.setNumber(ama::round(v * 360.0));
			}
			break;
		}
		case 1:
		{
			if (p_viewWnd->getDiagramColorModel() == ColorModel::rgb)
			{
				diagramValueEdt.setLimits(0, 255);
				diagramValueEdt.setIncrements(16, 8);
				diagramValueEdt.setNumber(ama::round(v * 255.0));
			}
			else
			{
				diagramValueEdt.setLimits(0, 100);
				diagramValueEdt.setIncrements(10, 5);
				diagramValueEdt.setNumber(ama::round(v * 100.0));
			}
			break;
		}
		case 2:
		{
			if (p_viewWnd->getDiagramColorModel() == ColorModel::rgb)
			{
				diagramValueEdt.setLimits(0, 255);
				diagramValueEdt.setIncrements(16, 8);
				diagramValueEdt.setNumber(ama::round(v * 255.0));
			}
			else
			{
				diagramValueEdt.setLimits(0, 100);
				diagramValueEdt.setIncrements(10, 5);
				diagramValueEdt.setNumber(ama::round(v * 100.0));
			}
			break;
		}
		default: break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftDlg - OVERRIDES
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CLeftDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Initialize controls
	diagramColorModelLsb.AddString(L"RGB");
	diagramColorModelLsb.AddString(L"HSV");
	diagramColorModelLsb.AddString(L"HSL");
	diagramColorModelLsb.AddString(L"HSG");
	diagramColorModelLsb.AddString(L"HSP");
	diagramColorModelLsb.SetCurSel(0);
	diagramIndex1Btn.SetCheck(1);
	diagramValueEdt.LimitText(4);
	diagramValueEdt.setNumber(0);
	contourColorModelLsb.AddString(L"RGB");
	contourColorModelLsb.AddString(L"HSV");
	contourColorModelLsb.AddString(L"HSL");
	contourColorModelLsb.AddString(L"HSG");
	contourColorModelLsb.AddString(L"HSP");
	contourColorModelLsb.SetCurSel(0);
	contourColorModelLsb.EnableWindow(FALSE);
	contourIndex1Btn.EnableWindow(FALSE);
	contourIndex2Btn.EnableWindow(FALSE);
	contourIndex3Btn.EnableWindow(FALSE);
	contourIndex1Btn.SetCheck(1);
	return TRUE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::DoDataExchange(CDataExchange* p_dx)
{
	DDX_Control(p_dx, IDC_DIAGRAM_COLOR_MODEL_LSB, diagramColorModelLsb);
	DDX_Control(p_dx, IDC_DIAGRAM_INDEX_1_RDB, diagramIndex1Btn);
	DDX_Control(p_dx, IDC_DIAGRAM_INDEX_2_RDB, diagramIndex2Btn);
	DDX_Control(p_dx, IDC_DIAGRAM_INDEX_3_RDB, diagramIndex3Btn);
	DDX_Control(p_dx, IDC_DIAGRAM_VALUE_EDT, diagramValueEdt);
	DDX_Control(p_dx, IDC_CONTOUR_ENABLED_CKB, contourEnabledCkb);
	DDX_Control(p_dx, IDC_CONTOUR_COLOR_MODEL_LSB, contourColorModelLsb);
	DDX_Control(p_dx, IDC_CONTOUR_INDEX_1_RDB, contourIndex1Btn);
	DDX_Control(p_dx, IDC_CONTOUR_INDEX_2_RDB, contourIndex2Btn);
	DDX_Control(p_dx, IDC_CONTOUR_INDEX_3_RDB, contourIndex3Btn);
	CDialog::DoDataExchange(p_dx);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftDlg - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CLeftDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_DIAGRAM_COLOR_MODEL_LSB, &CLeftDlg::OnDiagramColorModelLsbSelchange)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_DIAGRAM_INDEX_1_RDB, IDC_DIAGRAM_INDEX_3_RDB, &CLeftDlg::OnDiagramIndexRdbClick)
	ON_EN_CHANGE(IDC_DIAGRAM_VALUE_EDT, &CLeftDlg::OnDiagramValueEdtChange)
	ON_BN_CLICKED(IDC_CONTOUR_ENABLED_CKB, &CLeftDlg::OnContourEnabledCkbClick)
	ON_LBN_SELCHANGE(IDC_CONTOUR_COLOR_MODEL_LSB, &CLeftDlg::OnContourColorModelLsbSelchange)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CONTOUR_INDEX_1_RDB, IDC_CONTOUR_INDEX_3_RDB, &CLeftDlg::OnContourIndexRdbClick)
END_MESSAGE_MAP()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::OnDiagramColorModelLsbSelchange()
{
	const ColorModel cm = static_cast<ColorModel>(diagramColorModelLsb.GetCurSel());
	p_viewWnd->setDiagramColorModel(cm);
	switch (cm)
	{
		case ColorModel::rgb:
			diagramIndex1Btn.SetWindowText(L"Red");
			diagramIndex2Btn.SetWindowText(L"Green");
			diagramIndex3Btn.SetWindowText(L"Blue");
			break;
		case ColorModel::hsv:
			diagramIndex1Btn.SetWindowText(L"Hue");
			diagramIndex2Btn.SetWindowText(L"Saturation");
			diagramIndex3Btn.SetWindowText(L"Value");
			break;
		case ColorModel::hsl:
			diagramIndex1Btn.SetWindowText(L"Hue");
			diagramIndex2Btn.SetWindowText(L"Saturation");
			diagramIndex3Btn.SetWindowText(L"Lightness");
			break;
		case ColorModel::hsg:
			diagramIndex1Btn.SetWindowText(L"Hue");
			diagramIndex2Btn.SetWindowText(L"Saturation");
			diagramIndex3Btn.SetWindowText(L"Gray Scale");
			break;
		case ColorModel::hsp:
			diagramIndex1Btn.SetWindowText(L"Hue");
			diagramIndex2Btn.SetWindowText(L"Saturation");
			diagramIndex3Btn.SetWindowText(L"Perceived Brightness");
			break;
		default:
			diagramIndex1Btn.SetWindowText(L"Value 1");
			diagramIndex2Btn.SetWindowText(L"Value 2");
			diagramIndex3Btn.SetWindowText(L"Value 3");
			break;
	}
	refreshDiagramValueEdt();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::OnDiagramIndexRdbClick(UINT id)
{
	p_viewWnd->setDiagramIndex(id - IDC_DIAGRAM_INDEX_1_RDB);
	refreshDiagramValueEdt();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::OnDiagramValueEdtChange()
{
	diagramValueEdt.UpdateWindow();
	p_viewWnd->setDiagramValue(diagramValueEdt.getNumber());
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::OnContourEnabledCkbClick()
{
	const bool b = contourEnabledCkb.GetCheck() == 1;
	p_viewWnd->setContourEnabled(b);
	contourColorModelLsb.EnableWindow(b);
	contourIndex1Btn.EnableWindow(b);
	contourIndex2Btn.EnableWindow(b);
	contourIndex3Btn.EnableWindow(b);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::OnContourColorModelLsbSelchange()
{
	const ColorModel cm = static_cast<ColorModel>(contourColorModelLsb.GetCurSel());
	p_viewWnd->setContourColorModel(cm);
	switch (cm)
	{
		case ColorModel::rgb:
			contourIndex1Btn.SetWindowText(L"Red");
			contourIndex2Btn.SetWindowText(L"Green");
			contourIndex3Btn.SetWindowText(L"Blue");
			break;
		case ColorModel::hsv:
			contourIndex1Btn.SetWindowText(L"Hue");
			contourIndex2Btn.SetWindowText(L"Saturation");
			contourIndex3Btn.SetWindowText(L"Value");
			break;
		case ColorModel::hsl:
			contourIndex1Btn.SetWindowText(L"Hue");
			contourIndex2Btn.SetWindowText(L"Saturation");
			contourIndex3Btn.SetWindowText(L"Lightness");
			break;
		case ColorModel::hsg:
			contourIndex1Btn.SetWindowText(L"Hue");
			contourIndex2Btn.SetWindowText(L"Saturation");
			contourIndex3Btn.SetWindowText(L"Gray Scale");
			break;
		case ColorModel::hsp:
			contourIndex1Btn.SetWindowText(L"Hue");
			contourIndex2Btn.SetWindowText(L"Saturation");
			contourIndex3Btn.SetWindowText(L"Perceived Brightness");
			break;
		default:
			contourIndex1Btn.SetWindowText(L"Value 1");
			contourIndex2Btn.SetWindowText(L"Value 2");
			contourIndex3Btn.SetWindowText(L"Value 3");
			break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftDlg::OnContourIndexRdbClick(UINT id)
{
	p_viewWnd->setContourIndex(id - IDC_CONTOUR_INDEX_1_RDB);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftBar
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftBar - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CLeftBar::CLeftBar() : 
	CDialogBar(), 
	leftDlg()
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftBar - ELEMENT FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CLeftBar::Create(CWnd* p_pw)
{
	return CDialogBar::Create(p_pw, IDD_LEFT_BAR, CBRS_ALIGN_LEFT | CBRS_BORDER_LEFT, IDD_LEFT_BAR);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CLeftBar - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CLeftBar, CDialogBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CLeftBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == 0)
	{
		if (leftDlg.Create(this)) return 0;
	}
	return -1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CLeftBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);
	leftDlg.MoveWindow(0, 0, cx, cy);
	leftDlg.ShowWindow(TRUE);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
