//
// Created by Gegel85 on 22/04/2020.
//

#include "ColliderFactory.hpp"
#include "CircleCollider.hpp"
#include "RectangleCollider.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	const std::map<std::string, std::function<ICollider *()>> ColliderFactory::_builders{
		{"Rectangle", []{ return new RectangleCollider(0, 0, 0, 0, 0); }},
		{"Circle",    []{ return new CircleCollider(0, 0, 0); }}
	};
	const std::map<std::string, std::function<ICollider *(std::istream &)>> ColliderFactory::_unserializeBuilders{
		{"Rectangle", [](std::istream &stream){ return new RectangleCollider(stream); }},
		{"Circle",    [](std::istream &stream){ return new CircleCollider(stream); }}
	};

	ICollider *ColliderFactory::build(const std::string &name)
	{
		try {
			return ColliderFactory::_builders.at(name)();
		} catch (std::out_of_range &) {
			throw InvalidColliderException(name + " is not a valid collider shape");
		}
	}

	ICollider *ColliderFactory::build(const std::string &name, std::istream &stream)
	{
		try {
			return ColliderFactory::_unserializeBuilders.at(name)(stream);
		} catch (std::out_of_range &) {
			throw InvalidColliderException(name + " is not a valid collider shape");
		}
	}
}
