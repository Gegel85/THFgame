//
// Created by Gegel85 on 18/11/2019.
//

#include "BasicSerializeComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	BasicSerializeComponent::BasicSerializeComponent(const std::string &name) :
		Component(name)
	{}

	void BasicSerializeComponent::serialize(std::ostream &) const
	{}
}