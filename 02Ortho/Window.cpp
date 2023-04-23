#include "Window.h"

gm::Window::Window(const std::wstring& title, uint32_t width, uint32_t height)
	: mTitle{ title }
	, mWidth{ width }
	, mHeight{ height }
	, mhWnd{}
	, mpD2DFactory{ nullptr }
	, mpRenderTarget{ nullptr }
	, mpSolidColorBrush{ nullptr }
{
}

gm::Window::~Window()
{
	SafeRelease(&mpSolidColorBrush);
	SafeRelease(&mpRenderTarget);
}

BOOL gm::Window::Initialize(const gm::Application* pApplication, const std::wstring& className, const int nCmdShow)
{
	HMODULE hModule{ GetModuleHandle(nullptr) };
	mhWnd = CreateWindowW(
		className.c_str(),
		mTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		mWidth,
		mHeight,
		NULL,
		NULL,
		hModule,
		(LPVOID)pApplication
	);
	if (!mhWnd)
		return FALSE;

	BOOL darkMode{ TRUE };
	DwmSetWindowAttribute(mhWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
	//COLORREF colorBorder{ GetSysColor(COLOR_HIGHLIGHT) };
	COLORREF colorCaption{ GetSysColor(COLOR_WINDOWTEXT) };
	COLORREF colorText{ GetSysColor(COLOR_WINDOW) };
	//DwmSetWindowAttribute(mhWnd, DWMWA_BORDER_COLOR, &colorBorder, sizeof(colorBorder));
	DwmSetWindowAttribute(mhWnd, DWMWA_CAPTION_COLOR, &colorCaption, sizeof(colorCaption));
	DwmSetWindowAttribute(mhWnd, DWMWA_TEXT_COLOR, &colorText, sizeof(colorText));

	ShowWindow(mhWnd, nCmdShow);
	UpdateWindow(mhWnd);

	return TRUE;
}

void gm::Window::SetFactory(ID2D1Factory* pD2DFactory)
{
	mpD2DFactory = pD2DFactory;
}

HRESULT gm::Window::CreateRenderTarget()
{
	if (mpD2DFactory == nullptr)
		return E_POINTER;
	if (mpRenderTarget != nullptr)
		return NOERROR;
	RECT rect{};
	GetClientRect(mhWnd, &rect);
	return mpD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			mhWnd,
			D2D1::SizeU(
				rect.right - rect.left,
				rect.bottom - rect.top)
		),
		&mpRenderTarget);
}

void gm::Window::InvalidateRectangle()
{
	if (mhWnd)
		InvalidateRect(mhWnd, NULL, FALSE);
}

HRESULT gm::Window::CreateSolidColorBrush(D2D1::ColorF color)
{
	if (mpRenderTarget == nullptr)
		return E_POINTER;
	return mpRenderTarget->CreateSolidColorBrush(color, &mpSolidColorBrush);
}

ID2D1HwndRenderTarget* gm::Window::GetRenderTarget()
{
	return mpRenderTarget;
}

ID2D1SolidColorBrush* gm::Window::GetSolidColorBrush()
{
	return mpSolidColorBrush;
}
