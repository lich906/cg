#include "core/core.h"
#include "ParticlesLayer.h"

class BgLayer : public core::Layer
{
public:
	BgLayer(float r, float g, float b, float a)
		: m_r(r)
		, m_g(g)
		, m_b(b)
		, m_a(a)
	{
	}

	virtual void OnUpdate(core::Timestep ts) override
	{
		GlCall(glClearColor(m_r, m_g, m_b, m_a));
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
	}

private:
	float m_r, m_g, m_b, m_a;
};

int main()
try
{
	ParticlesModel model;
	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Charged particles");

	app->PushLayer(std::make_shared<BgLayer>(0.0f, 0.05f, 0.05f, 0.0f));
	app->PushLayer(std::make_shared<ParticlesLayer>(model));

	app->Run();

	return 0;
}
catch (const std::runtime_error& e)
{
	std::cout << "Runtime error: " << e.what() << std::endl;
	return 1;
}
