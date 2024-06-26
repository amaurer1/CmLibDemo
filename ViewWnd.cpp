//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ViewWnd.cpp
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2019-2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "pch.h"
#include "framework.h"
#include "ViewWnd.h"
#include "CmLibDemoApp.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CImageSizeDlg
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CImageSizeDlg - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CImageSizeDlg::CImageSizeDlg(const int s) : 
	CDialog(IDD_IMAGE_SIZE_DLG), 
	size(s), 
	sizeEdt()
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CImageSizeDlg, CDialog)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CImageSizeDlg - OVERRIDES
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CImageSizeDlg::DoDataExchange(CDataExchange* p_dx)
{
	DDX_Control(p_dx, IDC_SIZE_EDT, sizeEdt);
	CDialog::DoDataExchange(p_dx);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CImageSizeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	sizeEdt.setNumber(size);
	return TRUE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CImageSizeDlg::OnOK()
{
	if (size <= 0 || size > 10000)
	{
		::AfxMessageBox(L"Invalid image size");
	}
	else
	{
		CDialog::OnOK();
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CImageSizeDlg - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CImageSizeDlg, CDialog)
	ON_EN_CHANGE(IDC_SIZE_EDT, &CImageSizeDlg::OnSizeEdtChange)
END_MESSAGE_MAP()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CImageSizeDlg::OnSizeEdtChange()
{
	size = sizeEdt.getNumber();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CViewWnd::CViewWnd() : 
	CWnd(), 
	image(), 
	wndSize(0, 0), 
	imageOrigin(0, 0), 
	imageSize(0), 
	diagramColorModel(ColorModel::rgb), 
	diagramIndex(0), 
	diagramValue(0.0), 
	contourEnabled(false), 
	contourColorModel(ColorModel::rgb), 
	contourIndex(0)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd - ELEMENT FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ama::Color<double> CViewWnd::calcDiagramColor(const double x, const double y)
{
	switch (diagramIndex)
	{
		case 0:
		{
			switch (diagramColorModel)
			{
				case ColorModel::rgb: return {diagramValue, x, y};
				case ColorModel::hsv: return ama::convertToRgb(ama::Hsv<double>(diagramValue, x, y));
				case ColorModel::hsl: return ama::convertToRgb(ama::Hsl<double>(diagramValue, x, y));
				case ColorModel::hsg: return ama::convertToRgb(ama::Hsg<double>(diagramValue, x, y));
				case ColorModel::hsp: return ama::convertToRgb(ama::Hsp<double>(diagramValue, x, y));
				default: return {};
			}
			break;
		}
		case 1:
		{
			switch (diagramColorModel)
			{
				case ColorModel::rgb: return {x, diagramValue, y};
				case ColorModel::hsv: return ama::convertToRgb(ama::Hsv<double>(x, diagramValue, y));
				case ColorModel::hsl: return ama::convertToRgb(ama::Hsl<double>(x, diagramValue, y));
				case ColorModel::hsg: return ama::convertToRgb(ama::Hsg<double>(x, diagramValue, y));
				case ColorModel::hsp: return ama::convertToRgb(ama::Hsp<double>(x, diagramValue, y));
				default: return {};
			}
			break;
		}
		case 2:
		{
			switch (diagramColorModel)
			{
				case ColorModel::rgb: return {x, y, diagramValue};
				case ColorModel::hsv: return ama::convertToRgb(ama::Hsv<double>(x, y, diagramValue));
				case ColorModel::hsl: return ama::convertToRgb(ama::Hsl<double>(x, y, diagramValue));
				case ColorModel::hsg: return ama::convertToRgb(ama::Hsg<double>(x, y, diagramValue));
				case ColorModel::hsp: return ama::convertToRgb(ama::Hsp<double>(x, y, diagramValue));
				default: return {};
			}
			break;
		}
		default: break;
	}
	return {};
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double CViewWnd::calcContourValue(const ama::Color<double>& c)
{
	switch (contourIndex)
	{
		case 0:
		{
			switch (contourColorModel)
			{
				case ColorModel::rgb: return c.r;
				case ColorModel::hsv: return ama::convertToHsv(c).h;
				case ColorModel::hsl: return ama::convertToHsl(c).h;
				case ColorModel::hsg: return ama::convertToHsg(c).h;
				case ColorModel::hsp: return ama::convertToHsp(c).h;
				default: return 0.0;
			}
			break;
		}
		case 1:
		{
			switch (contourColorModel)
			{
				case ColorModel::rgb: return c.g;
				case ColorModel::hsv: return ama::convertToHsv(c).s;
				case ColorModel::hsl: return ama::convertToHsl(c).s;
				case ColorModel::hsg: return ama::convertToHsg(c).s;
				case ColorModel::hsp: return ama::convertToHsp(c).s;
				default: return 0.0;
			}
			break;
		}
		case 2:
		{
			switch (contourColorModel)
			{
				case ColorModel::rgb: return c.b;
				case ColorModel::hsv: return ama::convertToHsv(c).v;
				case ColorModel::hsl: return ama::convertToHsl(c).l;
				case ColorModel::hsg: return ama::convertToHsg(c).g;
				case ColorModel::hsp: return ama::convertToHsp(c).p;
				default: return 0.0;
			}
			break;
		}
		default: break;
	}
	return 0.0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::calcImage()
{
	if (!image.IsNull())
	{
		const CSize is(image.getSize());
		for (int j = 0; j < is.cy; ++j)
		{
			const double y = j / (is.cy - 1.0);
			for (int i = 0; i < is.cx; ++i)
			{
				const double x = i / (is.cx - 1.0);
				const ama::Color<double> dc(calcDiagramColor(x, y));
				if (contourEnabled)
				{
					const double cv = ama::limit(static_cast<int>(calcContourValue(dc) * 20.0) / 19.0, 0.0, 1.0);
					image.setPixel(i, j, ama::Color<double>(cv, cv, cv));
				}
				else
				{
					image.setPixel(i, j, dc);
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::recalcLayout()
{
	const double r = 0.01;
	if (wndSize.cy / static_cast<double>(wndSize.cx) < 1.0)
	{
		const int b = ama::round(wndSize.cy * r);
		imageOrigin = {ama::round((wndSize.cx - wndSize.cy) / 2.0) + b, b};
		imageSize = ama::round(wndSize.cy * (1.0 - 2.0 * r));
	}
	else
	{
		const int b = ama::round(wndSize.cx * r);
		imageOrigin = {b, ama::round((wndSize.cy - wndSize.cx) / 2.0) + b};
		imageSize = ama::round(wndSize.cx * (1.0 - 2.0 * r));
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::refresh()
{
	Invalidate(FALSE);
	UpdateWindow();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CViewWnd::Create(CWnd* p_pw, UINT id)
{
	LPCTSTR cn = ::AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor(nullptr, IDC_ARROW));
	return CWnd::CreateEx(WS_EX_CLIENTEDGE, cn, nullptr, WS_CHILD | WS_VISIBLE, {0, 0, 0, 0}, p_pw, id);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::setDiagramColorModel(const ColorModel cm)
{
	diagramColorModel = cm;
	calcImage();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::setDiagramIndex(const int v)
{
	diagramIndex = v;
	calcImage();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::setDiagramValue(const int v)
{
	if (diagramColorModel == ColorModel::rgb)
	{
		diagramValue = v / 255.0;
	}
	else
	{
		diagramValue = diagramIndex == 0 ? v / 360.0 : v / 100.0;
	}
	calcImage();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::setContourEnabled(const bool b)
{
	contourEnabled =  b;
	calcImage();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::setContourColorModel(const ColorModel cm)
{
	contourColorModel = cm;
	calcImage();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::setContourIndex(const int v)
{
	contourIndex = v;
	calcImage();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CViewWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_COMMAND(ID_FILE_SAVE_IMAGE_AS, &CViewWnd::OnFileSaveImageAs)
	ON_COMMAND(ID_EDIT_CHANGE_IMAGE_SIZE, &CViewWnd::OnEditChangeImageSize)
END_MESSAGE_MAP()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == 0)
	{
		const CSize mws( // Maximum window size
			::GetSystemMetrics(SM_CXSCREEN), 
			::GetSystemMetrics(SM_CYSCREEN));
		const int is = (std::min)(mws.cx, mws.cy) / 2; // Image size
		if (image.create({is, is}, 24))
		{
			calcImage();
			return 0;
		}
	}
	return -1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	wndSize = {cx, cy};
	recalcLayout();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::OnPaint() 
{
	CPaintDC dc(this);
	const COLORREF bc = ::GetSysColor(COLOR_3DLIGHT);
	dc.FillSolidRect(0, 0, imageOrigin.x, wndSize.cy, bc);
	dc.FillSolidRect(imageOrigin.x + imageSize, 0, wndSize.cx - imageOrigin.x - imageSize, wndSize.cy, bc);
	dc.FillSolidRect(imageOrigin.x, 0, imageSize, imageOrigin.y, bc);
	dc.FillSolidRect(imageOrigin.x, imageOrigin.y + imageSize, imageSize, wndSize.cy - imageOrigin.y - imageSize, bc);
	dc.SetStretchBltMode(COLORONCOLOR);
	image.StretchBlt(dc.GetSafeHdc(), imageOrigin.x, imageOrigin.y, imageSize, imageSize);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::OnSysColorChange()
{
	CWnd::OnSysColorChange();
	refresh();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::OnFileSaveImageAs()
{
	if (!image.IsNull())
	{
		CFileDialog dlg(FALSE, 0, 0, 
			OFN_ENABLESIZING, 
			L"BMP Files (*.bmp)|*.bmp|"
			L"PNG Files (*.png)|*.png|"
			L"JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg||", 
			nullptr, 0, FALSE);
		OPENFILENAME& ofn = dlg.GetOFN();
		ofn.nFilterIndex = 2;
		if (dlg.DoModal() == IDOK)
		{
			std::filesystem::path fp(removeImgExt(dlg.GetPathName().GetString()));
			switch (dlg.m_ofn.nFilterIndex)
			{
				case 1: fp += L".bmp"; break;
				case 2: fp += L".png"; break;
				case 3: fp += L".jpeg"; break;
				default: break;
			}
			if (std::filesystem::exists(fp))
			{
				if (::AfxMessageBox(std::format(L"The file {} already exists.\nDo you want to replace it?", fp.c_str()).data(), 
					MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
				{
					::AfxGetApp()->DoWaitCursor(-1);
					return;
				}
			}
			::AfxGetApp()->DoWaitCursor(1);
			if (image.Save(fp.c_str()) != S_OK)
			{
				::AfxGetApp()->DoWaitCursor(-1);
				::AfxMessageBox(L"Save error");
			}
			::AfxGetApp()->DoWaitCursor(-1);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CViewWnd::OnEditChangeImageSize()
{
	CImageSizeDlg dlg(image.getSize().cx);
	if (dlg.DoModal() == IDOK)
	{
		const int s(dlg.getSize());
		if (image.create({s, s}, 24))
		{
			calcImage();
			refresh();
		}
		else
		{
			::AfxMessageBox(L"Image creation error");
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CViewWnd - GLOBAL FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::filesystem::path removeImgExt(const std::filesystem::path& opn)
{
	std::filesystem::path npn(opn);
	std::wstring fe(npn.extension());
	std::transform(fe.cbegin(), fe.cend(), fe.begin(), towlower);
	if (fe == L".bmp" || fe == L".png" || fe == L".jpg"  || fe == L".jpeg")
	{
		npn.replace_extension();
	}
	return npn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
