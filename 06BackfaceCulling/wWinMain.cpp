#include "pch.h"
#include "Application.h"

int APIENTRY wWinMain(_In_ [[maybe_unused]] HINSTANCE hInstance, _In_opt_ [[maybe_unused]] HINSTANCE hPrevInstance, _In_ [[maybe_unused]] LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	gm::Application application{ nCmdShow };
	return application.Run();
}
