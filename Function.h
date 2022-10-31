//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Function.h
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Copyright (c) 2022 Adrian Maurer. All rights reserved.
// Distributed under the MIT software license (http://www.opensource.org/licenses/mit-license.php).
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef AMA_FUNCTION_H
#define AMA_FUNCTION_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <concepts>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace ama {
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T1 = int, class T2>
requires std::integral<T1> && std::floating_point<T2>
constexpr T1 round(const T2 v) noexcept
{
	return static_cast<T1>(v > T2(0.0) ? v + T2(0.5) : v - T2(0.5));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <class T1, class T2, class T3>
constexpr T1 limit(const T1 v, const T2 l1, const T3 l2) noexcept
{
	if (v < l1) return static_cast<T1>(l1);
	if (v > l2) return static_cast<T1>(l2);
	return v;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
} //namespace ama
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif // AMA_FUNCTION_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
