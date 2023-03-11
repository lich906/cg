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
		SetupProjectionMatrix(width, height);

		m_letterM.Draw(-0.6f, 0.0f);
		m_letterA.Draw(-0.3f, 0.0f);
		m_letterA2.Draw(0.0f, 0.0f);
	}

	static void SetupProjectionMatrix(int width, int height)
	{
		// Вычисляет матрицу ортографического преобразования такую, чтобы вписать квадратную область
		// [-1;+1] по обеим осям внутрь видового порта размером width*height пикселей
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		const double aspectRatio = double(width) / double(height);
		double viewWidth = 3.0;
		double viewHeight = viewWidth;
		if (aspectRatio > 1.0)
		{
			viewWidth = viewHeight * aspectRatio;
		}
		else
		{
			viewHeight = viewWidth / aspectRatio;
		}
		glOrtho(-viewWidth * 0.2, viewWidth * 0.2, -viewHeight * 0.2, viewHeight * 0.2, -1.0, 1.0);
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
