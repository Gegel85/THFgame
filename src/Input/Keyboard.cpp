//
// Created by Gegel85 on 28/09/2019.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Keyboard.hpp"

namespace TouhouFanGame::Inputs
{
	const std::map<sf::Keyboard::Key, std::string> Keyboard::_keysToString{
		{sf::Keyboard::Unknown,   "Unknown"},
		{sf::Keyboard::A,         "A"},
		{sf::Keyboard::B,         "B"},
		{sf::Keyboard::C,         "C"},
		{sf::Keyboard::D,         "D"},
		{sf::Keyboard::E,         "E"},
		{sf::Keyboard::F,         "F"},
		{sf::Keyboard::G,         "G"},
		{sf::Keyboard::H,         "H"},
		{sf::Keyboard::I,         "I"},
		{sf::Keyboard::J,         "J"},
		{sf::Keyboard::K,         "K"},
		{sf::Keyboard::L,         "L"},
		{sf::Keyboard::M,         "M"},
		{sf::Keyboard::N,         "N"},
		{sf::Keyboard::O,         "O"},
		{sf::Keyboard::P,         "P"},
		{sf::Keyboard::Q,         "Q"},
		{sf::Keyboard::R,         "R"},
		{sf::Keyboard::S,         "S"},
		{sf::Keyboard::T,         "T"},
		{sf::Keyboard::U,         "U"},
		{sf::Keyboard::V,         "V"},
		{sf::Keyboard::W,         "W"},
		{sf::Keyboard::X,         "X"},
		{sf::Keyboard::Y,         "Y"},
		{sf::Keyboard::Z,         "Z"},
		{sf::Keyboard::Num0,      "0"},
		{sf::Keyboard::Num1,      "1"},
		{sf::Keyboard::Num2,      "2"},
		{sf::Keyboard::Num3,      "3"},
		{sf::Keyboard::Num4,      "4"},
		{sf::Keyboard::Num5,      "5"},
		{sf::Keyboard::Num6,      "6"},
		{sf::Keyboard::Num7,      "7"},
		{sf::Keyboard::Num8,      "8"},
		{sf::Keyboard::Num9,      "9"},
		{sf::Keyboard::Escape,    "Escape"},
		{sf::Keyboard::LControl,  "LCtrl"},
		{sf::Keyboard::LShift,    "LShift"},
		{sf::Keyboard::LAlt,      "LAlt"},
		{sf::Keyboard::LSystem,   "LSys"},
		{sf::Keyboard::RControl,  "RCtrl"},
		{sf::Keyboard::RShift,    "RShift"},
		{sf::Keyboard::RAlt,      "RAlt"},
		{sf::Keyboard::RSystem,   "RSys"},
		{sf::Keyboard::Menu,      "Menu"},
		{sf::Keyboard::LBracket,  "["},
		{sf::Keyboard::RBracket,  "]"},
		{sf::Keyboard::SemiColon, ";"},
		{sf::Keyboard::Comma,     ","},
		{sf::Keyboard::Period,    "."},
		{sf::Keyboard::Quote,     "'"},
		{sf::Keyboard::Slash,     "/"},
		{sf::Keyboard::BackSlash, "\\"},
		{sf::Keyboard::Tilde,     "~"},
		{sf::Keyboard::Equal,     "="},
		{sf::Keyboard::Dash,      "-"},
		{sf::Keyboard::Space,     "Space"},
		{sf::Keyboard::Return,    "Enter"},
		{sf::Keyboard::BackSpace, "Backspace"},
		{sf::Keyboard::Tab,       "Tab"},
		{sf::Keyboard::PageUp,    "PgUp"},
		{sf::Keyboard::PageDown,  "PgDown"},
		{sf::Keyboard::End,       "End"},
		{sf::Keyboard::Home,      "Home"},
		{sf::Keyboard::Insert,    "Insert"},
		{sf::Keyboard::Delete,    "Del"},
		{sf::Keyboard::Add,       "+"},
		{sf::Keyboard::Subtract,  "-"},
		{sf::Keyboard::Multiply,  "*"},
		{sf::Keyboard::Divide,    "/"},
		{sf::Keyboard::Left,      "Left Arrow"},
		{sf::Keyboard::Right,     "Right Arrow"},
		{sf::Keyboard::Up,        "Up Arrow"},
		{sf::Keyboard::Down,      "Down Arrow"},
		{sf::Keyboard::Numpad0,   "Num0"},
		{sf::Keyboard::Numpad1,   "Num1"},
		{sf::Keyboard::Numpad2,   "Num2"},
		{sf::Keyboard::Numpad3,   "Num3"},
		{sf::Keyboard::Numpad4,   "Num4"},
		{sf::Keyboard::Numpad5,   "Num5"},
		{sf::Keyboard::Numpad6,   "Num6"},
		{sf::Keyboard::Numpad7,   "Num7"},
		{sf::Keyboard::Numpad8,   "Num8"},
		{sf::Keyboard::Numpad9,   "Num9"},
		{sf::Keyboard::F1,        "F1"},
		{sf::Keyboard::F2,        "F2"},
		{sf::Keyboard::F3,        "F3"},
		{sf::Keyboard::F4,        "F4"},
		{sf::Keyboard::F5,        "F5"},
		{sf::Keyboard::F6,        "F6"},
		{sf::Keyboard::F7,        "F7"},
		{sf::Keyboard::F8,        "F8"},
		{sf::Keyboard::F9,        "F9"},
		{sf::Keyboard::F10,       "F10"},
		{sf::Keyboard::F11,       "F11"},
		{sf::Keyboard::F12,       "F12"},
		{sf::Keyboard::F13,       "F13"},
		{sf::Keyboard::F14,       "F14"},
		{sf::Keyboard::F15,       "F15"},
		{sf::Keyboard::Pause,     "Pause"},
	};

