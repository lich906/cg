#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad_glfw.h"

#include "vendor/ImGuiFileDialog/ImGuiFileDialog.h"
#include "graphics/CurrentShader.h"
#include "view/Window.h"
#include "controller/MenuController.h"

struct FakeMenuController : public IMenuController
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

struct FakeMouseInputController : public IMouseInputController
{
	// Inherited via IMouseInputController
	virtual void OnMouseDown(const Vector& pos) override
	{
		printf("Mouse down: %.2f\t%.2f\n", pos.x, pos.y);
	}
	virtual void OnMouseUp(const Vector& pos) override
	{
		printf("Mouse up: %.2f\t%.2f\n", pos.x, pos.y);
	}
	virtual void OnMouseMove(const Vector& delta) override
	{
		//printf("Mouse move: %.2f\t%.2f\n", delta.x, delta.y);
	}
	virtual void OnScrollUp(float offset) override
	{
		printf("Scroll up: %.2f\n", offset);
	}
	virtual void OnScrollDown(float offset) override
	{
		printf("Scroll down: %.2f\n", offset);
	}
};

int main()
{
	auto doc = std::make_shared<Document>();
	auto scene = std::make_shared<Scene>();
	auto menuController = std::make_shared<MenuController>(doc, scene);

	Window window(scene, std::make_shared<FakeMouseInputController>(), menuController);
	window.Run();
}
