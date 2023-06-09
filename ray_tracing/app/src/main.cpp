#include "core/core.h"

#include "SceneLayer.h"
#include "ImGuiOverlay.h"

int main()
try
{
	Scene scene;
	auto app = std::make_unique<core::Application>("Ray tracing", 320, 200);
	app->PushLayer(std::make_shared<SceneLayer>(scene));
	app->PushLayer(std::make_shared<ImGuiOverlay>(scene));

	app->Run();

	return 0;
}
catch (std::runtime_error& e)
{
	std::cout << "Runtime error: " << e.what() << std::endl;

	return 1;
}
