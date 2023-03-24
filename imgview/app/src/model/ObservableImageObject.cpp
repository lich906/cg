#include "model/ObservableImageObject.h"

void ObservableImageObject::SubscribeOnTransform(IImageObjectObserver* observerPtr, bool instantNotify)
{
	m_observer = observerPtr;

	if (instantNotify)
	{
		Notify();
	}
}

void ObservableImageObject::TransformMatrixChanged()
{
	Notify();
}

void ObservableImageObject::Notify()
{
	if (m_observer)
	{
		m_observer->UpdateTransformMatrix(GetTransformMatrix());
	}
}
