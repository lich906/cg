#include "BaseGlfwWindow.h"
#include "GlfwInitializer.h"
#include "LetterM.h"
#include "LetterA.h"
#include <iostream>
#include <vector>

class Window : public BaseGlfwWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseGlfwWindow(w, h, title)
		, m_letterM(0.2f, 0.3f, { 0.2f, 0.5f, 0.4f, 1.0f })
		, m_letterA(0.2f, 0.3f, { 0.6f, 0.2f, 0.7f, 1.0f })
		, m_letterA2(0.2f, 0.3f, { 0.1f, 0.9f, 0.9f, 1.0f })
	{
	}

private:
	void Draw(int width, int height) override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);

		m_letterM.Draw(-0.6f, 0.0f);
		m_letterA.Draw(-0.3f, 0.0f);
		m_letterA2.Draw(0.0f, 0.0f);
	}

	LetterM m_letterM;
	LetterA m_letterA;
	LetterA m_letterA2;
};

int main()
{
	GlfwInitializer initGlfw;
	Window window{ 800, 600, "Hello, MAA" };
	window.Run();
}
