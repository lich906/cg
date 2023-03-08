#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "BaseGlfwWindow.h"
#include "GlfwInitializer.h"
#include "Color.h"

class Window : public BaseGlfwWindow
{
public:
	using BaseGlfwWindow::BaseGlfwWindow;

private:
	void Draw(int width, int height) override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, width, height);

		DrawEllipse(0.0f, 0.0f, 0.2f, 0.4f, { 1.0f, 0.0f, 1.0f }, { 0.1f, 0.5f, 0.2f });
	}

	void DrawEllipse(
		float xCenter,
		float yCenter,
		float rx,
		float ry,
		Color borderColor,
		Color fillColor,
		int points = 360)
	{
		const float step = 2 * M_PI / points;

		// Ellipse fill
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(fillColor.r, fillColor.g, fillColor.b);
		glVertex2f(xCenter, yCenter);
		for (float angle = 0; angle < 2 * M_PI; angle += step)
		{
			const float dx = rx * cosf(angle);
			const float dy = ry * sinf(angle);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();

		// Ellipse border
		glBegin(GL_LINE_LOOP);
		glColor3f(borderColor.r, borderColor.g, borderColor.b);
		for (float angle = 0; angle < 2 * M_PI; angle += step)
		{
			const float dx = rx * cosf(angle);
			const float dy = ry * sinf(angle);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}
};

int main()
{
	GlfwInitializer initGlfw;
	Window window{ 800, 600, "Hello, ellipse!" };
	window.Run();
}
