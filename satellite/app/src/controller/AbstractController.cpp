#include "controller/AbstractController.h"

AbstractController::AbstractController(IWindowContext* context)
	: m_context(context)
{
}

IWindowContext* AbstractController::GetContext()
{
	return m_context;
}
