#include "Application.h"

int APIENTRY wWinMain(_In_ [[maybe_unused]] HINSTANCE hInstance, _In_opt_ [[maybe_unused]] HINSTANCE hPrevInstance, _In_ [[maybe_unused]] LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	MSG msg{};
	{
		gm::Application application{ nCmdShow };

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (msg.message == WM_DWMCOMPOSITIONCHANGED)
				application.GetWindow()->InvalidateRectangle();
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
