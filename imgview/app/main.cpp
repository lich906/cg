#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include "vendor/ImGuiFileDialog/ImGuiFileDialog.h"
#include "graphics/CurrentShader.h"
#include "view/Window.h"
#include "controller/MenuController.h"
#include "controller/MouseInputController.h"

int main()
{
	auto doc = std::make_shared<Document>();
	auto scene = std::make_shared<Scene>();
	auto menuController = std::make_shared<MenuController>(doc, scene);
	auto mouseInputController = std::make_shared<MouseInputController>(doc);

	Window window(scene, mouseInputController, menuController);
	window.Run();
}