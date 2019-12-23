//
// Created by Gegel85 on 22/12/2019.
//

#ifndef THFGAME_INVENTORYMENU_HPP
#define THFGAME_INVENTORYMENU_HPP


#include "../../Core/Menus/Menu.hpp"
#include "../../Core/Menus/MenuMgr.hpp"
#include "../../Core/Rendering/Hud.hpp"
#include "../../Core/Map.hpp"

namespace TouhouFanGame
{
	class InventoryMenu : public Menu {
	private:
		Map &_map;
		MenuMgr &_menu;
		Rendering::HUD &_hud;
		Rendering::Screen &_screen;
		std::map<std::string, sf::Texture> &_textures;

	public:
		InventoryMenu(MenuMgr &menu, Map &map, Rendering::HUD &hud, Rendering::Screen &screen, std::map<std::string, sf::Texture> &textures);
		void render() override;
		void switched(bool isActive) override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //THFGAME_INVENTORYMENU_HPP
