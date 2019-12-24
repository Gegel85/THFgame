//
// Created by Gegel85 on 22/12/2019.
//

#ifndef THFGAME_MAINMENU_HPP
#define THFGAME_MAINMENU_HPP


#include "../../Core/Menus/Menu.hpp"
#include "../../Core/Menus/MenuMgr.hpp"
#include "../../Core/Resources.hpp"
#include "../../Core/Map.hpp"
#include "../../Core/Rendering/Hud.hpp"

namespace TouhouFanGame
{
	class MainMenu : public Menu {
	private:
		Map &_map;
		MenuMgr &_menu;
		tgui::Gui &_gui;
		Rendering::Screen &_window;

	public:
		MainMenu(MenuMgr &menu, Map &map, tgui::Gui &gui, Rendering::Screen &window);
		void render() override;
		void switched(bool isActive) override;
		void handleEvent(const Input::Event &event) override;
	};
}


#endif //THFGAME_MAINMENU_HPP
