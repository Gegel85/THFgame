//
// Created by Gegel85 on 23/12/2019.
//

#ifndef THFGAME_MAPEDITOR_HPP
#define THFGAME_MAPEDITOR_HPP


#include <TGUI/TGUI.hpp>
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
			unsigned short links[4];
			MapParams() = default;
			MapParams(const Map &map);
		};

		Map _map;
		Game _game;
		sf::Font _font;
		bool _deleting = false;
		unsigned _loaded;
		MapParams _params;
		sf::Vector2i _startPos;
		sf::Vector2f _cameraPos;
		sf::Vector2f _oldCam;
		unsigned char _pressed = 0;
		unsigned char _selected = 0;
		std::unique_ptr<tgui::Gui> _gui;
		sf::Vector2<std::shared_ptr<tgui::Label>> _posLabels;

		void _makeAllWidgets();
		void _displaySettings();
		void _renderMap();
		void _resetMap();
		void _showMapEditWindow();
		void _showToolBox(bool openWindow = true);
		void _showNewEntityBox();
		void _changeObject(sf::Vector2i pixels);
		void _changeObject(int x, int y);
		void _showNewTeleporterBox(Map::TpTrigger &trigger);
		void _showEntityProperties(const std::shared_ptr<ECS::Entity> &entity);
		void _showAllEntities(bool openWindow = true);
		void _showAllTeleporters(bool openWindow = true);
		void _removeComponentFromEntity(std::shared_ptr<ECS::Entity> entity, const std::string &name);
		void _addComponentToEntity(std::shared_ptr<ECS::Entity> entity, const std::string &name);
	public:
		MapEditor();
		~MapEditor();
		void setup();
		int run();
	};
}


#endif //THFGAME_MAPEDITOR_HPP
