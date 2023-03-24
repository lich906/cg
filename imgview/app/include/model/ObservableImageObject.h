#pragma once

#include "IObservableImageObject.h"

class ObservableImageObject : public IObservableImageObject
{
public:
	// Inherited via IObservableImageObject
	void SubscribeOnTransform(IImageObjectObserver* observerPtr, bool instantNotify) override;

protected:
	void TransformMatrixChanged();

private:
	virtual glm::mat4 GetTransformMatrix() = 0;
	void Notify();

	IImageObjectObserver* m_observer;
};
