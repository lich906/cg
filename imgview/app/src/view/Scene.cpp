#include "view/Scene.h"

void Scene::Draw()
{
	if (m_imageObjectView)
	{
		m_imageObjectView->Draw();
	}
}

void Scene::AddImageObjectView(std::unique_ptr<ImageObjectView>&& imageObjectView)
{
	m_imageObjectView = std::move(imageObjectView);
}

void Scene::RemoveImageObjectView()
{
	m_imageObjectView = nullptr;
}
