//
// Created by Gegel85 on 22/12/2019.
//

#include "InventoryMenu.hpp"
#include "../../Core/ECS/Components/InventoryComponent.hpp"

namespace TouhouFanGame
{
	InventoryMenu::InventoryMenu(MenuMgr &menu, Map &map, Rendering::HUD &hud, Rendering::Screen &screen, std::map<std::string, sf::Texture> &textures) :
		_map(map),
		_menu(menu),
		_hud(hud),
		_screen(screen),
		_textures(textures)
	{
	}

	void InventoryMenu::render()
	{
		auto &player = this->_map.getPlayer();
		auto &inventory = player.getComponent("Inventory").to<ECS::Components::InventoryComponent>();
		auto camera = this->_screen.getCameraCenter();
		auto screenSize = this->_screen.getSize();

		this->_map.render();
		this->_hud.draw(this->_screen);
		this->_screen.fillColor({120, 120, 120});
		this->_screen.draw({
			static_cast<int>(camera.x - screenSize.x / 2. + 32),
			static_cast<int>(camera.y - screenSize.y / 2. + 32),
			static_cast<int>(screenSize.x) - 64,
			static_cast<int>(screenSize.y) - 64
		});
		this->_screen.textSize(16);
		this->_screen.fillColor();

		for (unsigned i = 0; i < inventory.items.size(); i++) {
			auto &item = inventory.items[i];

			try {
				this->_screen.draw(
					this->_textures.at(item->getTexture()),
					{camera.x - screenSize.x / 2.f + 60, camera.y - screenSize.y / 2.f + 40 + i * 32.f}
				);
			} catch (std::out_of_range &) {}
			this->_screen.draw(
				item->getName(),
				{
					camera.x - screenSize.x / 2.f + 90,
					camera.y - screenSize.y / 2.f + 48 + i * 32.f
				}
			);
		}
	}

	void InventoryMenu::switched(bool)
	{}

	void InventoryMenu::handleEvent(const TouhouFanGame::Input::Event &event)
	{
		if (event.type == Input::Event::EVENT_TRIGGERED) {
			switch (event.action) {
			case Input::INVENTORY:
				this->_menu.changeMenu("in_game");
				break;
			default:
				break;
			}
		}
	}
}