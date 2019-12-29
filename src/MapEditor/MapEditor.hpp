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
		struct MapParams {
			sf::Vector2<unsigned short> size;
			bool solid;
			std::string music;
			std::string tilemap;
			unsigned char tilesize;
			MapParams() = default;
			MapParams(const Map &map);
		};

		Map _map;
		Game _game;
		sf::Font _font;
		unsigned _loaded;
		MapParams _params;
		sf::Vector2f _cameraPos;
		std::unique_ptr<tgui::Gui> _gui;

		void _makeAllWidgets();
		void _displaySettings();
		void _renderMap();
		void _resetMap();
		void _showMapEditWindow();
		void _showToolBox();
		void _showNewEntityBox();
		void _showNewTeleporterBox();
		void _showEntityProperties(ECS::Entity &entity);
	public:
		MapEditor();
		~MapEditor();
		void setup();
		int run();
	};
}


#endif //THFGAME_MAPEDITOR_HPP
