//
// Created by Gegel85 on 28/09/2019.
//

#ifndef THFGAME_KEYBOARD_HPP
#define THFGAME_KEYBOARD_HPP


#include <map>
#include <vector>
#include <optional>
#include <SFML/Window/Keyboard.hpp>
#include "../Input.hpp"

namespace TouhouFanGame::Inputs
{
	//! @brief An input method using the keyboard
	class Keyboard : public Input {
	private:
		//! @brief Used to know if the key has just been changed or not
		bool	_keyChanged = false;

		//! @brief The action that has been requested to change
		std::optional<Action>	_keyChanging;

		//! @brief The keys choose
		std::vector<sf::Keyboard::Key>	_keys;

		//! @brief The reference window
		sf::RenderWindow	*_window;

		//! @brief Maps an sf::Keyboard to the string representing the key
		static const std::map<sf::Keyboard::Key, std::string>	_keysToString;
	public:
		//! @param window The reference window (if any)
		Keyboard(sf::RenderWindow *window);
		bool changeKeyFor(Action) override;
		void cancelChangeKey() override;
		bool actionPressed(Action) override;
		void handleEvent(sf::Event) override;
		//! @note If the reference window (if any) doesn't have foxus, all key presses are ignored
		std::vector<Action> getActions() override;
		void unserialize(std::istream &) override;
		void serialize(std::ostream &) const override;
		std::string getEnumControlString(Action code) override;
	};
}


#endif //THFGAME_KEYBOARD_HPP
