#pragma once

#include "pch.h"

#include "core/Layer.h"

namespace core
{

class LayerStack
{
public:
	using LayerVector = std::vector<std::shared_ptr<Layer>>;
	using LayerIterator = LayerVector::iterator;

	void PushLayer(const std::shared_ptr<Layer>& layer);
	void PushOverlay(const std::shared_ptr<Layer>& overlay);
	void PopLayer(const std::shared_ptr<Layer>& layer);
	void PopOverlay(const std::shared_ptr<Layer>& overlay);

	LayerIterator begin() { return m_layers.begin(); }
	LayerIterator end() { return m_layers.end(); }

private:
	LayerVector m_layers;
	uint32_t m_layerInsertIndex = 0;
};

} // namespace core
