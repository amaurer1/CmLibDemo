//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CustomControl.h
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Resource.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ILock
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class ILock
{
// ELEMENT DATA
private:
	bool locked;

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	ILock() : locked(false) {}

// ELEMENT FUNCTIONS
public:
	void setLocked(const bool e) {locked = e;}
	bool isLocked() const {return locked;}
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCustomButton
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCustomButton : public ILock, public CButton
{
// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnLButtonUp(UINT, CPoint);
	afx_msg void OnKeyUp(UINT, UINT, UINT);
	afx_msg UINT OnGetDlgCode();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCustomComboBox
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCustomComboBox : public ILock, public CComboBox
{
// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	afx_msg void OnChar(UINT, UINT, UINT);
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCustomListBox
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCustomListBox : public ILock, public CListBox
{
// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	afx_msg void OnChar(UINT, UINT, UINT);
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
