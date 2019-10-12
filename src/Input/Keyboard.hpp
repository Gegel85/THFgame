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
	class Keyboard : public Input {
	private:
		bool				_keyChanged = false;
		std::optional<Action>		_keyChanging;
		std::vector<sf::Keyboard::Key>	_keys;
		sf::RenderWindow		*_window;

		static const std::map<sf::Keyboard::Key, std::string>	_keysToString;
	public:
		Keyboard(sf::RenderWindow *window);
		bool changeKeyFor(Action) override;
		bool actionPressed(Action) override;
		void handleEvent(sf::Event) override;
		std::vector<Action> getActions() override;
		void unserialize(std::istream &) override;
		void serialize(std::ostream &) const override;
		std::string getEnumControlString(Action code) override;
	};
}


#endif //THFGAME_KEYBOARD_HPP
