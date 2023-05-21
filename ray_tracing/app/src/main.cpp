#include "core/core.h"

#include "SceneLayer.h"

int main()
try
{
	auto app = std::make_unique<core::Application>("Ray tracing", 320, 200);
	app->PushLayer(std::make_shared<SceneLayer>());
	app->Run();

	return 0;
}
catch (std::runtime_error& e)
{
	std::cout << "Runtime error: " << e.what() << std::endl;

	return 1;
}
