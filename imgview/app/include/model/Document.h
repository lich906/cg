#pragma once

#include <memory>

#include "ImageObject.h"

class Document
{
public:
	void AddImageObject(std::unique_ptr<ImageObject>&& imageObject);

	void RemoveImageObject();

	std::unique_ptr<ImageObject>& FindObjectAtPos(const Vector& pos);

private:
	std::unique_ptr<ImageObject> m_imageObject;
};
