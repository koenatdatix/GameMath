#pragma once
#include "pch.h"

namespace gm
{
	class WindowClass final
	{
	public:
		explicit WindowClass(const std::wstring& className);
	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}
