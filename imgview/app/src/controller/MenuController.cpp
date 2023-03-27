#include "controller/MenuController.h"

MenuController::MenuController(const std::shared_ptr<Document>& doc, const std::shared_ptr<Scene>& scene)
	: m_document(doc)
	, m_scene(scene)
{
}

void MenuController::OnFileOpen(const std::string& filePath)
{
	gfx::Texture texture(filePath, GL_CLAMP_TO_EDGE, config::TextureFilteringMode);

	ImageObject imageObject(texture.GetWidth(), texture.GetHeight());
	auto imageObjectView = std::make_unique<ImageObjectView>(texture);
	imageObject.SubscribeOnTransform(imageObjectView.get(), true);

	m_document->AddImageObject(imageObject);
	m_scene->AddImageObjectView(std::move(imageObjectView));
}

void MenuController::OnFileClose()
{
	m_document->RemoveImageObject();
	m_scene->RemoveImageObjectView();
}
