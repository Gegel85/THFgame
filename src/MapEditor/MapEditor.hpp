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
		Map _map;
		Game _game;
		sf::Font _font;
		unsigned _loaded;
		std::unique_ptr<tgui::Gui> _gui;

		void _makeAllWidgets();
		void _displaySettings();
	public:
		MapEditor();
		void setup();
		int run();
	};
}


#endif //THFGAME_MAPEDITOR_HPP
