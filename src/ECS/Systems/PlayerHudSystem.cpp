//
// Created by Gegel85 on 18/11/2019.
//

#include "PlayerHudSystem.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ManaComponent.hpp"
#include "../Components/PlayerHudComponent.hpp"
#include "../Components/NameComponent.hpp"

namespace TouhouFanGame::ECS::Systems
{
	PlayerHUDSystem::PlayerHUDSystem(TouhouFanGame::ECS::Core &core) :
		System(core, "PlayerHUD", {"Name", "Mana", "Health"})
	{}

	void PlayerHUDSystem::updateEntity(TouhouFanGame::ECS::Entity &entity)
	{
		auto &health = entity.getComponent("Health").to<Components::HealthComponent>();
		auto &mana = entity.getComponent("Mana").to<Components::ManaComponent>();
		auto &name = entity.getComponent("Name").to<Components::NameComponent>();
		auto &hud = entity.getComponent("PlayerHUD").to<Components::PlayerHUDComponent>();
		auto camera = hud.screen.getCameraCenter();
		auto screenSize = hud.screen.getSize();

		hud.screen.fillColor(sf::Color{120, 120, 120});
		hud.screen.textSize(15);
		hud.screen.draw(name.name, {
			camera.x - screenSize.x / 2.f + 5,
			camera.y + screenSize.y / 2.f - 53,
		});

		hud.screen.fillColor(sf::Color{120, 120, 120});
		hud.screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 5),
			static_cast<int>(camera.y + screenSize.y / 2. - 35),
			210,
			30
		});
		hud.screen.draw(sf::IntRect{
			static_cast<int>(camera.x + screenSize.x / 2. - 215),
			static_cast<int>(camera.y + screenSize.y / 2. - 35),
			210,
			30
		});

		hud.screen.fillColor(sf::Color{255, 0, 0});
		hud.screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 10),
			static_cast<int>(camera.y + screenSize.y / 2. - 30),
			static_cast<int>(health.health * 200 / health.maxHealth),
			20
		});
		hud.screen.fillColor(sf::Color{200, 200, 255});
		hud.screen.draw(sf::IntRect{
			static_cast<int>(camera.x + screenSize.x / 2. - 210),
			static_cast<int>(camera.y + screenSize.y / 2. - 30),
			static_cast<int>(mana.mana * 200 / mana.maxMana),
			20
		});

		hud.screen.fillColor(sf::Color{255, 255, 255});
	}
}