//
// Created by Gegel85 on 22/12/2019.
//

#include "InventoryMenu.hpp"
#include "../../Core/ECS/Components/InventoryComponent.hpp"

namespace TouhouFanGame
{
	InventoryMenu::InventoryMenu(MenuMgr &menu, Game &game, Map &map, Rendering::HUD &hud, Rendering::Screen &screen, std::map<std::string, sf::Texture> &textures) :
		_map(map),
		_game(game),
		_menu(menu),
		_hud(hud),
		_screen(screen),
		_textures(textures)
	{
		this->_triangle.setPoint(0, Vector2f(0, 0));
		this->_triangle.setPoint(1, Vector2f(15, 10));
		this->_triangle.setPoint(2, Vector2f(0, 20));
		this->_triangle.setFillColor(sf::Color::Black);
		this->_triangle.setOutlineThickness(0);
	}

	void InventoryMenu::render()
	{
		auto player = this->_map.getPlayer();
		auto &inventory = player->getComponent("Inventory").to<ECS::Components::InventoryComponent>();
		auto camera = this->_screen.getCameraCenter();
		auto screenSize = this->_screen.getSize();

		this->_map.render();
		this->_hud.draw(this->_game);
		this->_screen.fillColor({120, 120, 120});
		this->_screen.draw({
			static_cast<int>(camera.x - screenSize.x / 2. + 32),
			static_cast<int>(camera.y - screenSize.y / 2. + 32),
			static_cast<int>(screenSize.x) - 64,
			static_cast<int>(screenSize.y) - 64
		});
		this->_screen.textSize(16);
		this->_screen.fillColor();

		for (size_t i = 0; i < inventory.items.size(); i++) {
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

		if (!inventory.items.empty()) {
			this->_triangle.setPosition(camera.x - screenSize.x / 2.f + 40, camera.y - screenSize.y / 2.f + 48 + this->_selectedEntry * 32.f);
			static_cast<sf::RenderWindow &>(this->_screen).draw(this->_triangle);
		}
	}

	void InventoryMenu::switched(bool)
	{
		this->_selectedEntry = 0;
	}

	void InventoryMenu::handleEvent(const TouhouFanGame::Input::Event &event)
	{
		auto player = this->_map.getPlayer();
		auto &inventory = player->getComponent("Inventory").to<ECS::Components::InventoryComponent>();

		if (event.type == Input::Event::EVENT_TRIGGERED) {
			switch (event.action) {
			case Input::INVENTORY:
				this->_menu.changeMenu("in_game");
				break;
			case Input::DOWN:
				this->_selectedEntry += 1;
				this->_selectedEntry %= inventory.items.size() ?: 1;
				break;
			case Input::UP:
				if (this->_selectedEntry)
					this->_selectedEntry -= 1;
				else
					this->_selectedEntry = inventory.items.size() - 1;
				break;
			case Input::INTERACT:
				if (!inventory.items.empty()) {
					inventory.items[this->_selectedEntry]->use(*player);
					inventory.items.erase(inventory.items.begin() + this->_selectedEntry);
					if (this->_selectedEntry == inventory.items.size() && !inventory.items.empty())
						this->_selectedEntry--;
					this->_map.getECSCore().getSystemByName("PlayerHUD").updateEntity(player);
				}
				break;
			default:
				break;
			}
		}
	}
}