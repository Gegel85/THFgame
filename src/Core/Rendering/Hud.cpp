/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** Hud.cpp
*/

#include "Hud.hpp"
#include "../Game.hpp"

void TouhouFanGame::Rendering::HUD::setBossLife(float bossLife)
{
	this->_bossLife = bossLife;
}

void TouhouFanGame::Rendering::HUD::setPlayerLife(float playerLife)
{
	this->_playerLife = playerLife;
}

void TouhouFanGame::Rendering::HUD::setPlayerMana(float playerMana)
{
	this->_playerMana = playerMana;
}

void TouhouFanGame::Rendering::HUD::setBossName(const std::string &bossName)
{
	this->_bossName = bossName + ": ";
}

void TouhouFanGame::Rendering::HUD::setPlayerName(const std::string &playerName)
{
	this->_playerName = playerName;
}

void TouhouFanGame::Rendering::HUD::setMusicName(const std::string &musicName)
{
	if (this->_musicName == musicName)
		return;
	this->_musicNamePos = 240;
	this->_musicName = musicName;
}

void TouhouFanGame::Rendering::HUD::_renderPlayerHUD(TouhouFanGame::Rendering::Screen &screen)
{
	auto camera = screen.getCameraCenter();
	auto screenSize = screen.getSize();

	screen.fillColor(sf::Color{0, 0, 0});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2.),
		static_cast<int>(camera.y + screenSize.y / 2. - HUD_VERTICAL_SIZE),
		static_cast<int>(screenSize.x),
		HUD_VERTICAL_SIZE
	});

	screen.fillColor(sf::Color{120, 120, 120});
	screen.textSize(15);
	screen.draw(this->_playerName, {
		camera.x - screenSize.x / 2.f + 5,
		camera.y + screenSize.y / 2.f - 53,
	});

	screen.fillColor(sf::Color{200, 200, 200});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 5),
		static_cast<int>(camera.y + screenSize.y / 2. - 35),
		210,
		30
	});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x + screenSize.x / 2. - 215),
		static_cast<int>(camera.y + screenSize.y / 2. - 35),
		210,
		30
	});

	screen.fillColor(sf::Color{50, 50, 50});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 10),
		static_cast<int>(camera.y + screenSize.y / 2. - 30),
		static_cast<int>(200),
		20
	});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x + screenSize.x / 2. - 210),
		static_cast<int>(camera.y + screenSize.y / 2. - 30),
		static_cast<int>(200),
		20
	});

	screen.fillColor(sf::Color{255, 0, 0});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 10),
		static_cast<int>(camera.y + screenSize.y / 2. - 30),
		static_cast<int>(this->_playerLife * 2),
		20
	});
	screen.fillColor(sf::Color{106, 90, 205});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x + screenSize.x / 2. - 210),
		static_cast<int>(camera.y + screenSize.y / 2. - 30),
		static_cast<int>(this->_playerMana * 2),
		20
	});
}

void TouhouFanGame::Rendering::HUD::_renderBossHUD(TouhouFanGame::Rendering::Screen &screen)
{
	auto camera = screen.getCameraCenter();
	auto screenSize = screen.getSize();

	screen.fillColor(sf::Color{0, 0, 0});
	screen.textSize(10);
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2.),
		static_cast<int>(camera.y - screenSize.y / 2.),
		static_cast<int>(screen.getTextWidth(this->_bossName)),
		10
	});

	screen.fillColor(sf::Color{255, 255, 255});
	screen.draw(this->_bossName, {
		camera.x - screenSize.x / 2.f,
		camera.y - screenSize.y / 2.f - 3,
	});

	screen.fillColor(sf::Color{120, 120, 120, 120});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 1 + screen.getTextWidth(this->_bossName)),
		static_cast<int>(camera.y - screenSize.y / 2. + 1),
		static_cast<int>(screenSize.x - 2 - screen.getTextWidth(this->_bossName)),
		5
	});

	screen.fillColor(sf::Color{255, 0, 0, 120});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 2 + screen.getTextWidth(this->_bossName)),
		static_cast<int>(camera.y - screenSize.y / 2. + 2),
		static_cast<int>(this->_bossLife * (screenSize.x - 4 - screen.getTextWidth(this->_bossName)) / 100),
		3
	});
}

void TouhouFanGame::Rendering::HUD::_renderMusic(TouhouFanGame::Rendering::Screen &screen)
{
	auto camera = screen.getCameraCenter();
	auto screenSize = screen.getSize();

	screen.fillColor(sf::Color{120, 120, 120});
	screen.textSize(15);
	if (this->_musicNamePos > 180) {
		screen.draw(this->_musicName, {
			camera.x + screenSize.x / 2.f - screen.getTextWidth(this->_musicName) * (1 - (this->_musicNamePos - 180) / 60.f),
			camera.y - screenSize.y / 2.f + 10,
		});
	} else if (this->_musicNamePos > 60) {
		screen.draw(this->_musicName, {
			camera.x + screenSize.x / 2.f - screen.getTextWidth(this->_musicName),
			camera.y - screenSize.y / 2.f + 10,
		});
	} else {
		screen.fillColor(sf::Color{120, 120, 120, static_cast<sf::Uint8>(255 * this->_musicNamePos / 60)});
		screen.draw(this->_musicName, {
			camera.x + screenSize.x / 2.f - screen.getTextWidth(this->_musicName),
			camera.y - screenSize.y / 2.f + 10,
		});
	}

	this->_musicNamePos--;
}

void TouhouFanGame::Rendering::HUD::setDialogManager(TouhouFanGame::DialogMgr *manager)
{
	this->_dialog = manager;
}

void TouhouFanGame::Rendering::HUD::draw(TouhouFanGame::Game &game)
{
	if (this->_dispPlayer)
		this->_renderPlayerHUD(*game.resources.screen);

	if (this->_dispBoss)
		this->_renderBossHUD(*game.resources.screen);

	if (this->_musicNamePos)
		this->_renderMusic(*game.resources.screen);

	game.resources.screen->fillColor(sf::Color{255, 255, 255});
	if (this->_dialog)
		this->_dialog->render(game);
}

void TouhouFanGame::Rendering::HUD::setDispBossHUD(bool dispBoss)
{
	this->_dispBoss = dispBoss;
}

void TouhouFanGame::Rendering::HUD::setDispPlayerHUD(bool dispPlayer)
{
	this->_dispPlayer = dispPlayer;
}
