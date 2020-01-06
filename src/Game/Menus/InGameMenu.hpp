//
// Created by Gegel85 on 22/12/2019.
//

#ifndef THFGAME_INGAMEMENU_HPP
#define THFGAME_INGAMEMENU_HPP


#include "../../Core/Menus/Menu.hpp"
#include "../../Core/Map.hpp"
#include "../../Core/Rendering/Hud.hpp"
#include "../../Core/Menus/MenuMgr.hpp"

namespace TouhouFanGame
{
	class InGameMenu : public Menu {
	private:
		Map &_map;
		Game &_game;
		MenuMgr &_menu;
		Rendering::HUD &_hud;
		Rendering::Screen &_screen;

	public:
		InGameMenu(MenuMgr &menu, Game &game, Map &map, Rendering::HUD &hud, Rendering::Screen &screen);
		void render() override;
		void switched(bool isActive) override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //THFGAME_INGAMEMENU_HPP
