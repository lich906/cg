#pragma once

#include <string>

struct IMenuController
{
	virtual ~IMenuController() = default;

	virtual void OnFileOpen(const std::string& filePath) = 0;
	virtual void OnFileClose() = 0;
};
