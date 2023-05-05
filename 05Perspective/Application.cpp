#include "Application.h"
#include "WindowClass.h"
#include "Cylinder.h"
#include "MouseButton.h"

const std::wstring gm::Application::mClassName{ L"GameMath" };

LRESULT CALLBACK gm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs{ (LPCREATESTRUCT)lParam };
		gm::Application* pApplication{ (gm::Application*)pcs->lpCreateParams };
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApplication));
	}
	else
	{
		gm::Application* pApplication{ reinterpret_cast<gm::Application*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))) };
		if (pApplication != nullptr)
			switch (message)
			{
			case WM_SIZE:
				pApplication->OnResize(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

gm::Application::Application(const int nCmdShow)
	: mpWindowClass{ nullptr }
	, mWindow{ L"GameMath 05: Perspective" }
	, mpD2DFactory{ nullptr }
	, mMeshesPtr{}
	, mKeyboard{}
	, mShowCursor{ true }
	, mCursorMode{ gm::CursorMode::Absolute }
	, mSaveCursorPos{}
{
	mpWindowClass = new gm::WindowClass{ mClassName };
	mWindow.Initialize(this, mClassName, nCmdShow);
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mpD2DFactory);
	mWindow.SetFactory(mpD2DFactory);
	mWindow.CreateRenderTarget();
	mWindow.CreateSolidColorBrush();

	mMeshesPtr.emplace_back(std::make_shared<gm::Cylinder>(100.f, 300.f, 16));
}

gm::Application::~Application()
{
	SafeRelease(&mpD2DFactory);
	delete mpWindowClass;
}

gm::Window* gm::Application::GetWindow()
{
	return &mWindow;
}

int gm::Application::Run()
{
	MSG msg{};
	bool doesEnd{ false };
	timeBeginPeriod(1);
	std::chrono::steady_clock::time_point start{};
	std::chrono::duration<double, std::nano> endMinusStart{}, frameDuration{ 10000000. };
	while (!doesEnd)
	{
		start = std::chrono::steady_clock::now();
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				doesEnd = true;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Input(frameDuration.count());
		Render();
		endMinusStart = std::chrono::steady_clock::now() - start;
		if (frameDuration.count() - endMinusStart.count() > 0)
			std::this_thread::sleep_for(frameDuration - endMinusStart);
	}
	timeEndPeriod(1);
	return (int)msg.wParam;
}

void gm::Application::Input(const double duration)
{
	GetKeyboardState(mKeyboard);
	gm::MouseButton mouseButton{ gm::MouseButton::Sentinel };
	bool showCursor{ true };
	if ((mKeyboard[VK_LBUTTON] & 0x80) == 0x80)
	{
		mouseButton = gm::MouseButton::Left;
		showCursor = false;
	}
	if ((mKeyboard[VK_MBUTTON] & 0x80) == 0x80)
	{
		mouseButton = gm::MouseButton::Middle;
		showCursor = false;
	}
	if ((mKeyboard[VK_RBUTTON] & 0x80) == 0x80)
	{
		mouseButton = gm::MouseButton::Right;
		showCursor = false;
	}
	if (showCursor && !mShowCursor)
	{
		mCursorMode = gm::CursorMode::Absolute;
		mShowCursor = true;
		ShowCursor(TRUE);
	}
	if (!showCursor && mShowCursor)
	{
		mCursorMode = gm::CursorMode::Relative;
		mShowCursor = false;
		while (ShowCursor(FALSE) > 0);
	}
	mCursorPos = GetCursor();
	if (mCursorMode == gm::CursorMode::Relative)
		for (auto meshPtr : mMeshesPtr)
			meshPtr->Move(float(duration), mouseButton, mCursorPos);
}

void gm::Application::Render()
{
	ID2D1HwndRenderTarget* pRenderTarget{ mWindow.GetRenderTarget() };
	if (pRenderTarget == nullptr)
		return;
	ID2D1SolidColorBrush* pSolidColorBrush{ mWindow.GetSolidColorBrush() };
	if (pSolidColorBrush == nullptr)
		return;

	pRenderTarget->BeginDraw();
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	for (auto& meshPtr : mMeshesPtr)
		meshPtr->Render(&mWindow, pSolidColorBrush);
	
	pRenderTarget->EndDraw();
}

void gm::Application::OnResize(const UINT width, const UINT height)
{
	mWindow.Resize(width, height);
	for (auto& meshPtr : mMeshesPtr)
		meshPtr->SetHasMoved();
	Render();
}

POINT gm::Application::GetCursor()
{
	POINT pos{};
	GetCursorPos(&pos);
	if (mCursorMode == gm::CursorMode::Relative)
	{
		POINT savePos{ mSaveCursorPos };
		SetCursorPos(savePos.x, savePos.y);
		pos.x = savePos.x - pos.x;
		pos.y = savePos.y - pos.y;
	}
	else
		mSaveCursorPos = pos;
	return pos;
}
