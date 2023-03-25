#pragma once

#include <optional>

#include "ImageObject.h"

class Document
{
public:
	void AddImageObject(const ImageObject& imageObject);

	void RemoveImageObject();

	ImageObject* FindObjectAtPos(const Vector& pos);

private:
	std::optional<ImageObject> m_imageObject;
};
