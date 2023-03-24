#include "controller/MenuController.h"

MenuController::MenuController(const std::shared_ptr<Document>& doc, const std::shared_ptr<Scene>& scene)
	: m_document(doc)
	, m_scene(scene)
{
}

void MenuController::OnFileOpen(const std::string& filePath)
try
{
	Texture texture(filePath);

	auto imageObject = std::make_unique<ImageObject>(texture.GetWidth(), texture.GetHeight());
	auto imageObjectView = std::make_unique<ImageObjectView>(std::move(texture));
	imageObject->SubscribeOnTransform(imageObjectView.get(), true);

	m_document->AddImageObject(std::move(imageObject));
	m_scene->AddImageObjectView(std::move(imageObjectView));
}
catch (std::exception& e)
{
	printf("%s\n", e.what());
}

void MenuController::OnFileClose()
{
	m_document->RemoveImageObject();
	m_scene->RemoveImageObjectView();
}
