#pragma once

#include <memory>

#include "view/Scene.h"
#include "view/IMenuController.h"
#include "model/Document.h"

class MenuController : public IMenuController
{
public:
	MenuController(const std::shared_ptr<Document>& doc, const std::shared_ptr<Scene>& scene);

private:
	// Inherited via IMenuController
	virtual void OnFileOpen(const std::string& filePath) override;
	virtual void OnFileClose() override;

	std::shared_ptr<Document> m_document;
	std::shared_ptr<Scene> m_scene;
};
