#pragma once

#include "Layer.h"

class CLayerStack {
public:
    CLayerStack() = default;
    ~CLayerStack() {
		for (CLayer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}
    }

    void PushLayer(CLayer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
    }

    void PopLayer(CLayer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
    }

    std::vector<CLayer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<CLayer*>::iterator end() { return m_Layers.end(); }
    std::vector<CLayer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
    std::vector<CLayer*>::reverse_iterator rend() { return m_Layers.rend(); }

    std::vector<CLayer*>::const_iterator begin() const { return m_Layers.begin(); }
    std::vector<CLayer*>::const_iterator end()	const { return m_Layers.end(); }
    std::vector<CLayer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
    std::vector<CLayer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
private:
    std::vector<CLayer*> m_Layers;
    unsigned int m_LayerInsertIndex = 0;
};