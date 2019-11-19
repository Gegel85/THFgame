/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** Hud.cpp
*/

#include "Hud.hpp"

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
	this->_bossName = bossName;
}

void TouhouFanGame::Rendering::HUD::setPlayerName(const std::string &playerName)
{
	this->_playerName = playerName;
}

void TouhouFanGame::Rendering::HUD::setMusicName(const std::string &musicName)
{
	this->_musicNamePos = 120;
	this->_musicName = musicName;
}

void TouhouFanGame::Rendering::HUD::_renderPlayerHUD(TouhouFanGame::Rendering::Screen &screen)
{
	auto camera = screen.getCameraCenter();
	auto screenSize = screen.getSize();

	screen.fillColor(sf::Color{120, 120, 120});
	screen.textSize(15);
	screen.draw(this->_playerName, {
		camera.x - screenSize.x / 2.f + 5,
		camera.y + screenSize.y / 2.f - 53,
	});

	screen.fillColor(sf::Color{120, 120, 120});
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

	screen.fillColor(sf::Color{255, 0, 0});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 10),
		static_cast<int>(camera.y + screenSize.y / 2. - 30),
		static_cast<int>(this->_playerLife * 2),
		20
	});
	screen.fillColor(sf::Color{200, 200, 255});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x + screenSize.x / 2. - 210),
		static_cast<int>(camera.y + screenSize.y / 2. - 30),
		static_cast<int>(this->_playerMana * 2),
		20
	});

	screen.fillColor(sf::Color{255, 255, 255});
}

void TouhouFanGame::Rendering::HUD::_renderBossHUD(TouhouFanGame::Rendering::Screen &screen)
{
	auto camera = screen.getCameraCenter();
	auto screenSize = screen.getSize();

	screen.fillColor(sf::Color{120, 120, 120});
	screen.textSize(15);
	screen.draw(this->_bossName, {
		camera.x - screenSize.x / 2.f + 5,
		camera.y + screenSize.y / 2.f - 53,
	});

	screen.fillColor(sf::Color{120, 120, 120});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 1),
		static_cast<int>(camera.y - screenSize.y / 2. + 1),
		static_cast<int>(screenSize.x - 2),
		5
	});

	screen.fillColor(sf::Color{255, 0, 0});
	screen.draw(sf::IntRect{
		static_cast<int>(camera.x - screenSize.x / 2. + 2),
		static_cast<int>(camera.y - screenSize.y / 2. + 2),
		static_cast<int>(this->_bossLife * (screenSize.x - 4) / 100),
		3
	});

}

void TouhouFanGame::Rendering::HUD::_renderMusic(TouhouFanGame::Rendering::Screen &)
{
	this->_musicNamePos--;
}

void TouhouFanGame::Rendering::HUD::draw(TouhouFanGame::Rendering::Screen &screen)
{
	if (this->_dispPlayer)
		this->_renderPlayerHUD(screen);

	if (this->_dispBoss)
		this->_renderBossHUD(screen);

	if (this->_musicNamePos)
		this->_renderMusic(screen);
}

void TouhouFanGame::Rendering::HUD::setDispBossHUD(bool dispBoss)
{
	this->_dispBoss = dispBoss;
}

void TouhouFanGame::Rendering::HUD::setDispPlayerHUD(bool dispPlayer)
{
	this->_dispPlayer = dispPlayer;
}
