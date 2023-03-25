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
	virtual void OnMouseDown(const Vector& cursorPos) override;
	virtual void OnMouseUp(const Vector& cursorPos) override;
	virtual void OnMouseMove(const Vector& cursorPos, const Vector& delta) override;
	virtual void OnScrollUp(const Vector& cursorPos) override;
	virtual void OnScrollDown(const Vector& cursorPos) override;

	void RefreshSelection(const Vector& pos);
	bool IsSelected();

	std::shared_ptr<Document> m_document;
	bool m_dragging;
	Vector m_lastCursorPos;
	ImageObject* m_selectedImageObject;
};
