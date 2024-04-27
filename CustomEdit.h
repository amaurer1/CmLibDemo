//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CustomEdit.h
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2023 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <optional>
#include <format>
#include "Function.h"
#include "CustomControl.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CCustomEdit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCustomEdit : public ILock, public CEdit
{
// ELEMENT DATA
private:

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CCustomEdit() : ILock(), CEdit() {}

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	afx_msg void OnChar(UINT, UINT, UINT);
	afx_msg void OnContextMenu(CWnd*, CPoint);
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CTextEdit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CTextEdit : public CCustomEdit
{
// ELEMENT DATA
private:
	bool changeHandlerEnabled;

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	CTextEdit() : CCustomEdit(), changeHandlerEnabled(true) {}

// ELEMENT FUNCTIONS
public:
	void setText(const std::wstring&, const bool = false);
	std::wstring getText() const;

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg BOOL OnEnChange();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
constexpr int getMaxPrecision()
requires std::integral<T>
{
	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
constexpr int getMaxPrecision()
requires std::floating_point<T>
{
	return std::numeric_limits<T>::digits10;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline T convertToNumber(const std::wstring& s)
requires std::signed_integral<T> && (!std::same_as<T, long long>)
{
	return static_cast<T>(wcstol(s.data(), nullptr, 10));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline T convertToNumber(const std::wstring& s)
requires std::unsigned_integral<T> && (!std::same_as<T, unsigned long long>)
{
	return static_cast<T>(wcstoul(s.data(), nullptr, 10));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline T convertToNumber(const std::wstring& s)
requires std::same_as<T, long long>
{
	return wcstoll(s.data(), nullptr, 10);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline T convertToNumber(const std::wstring& s)
requires std::same_as<T, unsigned long long>
{
	return wcstoull(s.data(), nullptr, 10);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline T convertToNumber(const std::wstring& s)
requires std::floating_point<T>
{
	return static_cast<T>(_wtof(s.data()));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline std::wstring convertToString(const T n, const int = 0)
requires std::integral<T>
{
	return std::format(L"{}", n);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
inline std::wstring convertToString(const T n, const int p = 0)
requires std::floating_point<T>
{
	constexpr int nss = std::numeric_limits<T>::digits10 + 10; // Number string size
	std::wstring ns(nss, '\0'); // Number string
	::swprintf_s(&ns[0], nss, !p ? L"%.0f" : std::format(L"%.{}g", p).data(), n);
	return ns;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TNumberEdit
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
concept number = std::integral<T> && (!std::same_as<T, bool>) && (!std::same_as<T, char>) || std::floating_point<T>;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
requires number<T>
class TNumberEdit : public CTextEdit
{
// ELEMENT DATA
private:
	bool numberValid;
	T limit1;
	T limit2;
	T increment1;
	T increment2;
	int precision;

// CONSTRUCTION / DESTRUCTION / ASSIGNMENT
public:
	TNumberEdit(const int = getMaxPrecision<T>());
	TNumberEdit(const T, const T, const int = getMaxPrecision<T>());
	TNumberEdit(const T, const T, const T, const T, const int = getMaxPrecision<T>());

// ELEMENT FUNCTIONS
private:
	T calcLimit(const T n) const {return ama::limit(n, limit1, limit2);}
public:
	bool isNumberValid() const {return numberValid;}
	void setLimit1(const T l) {limit1 = l;}
	void setLimit2(const T l) {limit2 = l;}
	void removeLimit1() {limit1 = std::numeric_limits<T>::lowest();}
	void removeLimit2() {limit2 = (std::numeric_limits<T>::max)();}
	void setLimits(const T, const T);
	void setLimits(const std::array<T, 2>&);
	void removeLimits();
	void setIncrement1(const T i) {increment1 = i;}
	void setIncrement2(const T i) {increment2 = i;}
	void setIncrements(const T, const T);
	void setPrecision(const int p) {precision = p;}
	void setNumber(const T, const bool = false);
	void removeNumber(const bool = false);
	T getNumber() const;
	void setOptionalNumber(const std::optional<T>&, const bool = false);
	std::optional<T> getOptionalNumber() const;
	void increment(const bool, const T) requires std::integral<T>;
	void increment(const bool, const T) requires std::floating_point<T>;
	void incrementLastDigit(const bool) requires std::integral<T>;
	void incrementLastDigit(const bool) requires std::floating_point<T>;

// MESSAGE MAP FUNCTIONS
protected:
	afx_msg void OnKillFocus(CWnd*);
	afx_msg BOOL OnMouseWheel(UINT, short, CPoint);
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	afx_msg BOOL OnEnChange();
	DECLARE_MESSAGE_MAP()
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TNumberEdit - CONSTRUCTION / DESTRUCTION / ASSIGNMENT
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline TNumberEdit<T>::TNumberEdit(const int p) : 
	CTextEdit(), 
	numberValid(false), 
	limit1(std::numeric_limits<T>::lowest()), 
	limit2((std::numeric_limits<T>::max)()), 
	increment1(T(0)), 
	increment2(T(0)), 
	precision(p)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline TNumberEdit<T>::TNumberEdit(const T i1, const T i2, const int p) : 
	CTextEdit(), 
	numberValid(false), 
	limit1(std::numeric_limits<T>::lowest()), 
	limit2((std::numeric_limits<T>::max)()), 
	increment1(i1), 
	increment2(i2), 
	precision(p)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline TNumberEdit<T>::TNumberEdit(const T l1, const T l2, const T i1, const T i2, const int p) : 
	CTextEdit(), 
	numberValid(false), 
	limit1(l1), 
	limit2(l2), 
	increment1(i1), 
	increment2(i2), 
	precision(p)
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TNumberEdit - ELEMENT FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::setLimits(const T l1, const T l2)
{
	setLimit1(l1);
	setLimit2(l2);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::setLimits(const std::array<T, 2>& la)
{
	setLimit1(la[0]);
	setLimit2(la[1]);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::removeLimits()
{
	removeLimit1();
	removeLimit2();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::setIncrements(const T i1, const T i2)
{
	setIncrement1(i1);
	setIncrement2(i2);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::setNumber(const T n, const bool che)
{
	numberValid = true;
	setText(convertToString(n, precision), che);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::removeNumber(const bool che)
{
	numberValid = false;
	setText(L"", che);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline T TNumberEdit<T>::getNumber() const
{
	return calcLimit(convertToNumber<T>(getText()));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::setOptionalNumber(const std::optional<T>& o_n, const bool che)
{
	o_n ? setNumber(*o_n, che) : removeNumber(che);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline std::optional<T> TNumberEdit<T>::getOptionalNumber() const
{
	return numberValid ? std::optional<T>(getNumber()) : std::nullopt;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::increment(const bool dir, const T is)
requires std::integral<T>
{
	if (numberValid && is > T(0))
	{
		using namespace std;
		const wstring ns(getText()); // Number string
		if (const T n = convertToNumber<T>(ns); n >= limit1 && n <= limit2) // Number
		{
			const T b = !dir ? std::numeric_limits<T>::lowest() : (std::numeric_limits<T>::max)();
			const T in = !dir ? n < b + is ? b : n - is : n > b - is ? b : n + is; // Incremented number
			const wstring ins = convertToString(calcLimit(in)); // Incremented number string
			const DWORD ocp = GetSel();
			SetRedraw(FALSE);
			setText(ins, true);
			const int ncp = static_cast<int>(ins.length()) - (static_cast<int>(ns.length()) - LOWORD(ocp));
			SetSel(ncp, ncp);
			SetRedraw(TRUE);
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::increment(const bool dir, const T is)
requires std::floating_point<T>
{
	if (numberValid && is > T(0))
	{
		using namespace std;
		const wstring ns(getText()); // Number string
		if (const T n = convertToNumber<T>(ns); n >= limit1 && n <= limit2) // Number
		{
			const wstring ins = convertToString(calcLimit(!dir ? n - is : n + is), precision); // Incremented number string
			const int cp = static_cast<int>(ins.length()) - (static_cast<int>(ns.length()) - LOWORD(GetSel()));
			SetRedraw(FALSE);
			setText(ins, true);
			SetSel(cp, cp);
			SetRedraw(TRUE);
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::incrementLastDigit(const bool dir)
requires std::integral<T>
{
	increment(dir, T(1));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::incrementLastDigit(const bool dir)
requires std::floating_point<T>
{
	if (numberValid)
	{
		using namespace std;
		const wstring ns(getText()); // Number string
		if (const T n = convertToNumber<T>(ns); n >= limit1 && n <= limit2) // Number
		{
			const size_t ep = ::wcscspn(ns.data(), L"eE"); // Exponent position
			const wstring bs(ns.substr(0, ep)); // Basis string
			const wstring es(ns.substr(ep, ns.size() - ep)); // Exponent string
			const size_t pp = bs.find_first_of('.'); // Point position
			const size_t p = pp != wstring::npos ? bs.size() - pp - 1 : 0; // Precision
			const T bn = convertToNumber<T>(bs); // Basis number
			const T is = T(1.0) / static_cast<T>(pow(10, p)); // Increment step
			const T ibn = !dir ? bn - is : bn + is; // Incremented basis number
			constexpr int inss = numeric_limits<T>::digits10 + 10; // Incremented number string size
			wstring ins(inss, '\0'); // Incremented number string
			::swprintf_s(&ins[0], inss, format(L"%.{}f%s", p).data(), ibn, es.data());
			if (const T in = convertToNumber<T>(ins); in >= limit1 && in <= limit2) // Incremented number
			{
				const int cp = static_cast<int>(ins.length()) - (static_cast<int>(ns.length()) - LOWORD(GetSel()));
				SetRedraw(FALSE);
				setText(ins, true);
				SetSel(cp, cp);
				SetRedraw(TRUE);
				Invalidate(FALSE);
				UpdateWindow();
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TNumberEdit - MESSAGE MAP FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PTM_WARNING_DISABLE
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
requires number<T>
inline const AFX_MSGMAP* TNumberEdit<T>::GetMessageMap() const
{
	return GetThisMessageMap();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
requires number<T>
inline const AFX_MSGMAP* PASCAL TNumberEdit<T>::GetThisMessageMap()
{
	typedef TNumberEdit<T> ThisClass;
	typedef CTextEdit TheBaseClass;
	__pragma(warning(push))
	__pragma(warning(disable: 4640))
	static const AFX_MSGMAP_ENTRY _messageEntries[] = 
	{
		ON_WM_KILLFOCUS()
		ON_WM_KEYDOWN()
		ON_WM_MOUSEWHEEL()
		ON_CONTROL_REFLECT_EX(EN_CHANGE, &TNumberEdit::OnEnChange)
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0}
	};
	__pragma(warning(pop))
	static const AFX_MSGMAP messageMap = {&TheBaseClass::GetThisMessageMap, &_messageEntries[0]};
	return &messageMap;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PTM_WARNING_RESTORE
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::OnKillFocus(CWnd* pNewWnd)
{
	CTextEdit::OnKillFocus(pNewWnd);
	if (numberValid) setNumber(getNumber());
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline void TNumberEdit<T>::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!isLocked() && !(GetStyle() & ES_READONLY))
	{
		const bool shift = HIWORD(::GetKeyState(VK_SHIFT));
		const bool ctrl = HIWORD(::GetKeyState(VK_CONTROL));
		if (nChar == VK_DOWN)
		{
			if (!ctrl) increment(false, !shift ? increment1 : increment2);
			else if (!shift) incrementLastDigit(false);
			return;
		}
		else if (nChar == VK_UP)
		{
			if (!ctrl) increment(true, !shift ? increment1 : increment2);
			else if (!shift) incrementLastDigit(true);
			return;
		}
	}
	CTextEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline BOOL TNumberEdit<T>::OnMouseWheel(UINT nFlags, short zDelta, CPoint pnt)
{
	if (!isLocked() && !(GetStyle() & ES_READONLY))
	{
		const bool shift = nFlags & MK_SHIFT;
		const bool ctrl = nFlags & MK_CONTROL;
		const bool dir = zDelta > 0;
		if (!ctrl) increment(dir, !shift ? increment1 : increment2);
		else if (!shift) incrementLastDigit(dir);
	}
	return CTextEdit::OnMouseWheel(nFlags, zDelta, pnt);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T>
requires number<T>
inline BOOL TNumberEdit<T>::OnEnChange()
{
	if (!isLocked() && !CTextEdit::OnEnChange())
	{
		numberValid = true;
		return FALSE;
	}
	return TRUE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
