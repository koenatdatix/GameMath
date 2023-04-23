#pragma once
#include "WindowClass.h"
#include "Window.h"
#include "CursorMode.h"

namespace gm
{
	class Mesh;

	class Application final
	{
	public:
		explicit Application(const int nCmdShow);
		~Application();
		gm::Window* GetWindow();
		int Run();
		void Input(const double nanos);
		void Render();
		void OnResize(const UINT width, const UINT height);
	private:
		gm::WindowClass* mpWindowClass;
		gm::Window mWindow;
		ID2D1Factory* mpD2DFactory;
		std::vector<std::shared_ptr<gm::Mesh>> mMeshesPtr;
		BYTE mKeyboard[256];
		bool mShowCursor;
		gm::CursorMode mCursorMode;
		POINT
			mCursorPos,
			mSaveCursorPos;

		POINT GetCursor();

		static const std::wstring mClassName;
	};
}
