#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include "vendor/ImGuiFileDialog/ImGuiFileDialog.h"
#include "graphics/CurrentShader.h"

#include "Window.h"

struct MenuControllerMock : public IMenuController
{
	// Inherited via IMenuController
	virtual void OnFileOpen(const std::string& filePath) override
	{
		printf("Open file: %s\n", filePath.c_str());
	}
	virtual void OnFileClose() override
	{
		printf("Close file.\n");
	}
};

int main()
{
	Window window(nullptr, std::make_shared<MenuControllerMock>());
	window.Run();
}
