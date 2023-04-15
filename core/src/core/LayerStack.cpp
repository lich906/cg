#include "pch.h"

#include "core/LayerStack.h"

namespace core
{

void LayerStack::PushLayer(const std::shared_ptr<Layer>& layer)
{
	m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
	m_layerInsertIndex++;
	layer->OnAttach();
}

void LayerStack::PushOverlay(const std::shared_ptr<Layer>& overlay)
{
	m_layers.emplace_back(overlay);
	overlay->OnAttach();
}

void LayerStack::PopLayer(const std::shared_ptr<Layer>& layer)
{
	auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
	if (it != m_layers.begin() + m_layerInsertIndex)
	{
		layer->OnDetach();
		m_layers.erase(it);
		m_layerInsertIndex--;
	}
}

void LayerStack::PopOverlay(const std::shared_ptr<Layer>& overlay)
{
	auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);
	if (it != m_layers.end())
	{
		overlay->OnDetach();
		m_layers.erase(it);
	}
}

} // namespace core