	Keyboard::Keyboard(sf::RenderWindow *window) :
		_keys{
			sf::Keyboard::Z,
			sf::Keyboard::D,
			sf::Keyboard::S,
			sf::Keyboard::Q,
			sf::Keyboard::LShift,
			sf::Keyboard::Space,
			sf::Keyboard::F,
			sf::Keyboard::E,
			sf::Keyboard::Escape
		},
		_window(window)
	{}

	void Keyboard::handleEvent(sf::Event event)
	{
		if (this->_keyChanging && event.type == sf::Event::KeyPressed) {
			this->_keys[*this->_keyChanging] = event.key.code;
			this->_keyChanging.reset();
			this->_keyChanged = true;
		}
	}

	bool Keyboard::actionPressed(Action action)
	{
		return sf::Keyboard::isKeyPressed(this->_keys[action]);
	}

	bool Keyboard::changeKeyFor(Action action)
	{
		if (this->_keyChanged) {
			this->_keyChanged = false;
			return true;
		}
		if (!this->_keyChanging)
			this->_keyChanging = action;
		return false;
	}

	void Keyboard::cancelChangeKey()
	{
		this->_keyChanged = false;
		this->_keyChanging.reset();
	}

	std::vector<TouhouFanGame::Input::Action> Keyboard::getActions()
	{
		std::vector<Action> actions;

		if (this->_window && !this->_window->hasFocus())
			return {};

		for (Action i = UP; i < NB_OF_ACTION; i = static_cast<Action>(i + 1))
			if (this->actionPressed(i))
				actions.push_back(i);
		return actions;
	}

	std::string Keyboard::getEnumControlString(TouhouFanGame::Input::Action code)
	{
		return _keysToString.at(this->_keys[code]);
	}

	void Keyboard::serialize(std::ostream &) const
	{}

	void Keyboard::unserialize(std::istream &)
	{}
}
