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
	//! @brief An input entity.
	class Input {
	public:
		//! @brief Any action that an Input can trigger.
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

		//! @brief Transforms the Action enumeration into a string.
		//! @param action The value to convert.
		//! @return A string representing the value given.
		static std::string actionToString(Action action);

		//! @brief Put the Input into the "change key" mode if it wasn't already.
		//! @param action The action to change.
		//! @return True if still in "change key" mode. False otherwise.
		virtual bool changeKeyFor(Action action) = 0;

		//! @brief Tell if the action is currently triggered.
		//! @param action The action to check.
		//! @return Whether the action is triggered or not.
		virtual bool actionPressed(Action action) = 0;

		//! @brief Consumes an event.
		virtual void handleEvent(sf::Event) = 0;

		//! @brief Tell all the actions currently triggered.
		//! @return All the action currently triggered.
		virtual std::vector<Action> getActions() = 0;

		//! @brief Unserialize a string.
		//! @param stream to load from.
		virtual void unserialize(std::istream &stream) = 0;

		//! @brief Serialize a string.
		//! @param stream to load to.
		virtual void serialize(std::ostream &stream) const = 0;

		//! @brief Get the key string assigned to this action.
		//! @param code The code to get the key.
		virtual std::string getEnumControlString(Action code) = 0;
	};
}


#endif //THFGAME_INPUT_HPP
