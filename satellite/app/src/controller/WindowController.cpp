#include "controller/WindowController.h"

WindowController::WindowController(UniverseModel& model, UniverseViewModel& viewModel, IControllableWindow* window)
	: m_model(model)
	, m_viewModel(viewModel)
	, m_window(window)
{
}
