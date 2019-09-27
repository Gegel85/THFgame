//
// Created by Gegel85 on 27/09/2019.
//

#include "Component.hpp"

namespace TouhouFanGame::ECS
{
	Component::Component(const std::string &name) :
		_name(name)
	{
	}

	std::string Component::getName() const
	{
		return this->_name;
	}
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Component &component)
{
	component.serialize(stream);
	return stream;
}

std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Component &component)
{
	component.unserialize(stream);
	return stream;
}