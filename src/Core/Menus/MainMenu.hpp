//
// Created by Gegel85 on 22/12/2019.
//

#ifndef THFGAME_MAINMENU_HPP
#define THFGAME_MAINMENU_HPP


#include "Menu.hpp"
#include "MenuMgr.hpp"
#include "../Resources.hpp"
#include "../Map.hpp"
#include "../Rendering/Hud.hpp"

namespace TouhouFanGame
{
	class MainMenu : public Menu {
	private:
		Map &_map;
		MenuMgr &_menu;
		Resources &_resources;
		Rendering::HUD &_hud;

	public:
		MainMenu(MenuMgr &menu, Map &map, Resources &resources, Rendering::HUD &hud);
		void render() override;
		void switched(bool isActive) override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //THFGAME_MAINMENU_HPP
