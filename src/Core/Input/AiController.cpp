//
// Created by Gegel85 on 16/04/2020.
//

#include "AiController.hpp"

#include <utility>
#include "../ExternalCode/ExternalModuleFactory.hpp"
#include "../Utils/Utils.hpp"

namespace TouhouFanGame::Inputs
{
	AIController::AIController(Map &map, ECS::Core &core) :
		_map(map),
		_core(core),
		_modulePath(""),
		_lastActions(NB_OF_ACTION),
		_handler(nullptr)
	{
	}

	AIController::AIController(const std::string &modulePath, Map &map, ECS::Core &core) :
		_map(map),
		_core(core),
		_modulePath(modulePath),
		_lastActions(NB_OF_ACTION),
		_handler(ExternalModuleFactory::build(modulePath))
	{
	}

	bool AIController::changeKeyFor(Input::Action)
	{
		return true;
	}

	void AIController::cancelChangeKey()
	{
	}

	std::optional<Input::Event> AIController::pollEvent()
	{
		return {};
	}

	bool AIController::actionPressed(Input::Action action) const
	{
		return this->_lastActions[action];
	}

	void AIController::handleEvent(sf::Event)
	{
	}

	std::vector<Input::Action> AIController::getActions()
	{
		auto res = Utils::callExternalModule<AIResponse>(*this->_handler, "getAIActions", *this->_me.lock(), this->_core, this->_map);

		for (auto && action : this->_lastActions)
			action = false;
		this->_lastAngle = res.direction;
		for (auto a : res.actions)
			this->_lastActions[a] = true;
		return res.actions;
	}

	double AIController::getDirectionAngle() const
	{
		return this->_lastAngle;
	}

	void AIController::unserialize(std::istream &stream)
	{
		stream >> this->_modulePath;
		this->_handler.reset(ExternalModuleFactory::build(this->_modulePath));
	}

	void AIController::serialize(std::ostream &stream) const
	{
		if (!this->_handler)
			throw InvalidStateException("This AI doesn't have a loaded module.");
		stream << this->_modulePath;
	}

	std::string AIController::getEnumControlString(Input::Action)
	{
		return "AI";
	}

	void AIController::setMe(std::weak_ptr<ECS::Entity> me)
	{
		this->_me = std::move(me);
	}

	void AIController::changeModule(const std::string &path)
	{
		this->_handler.reset(ExternalModuleFactory::build(path));
		this->_modulePath = path;
	}

	std::string AIController::getModulePath() const
	{
		return this->_modulePath;
	}
}