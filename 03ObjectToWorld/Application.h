#pragma once
#include "pch.h"
#include "WindowClass.h"
#include "Window.h"

namespace gm
{
	class Mesh;

	class Application final
	{
	public:
		explicit Application(int nCmdShow);
		~Application();
		gm::Window* GetWindow();
		void OnRender();
		void OnResize(UINT width, UINT height);
	private:
		gm::WindowClass* mpWindowClass;
		gm::Window mWindow;
		ID2D1Factory* mpD2DFactory;
		std::vector<std::shared_ptr<gm::Mesh>> mMeshesPtr;

		static const std::wstring mClassName;
	};
}
