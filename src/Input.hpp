//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_INPUT_HPP
#define THFGAME_INPUT_HPP

#include <vector>
#include <string>
#include <SFML/Window/Event.hpp>

namespace TouhouFanGame
{
	class Input {
	public:
		enum Action {
			UP,
			RIGHT,
			DOWN,
			LEFT,
			SPRINT,
			ATTACK,
			INTERACT,
			INVENTORY,
			PAUSE,
			NB_OF_ACTION
		};

		static std::string actionToString(Action action);

		virtual bool changeKeyFor(Action) = 0;
		virtual bool actionPressed(Action) = 0;
		virtual void handleEvent(sf::Event) = 0;
		virtual std::vector<Action> getActions() = 0;
		virtual void unserialize(std::istream &) = 0;
		virtual void serialize(std::ostream &) const = 0;
		virtual std::string getEnumControlString(Action code) = 0;
	};
}


#endif //THFGAME_INPUT_HPP
