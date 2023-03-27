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
	virtual void OnMouseDown(const gfx::Vector& cursorPos) override;
	virtual void OnMouseUp(const gfx::Vector& cursorPos) override;
	virtual void OnMouseMove(const gfx::Vector& cursorPos, const gfx::Vector& delta) override;
	virtual void OnScrollUp(const gfx::Vector& cursorPos) override;
	virtual void OnScrollDown(const gfx::Vector& cursorPos) override;

	void RefreshSelection(const gfx::Vector& pos);
	bool IsSelected();

	std::shared_ptr<Document> m_document;
	bool m_dragging;
	gfx::Vector m_lastCursorPos;
	ImageObject* m_selectedImageObject;
};
