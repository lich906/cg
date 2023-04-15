#include <boost/signals2.hpp>
#include "GraphicsInitializer.h"
#include "graphics/CurrentProgram.h"
#include "BezierCurve.h"
#include "core/Application.h"
#include "core/event/EventDispatcher.h"

class BackgroundLayer : public core::Layer
{
public:
	BackgroundLayer(const glm::vec4& color)
		: m_color(color)
	{
	}

	virtual void OnEvent(core::event::Event& event) override
	{
		core::event::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<core::event::WindowResizeEvent>(
			[](core::event::WindowResizeEvent& e) {
				GlCall(glViewport(0, 0, e.GetWidth(), e.GetHeight()));
				/*gfx::CurrentProgram::Get().SetUniformMatrix4fv("m_projection",
					glm::ortho(0.0f, float(e.GetWidth()), float(e.GetHeight()), 0.0f, -1.0f, 100.0f));*/
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0.0, e.GetWidth(), e.GetHeight(), 0.0, -1.0, 1.0);
				glMatrixMode(GL_MODELVIEW);
				return true;
			});
	}

	virtual void OnUpdate(core::Timestep ts) override
	{
		GlCall(glClearColor(m_color.r, m_color.g, m_color.b, m_color.a));
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
	}

private:
	glm::vec4 m_color;
};

class PointsLineLayer : public core::Layer
{
public:
	PointsLineLayer(const gfx::Vector& p1, const gfx::Vector& p2, const gfx::Vector& p3, const gfx::Vector& p4, const glm::vec4& color)
		: m_mesh(
			{
				{ p1, { 0.0f, 0.0f } },
				{ p2, { 0.0f, 0.0f } },
				{ p3, { 0.0f, 0.0f } },
				{ p4, { 0.0f, 0.0f } },
			},
			{ 0, 1, 1, 2, 2, 3 })
		, m_color(color)
	{
	}

	virtual void OnUpdate(core::Timestep ts) override
	{
		gfx::CurrentProgram::Get().SetUniform4fv("u_color", m_color);
		m_mesh.Draw(GL_LINES);
	}

private:
	gfx::Mesh m_mesh;
	glm::vec4 m_color;
};

class BezierCurveLayer : public core::Layer
{
public:
	BezierCurveLayer(const gfx::Vector& p1, const gfx::Vector& p2, const gfx::Vector& p3, const gfx::Vector& p4, const glm::vec4& color)
		: m_curve(p1, p2, p3, p4)
		, m_color(color)
	{
	}

	virtual void OnUpdate(core::Timestep ts) override
	{
		gfx::CurrentProgram::Get().SetUniform4fv("u_color", m_color);
		m_curve.Draw();
	}

private:
	BezierCurve m_curve;
	glm::vec4 m_color;
};

int main()
{
	std::vector<gfx::Vector> points = {
		{ 200.0f, 100.0f },
		{ 400.0f, 450.0f },
		{ 500.0f, 100.0f },
		{ 700.0f, 500.0f }
	};

	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Bezier curve");

	gfx::Program program("shaders/vertex.glsl", "shaders/fragment.glsl");
	program.Use();
	program.SetUniformMatrix4fv("m_model", glm::mat4(1.0f)); // Load identity matrices by default
	program.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
	program.SetUniformMatrix4fv("m_projection", glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 100.0f));
	gfx::CurrentProgram::Set(program);

	app->PushLayer(std::shared_ptr<BackgroundLayer>(new BackgroundLayer({ 0.0f, 0.0f, 0.0f, 0.0f })));
	app->PushLayer(std::shared_ptr<PointsLineLayer>(new PointsLineLayer(points[0], points[1], points[2], points[3], { 0.8f, 0.8f, 0.8f, 1.0f })));
	app->PushLayer(std::shared_ptr<BezierCurveLayer>(new BezierCurveLayer(points[0], points[1], points[2], points[3], { 1.0f, 0.0f, 0.0f, 1.0f })));

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Setup blending algorithm

	app->Run();

	gfx::CurrentProgram::Unset();

	return 0;
}
