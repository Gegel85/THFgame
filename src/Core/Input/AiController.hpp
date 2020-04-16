//
// Created by Gegel85 on 16/04/2020.
//

#ifndef THFGAME_AICONTROLLER_HPP
#define THFGAME_AICONTROLLER_HPP


#include "Input.hpp"
#include "../ExternalCode/ExternalModule.hpp"
#include "../ECS/Core.hpp"
#include "../Resources/Map.hpp"

namespace TouhouFanGame::Inputs
{
	class AIController : public Input {
	private:
		Map &_map;
		ECS::Core &_core;
		std::string _modulePath;
		float _lastAngle = 0;
		std::vector<bool> _lastActions;
		std::unique_ptr<ExternalModule> _handler;

	public:
		struct AIResponse {
			float direction;
			std::vector<Action> actions;
		};

		AIController(Map &map, ECS::Core &core);
		AIController(const std::string &modulePath, Map &map, ECS::Core &core);
		bool changeKeyFor(Action action) override;
		void cancelChangeKey() override;
		std::optional<Event> pollEvent() override;
		bool actionPressed(Action action) const override;
		void handleEvent(sf::Event event) override;
		std::vector<Action> getActions() override;
		double getDirectionAngle() const override;
		void unserialize(std::istream &stream) override;
		void serialize(std::ostream &stream) const override;
		std::string getEnumControlString(Action code) override;
	};
}


#endif //THFGAME_AICONTROLLER_HPP
