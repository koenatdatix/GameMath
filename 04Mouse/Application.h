#pragma once
#include "pch.h"
#include "WindowClass.h"
#include "Window.h"
#include "CursorMode.h"

namespace gm
{
	class Mesh;

	class Application final
	{
	public:
		explicit Application(int nCmdShow);
		~Application();
		gm::WindowClass* GetWindowClass() const;
		gm::Window* GetWindow();
		int Run();
		void Input(double nanos);
		void Render();
		void OnResize(UINT width, UINT height);
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
