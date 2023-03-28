#pragma once

#include <GLFW/glfw3.h>

#include <functional>

using GlfwKeyCallback = std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
using GlfwCursorPosCallback = std::function<void(GLFWwindow* window, double xpos, double ypos)>;
using GlfwMouseButtonCallback = std::function<void(GLFWwindow* window, int button, int action, int mods)>;
