//
// Created by Gegel85 on 16/04/2020.
//

#include <iostream>
#include "CutsceneComponent.hpp"
#include "../../ExternalCode/ExternalModuleFactory.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Components
{
	CutsceneComponent::CutsceneComponent(Game &game, std::istream &stream) :
		Component("Cutscene"),
		game(game)
	{
		stream >> this->_modulePath >> this->triggered;

		if (stream.fail())
			throw InvalidSerializedString("Invalid CutsceneComponent");
		this->handler.reset(ExternalModuleFactory::build(this->_modulePath));
	}

	CutsceneComponent::CutsceneComponent(Game &game, const std::string &modulePath) :
		Component("Cutscene"),
		_modulePath(modulePath),
		game(game)
	{
		this->handler.reset(ExternalModuleFactory::build(modulePath));
	}

	void CutsceneComponent::serialize(std::ostream &stream) const
	{
		stream << this->_modulePath << " " << this->triggered;
	}

	void CutsceneComponent::setModulePath(const std::string &path)
	{
		this->handler.reset(ExternalModuleFactory::build(path));
		this->_modulePath = path;
	}

	std::string CutsceneComponent::getModulePath() const
	{
		return this->_modulePath;
	}
}