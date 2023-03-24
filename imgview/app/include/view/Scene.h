#pragma once

#include <memory>

#include "ImageObjectView.h"

class Scene
{
public:
	void Draw();

	void AddImageObjectView(std::unique_ptr<ImageObjectView>&& imageObjectView);

	void RemoveImageObjectView();

private:
	std::unique_ptr<ImageObjectView> m_imageObjectView;
};
