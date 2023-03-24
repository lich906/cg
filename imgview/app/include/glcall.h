#pragma once

#include <iostream>

#include "glad_glfw.h"

#if _DEBUG

	#define GlCall(x) GlClearError(); \
		x; \
		if (!GlLogCall(#x, __FILE__, __LINE__)) \
			__debugbreak()

	static void GlClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	static bool GlLogCall(const char* function, const char* file, int line)
	{
		while (GLenum errCode = glGetError())
		{
			std::cout << "[OpenGL Error] (0x0" << std::hex << errCode << std::dec << "): "
				<< function << " " << file << ":" << line << std::endl;
			return false;
		}
		return true;
	}

#else

	#define GlCall(x) x

#endif
