//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ViewWnd.h
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2019-2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <filesystem>
#include "ColorModel.h"
#include "CustomEdit.h"
#include "TrueColorImage.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
enum class ColorModel {rgb, hsv, hsl, hsg, hsp};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CImageSizeDlg
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CImageSizeDlg : public CDialog
{
// ELEMENT DATA
private:
	int size;
	TNumberEdit<int> sizeEdt;

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CImageSizeDlg(const int);
	DECLARE_DYNAMIC(CImageSizeDlg)

// ELEMENT FUNCTIONS
public:
	int getSize() const {return size;}

// DIALOG DATA
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_IMAGE_SIZE_DLG};
#endif

// OVERRIDES
protected:
	virtual void DoDataExchange(CDataExchange*);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnSizeEdtChange();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CViewWnd : public CWnd
{
// ELEMENT DATA
private:
	CTrueColorImage image;
	CSize wndSize;
	CPoint imageOrigin;
	int imageSize;
	ColorModel diagramColorModel;
	int diagramIndex;
	double diagramValue;
	bool contourEnabled;
	ColorModel contourColorModel;
	int contourIndex;

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CViewWnd();

// ELEMENT FUNCTIONS
private:
	ama::Color<double> calcDiagramColor(const double, const double);
	double calcContourValue(const ama::Color<double>&);
	void recalcLayout();
	void calcImage();
	void refresh();
public:
	BOOL Create(CWnd*, UINT);
	void setDiagramColorModel(const ColorModel);
	ColorModel getDiagramColorModel() const {return diagramColorModel;}
	void setDiagramIndex(const int);
	int getDiagramIndex() const {return diagramIndex;}
	void setDiagramValue(const int);
	double getDiagramValue() const {return diagramValue;}
	void setContourEnabled(const bool);
	void setContourColorModel(const ColorModel);
	ColorModel getContourColorModel() const {return contourColorModel;}
	void setContourIndex(const int);
	int getContourIndex() const {return contourIndex;}

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnSize(UINT, int, int);
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg void OnFileSaveImageAs();
	afx_msg void OnEditChangeImageSize();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd - GOBAL FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::filesystem::path removeImgExt(const std::filesystem::path&);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
