#pragma once

#include "pch.h"

#include "core/Layer.h"

namespace core
{

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* overlay);

	std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
	std::vector<Layer*>::iterator end() { return m_layers.end(); }
private:
	std::vector<Layer*> m_layers;
	uint32_t m_layerInsertIndex = 0;
};

} // namespace core
