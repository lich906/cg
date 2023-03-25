#include "controller/MouseInputController.h"

MouseInputController::MouseInputController(const std::shared_ptr<Document>& doc)
	: m_document(doc)
	, m_dragging(false)
	, m_selectedImageObject(nullptr)
{
}

void MouseInputController::OnMouseDown(const Vector& cursorPos)
{
	if (!m_dragging && (m_selectedImageObject = m_document->FindObjectAtPos(cursorPos)))
	{
		m_dragging = true;
		m_lastCursorPos = cursorPos;
	}
}

void MouseInputController::OnMouseUp(const Vector& cursorPos)
{
	if (m_dragging)
	{
		m_dragging = false;
	}
}

void MouseInputController::OnMouseMove(const Vector& cursorPos, const Vector& delta)
{
	if (m_dragging && IsSelected())
	{
		m_selectedImageObject->Drag(delta);
	}

	RefreshSelection(cursorPos);
}

void MouseInputController::OnScrollUp(const Vector& cursorPos)
{
	if (IsSelected())
	{
		m_selectedImageObject->ZoomIn();
		RefreshSelection(cursorPos);
	}
}

void MouseInputController::OnScrollDown(const Vector& cursorPos)
{
	if (IsSelected())
	{
		m_selectedImageObject->ZoomOut();
		RefreshSelection(cursorPos);
	}
}

void MouseInputController::RefreshSelection(const Vector& pos)
{
	m_selectedImageObject = m_document->FindObjectAtPos(pos);
}

bool MouseInputController::IsSelected()
{
	return static_cast<bool>(m_selectedImageObject);
}
