#include "model/Document.h"

void Document::AddImageObject(const ImageObject& imageObject)
{
	m_imageObject = imageObject;
}

void Document::RemoveImageObject()
{
	m_imageObject.reset();
}

ImageObject* Document::FindObjectAtPos(const gfx::Vector& pos)
{
	if (m_imageObject && m_imageObject->ExistsAtPos(pos))
	{
		return &*m_imageObject;
	}

	return nullptr;
}
