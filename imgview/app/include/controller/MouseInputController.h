#pragma once

#include <optional>

#include "view/IMouseInputController.h"
#include "model/Document.h"

class MouseInputController : public IMouseInputController
{
public:
	MouseInputController(const std::shared_ptr<Document>& doc);

private:

// Inherited via IMouseInputController
	virtual void OnMouseDown(const glm::vec2& cursorPos) override;
	virtual void OnMouseUp(const glm::vec2& cursorPos) override;
	virtual void OnMouseMove(const glm::vec2& cursorPos, const glm::vec2& delta) override;
	virtual void OnScrollUp(const glm::vec2& cursorPos) override;
	virtual void OnScrollDown(const glm::vec2& cursorPos) override;

	void RefreshSelection(const glm::vec2& pos);
	bool IsSelected();

	std::shared_ptr<Document> m_document;
	bool m_dragging;
	glm::vec2 m_lastCursorPos;
	ImageObject* m_selectedImageObject;
};
