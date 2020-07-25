#include "lypch.h"
#include "LayerStack.h"

namespace Lynton
{

	LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        // layers are intended to live through the lifetime of the application
        for (Layer* layer : m_layers)
            delete layer;
    }

    void LayerStack::push_layer(Layer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_layer_insert_index, layer);
        m_layer_insert_index++;
    }

    void LayerStack::push_overlay(Layer* overlay)
    {
        // overlays are always after (other) layers
        m_layers.emplace_back(overlay);
    }

    void LayerStack::pop_layer(Layer* layer)
    {
        auto iterator = std::find(m_layers.begin(), m_layers.end(), layer);
        if (iterator != m_layers.end())
        {
            m_layers.erase(iterator);
            m_layer_insert_index--;
        }
    }

    void LayerStack::pop_over_layer(Layer* overlay)
    {
        auto iterator = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (iterator != m_layers.end())
            m_layers.erase(iterator);
    }

}
