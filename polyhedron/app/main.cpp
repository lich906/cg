#include "core/core.h"

#include "PolyhedronLayer.h"

int main()
try
{
	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Polyhedron");

	app->PushLayer(std::make_shared<PolyhedronLayer>());

	app->Run();

	return 0;
}
catch (std::runtime_error& e)
{
	std::cout << "Runtime error: " << e.what() << std::endl;
}
