#include "model/Document.h"

void Document::AddImageObject(std::unique_ptr<ImageObject>&& imageObject)
{
	m_imageObject = std::move(imageObject);
}

void Document::RemoveImageObject()
{
	m_imageObject = nullptr;
}

std::unique_ptr<ImageObject>& Document::FindObjectAtPos(const Vector& pos)
{
	if (m_imageObject && m_imageObject->ExistsAtPos(pos))
	{
		return m_imageObject;
	}

	return m_nullptr;
}
