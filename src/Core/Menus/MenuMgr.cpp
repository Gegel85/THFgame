//
// Created by Gegel85 on 25/09/2019.
//

#include <iostream>
#include "MenuMgr.hpp"
#include "../Game.hpp"
#include "../ECS/Components/PositionComponent.hpp"
#include "../ECS/Components/InventoryComponent.hpp"

namespace TouhouFanGame
{
	void MenuMgr::handleEvent(const Input::Event &event)
	{
		if (!this->_currentMenu.empty())
			this->_menus.at(this->_currentMenu)->handleEvent(event);
	}

	void MenuMgr::renderMenu()
	{
		if (!this->_currentMenu.empty())
			this->_menus.at(this->_currentMenu)->render();
	}

	void MenuMgr::changeMenu(const std::string &newMenu)
	{
		this->_menus.at(newMenu)->switched(true);
		if (!this->_currentMenu.empty())
			this->_menus.at(this->_currentMenu)->switched(false);
		this->_currentMenu = newMenu;
	}
}