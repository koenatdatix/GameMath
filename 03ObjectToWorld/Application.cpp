#include "Application.h"
#include "WindowClass.h"
#include "Cylinder.h"

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
			case WM_MOUSEMOVE:
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			case WM_PAINT:
				pApplication->OnRender();
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

gm::Application::Application(int nCmdShow)
	: mpWindowClass{ nullptr }
	, mWindow{ L"GameMath 03: Object To World" }
	, mpD2DFactory{ nullptr }
	, mMeshesPtr{}
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

void gm::Application::OnRender()
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
		meshPtr->Render(pRenderTarget, pSolidColorBrush);
	
	pRenderTarget->EndDraw();
}

void gm::Application::OnResize(UINT width, UINT height)
{
	ID2D1HwndRenderTarget* pRenderTarget{ mWindow.GetRenderTarget() };
	if (pRenderTarget != nullptr)
		pRenderTarget->Resize(D2D1::SizeU(width, height));
}
