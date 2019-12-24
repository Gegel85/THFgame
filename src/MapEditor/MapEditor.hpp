//
// Created by Gegel85 on 23/12/2019.
//

#ifndef THFGAME_MAPEDITOR_HPP
#define THFGAME_MAPEDITOR_HPP


#include <TGUI/Gui.hpp>
#include "../Core/Game.hpp"

namespace TouhouFanGame
{
	class MapEditor {
	private:
		Game _game;
		sf::Font _font;
		std::unique_ptr<tgui::Gui> _gui;

	public:
		MapEditor() = default;
		void setup();
		int run();
	};
}


#endif //THFGAME_MAPEDITOR_HPP
