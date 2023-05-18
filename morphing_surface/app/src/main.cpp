#include "core/core.h"

#include "SceneLayer.h"

int main()
try
{
	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Morphing Surface");

	app->PushLayer(std::make_shared<SceneLayer>());

	app->Run();

	return 0;
}
catch (std::runtime_error& e)
{
	std::cout << "Runtime error: " << e.what() << std::endl;
}
