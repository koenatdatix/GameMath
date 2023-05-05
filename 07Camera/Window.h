#pragma once
#include "pch.h"

namespace gm
{
	class Application;
	class Camera;

	class Window final
	{
	public:
		explicit Window(const std::wstring& title, uint32_t width = 1280, uint32_t height = 960);
		~Window();
		BOOL Initialize([[maybe_unused]] const gm::Application* pApplication, const std::wstring& className, const int nCmdShow);
		void SetFactory(ID2D1Factory* pD2DFactory);
		HRESULT CreateRenderTarget();
		HRESULT CreateSolidColorBrush(D2D1::ColorF color = D2D1::ColorF::White);
		void InvalidateRectangle();
		ID2D1HwndRenderTarget* GetRenderTarget();
		ID2D1SolidColorBrush* GetSolidColorBrush();
		Camera* GetCamera();
		void SetFixedCamera(uint32_t width = 1280, uint32_t height = 960);
		void SetMovingCamera(uint32_t width = 1280, uint32_t height = 960);
		void Resize(uint32_t width, uint32_t height);
	private:
		const std::wstring mTitle;
		uint32_t
			mWidth,
			mHeight;
		HWND mhWnd;
		ID2D1Factory* mpD2DFactory;
		ID2D1HwndRenderTarget* mpRenderTarget;
		ID2D1SolidColorBrush* mpSolidColorBrush;
		Camera* mpCamera;
	};
}
