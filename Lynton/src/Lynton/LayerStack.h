#pragma once

#include "Lynton/Core.h"
#include "Layer.h"

#include <vector>

namespace Lynton
{

	class LYNTON_API LayerStack
	{
	private:
		std::vector<Layer*> m_layers;
		std::vector<Layer*>::iterator m_layer_insert;
	public:
		LayerStack();
		~LayerStack();

		void push_layer(Layer* layer);
		void push_overerlay(Layer* overlay);
		void pop_layer(Layer* layer);
		void pop_over_layer(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }
	};

}