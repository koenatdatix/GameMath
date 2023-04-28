#include "WindowClass.h"

gm::WindowClass::WindowClass(const std::wstring& className)
{
	HMODULE hModule{ GetModuleHandle(nullptr) };
	WNDCLASSEXW wcex{};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = gm::WndProc;
	wcex.cbClsExtra = sizeof(LPVOID);
	wcex.cbWndExtra = 0;
	wcex.hInstance = hModule;
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className.c_str();
	[[maybe_unused]] ATOM wc{ RegisterClassExW(&wcex) };
}
