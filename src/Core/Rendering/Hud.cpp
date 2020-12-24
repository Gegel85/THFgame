/*
** EPITECH PROJECT, 2019
** THFgame
** File description:
** Hud.cpp
*/

#include "Hud.hpp"
#include "../Resources/Game.hpp"

namespace TouhouFanGame::Rendering
{
	HUD::HUD(std::map<std::string, sf::Texture> &textures) :
		_textures(textures)
	{
	}

	void HUD::setBossLife(float bossLife)
	{
		this->_bossLife = bossLife;
	}

	void HUD::setPlayerLife(float playerLife)
	{
		this->_playerLife = playerLife;
	}

	void HUD::setPlayerMana(float playerMana)
	{
		this->_playerMana = playerMana;
	}

	void HUD::setBossName(const std::string &bossName)
	{
		this->_bossName = bossName;
	}

	void HUD::setPlayerName(const std::string &playerName)
	{
		this->_playerName = playerName;
	}

	void HUD::setMusicName(const std::string &musicName)
	{
		if (this->_musicName == musicName)
			return;
		this->_musicNamePos = 240;
		this->_musicName = musicName;
	}

	void HUD::_renderPlayerDeck(Screen &screen)
	{
		if (this->_playerDeck.empty())
			return;

		auto selected = this->_selectedCard % this->_playerDeck.size();
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();

		screen.fillColor(sf::Color{255, 255, 0});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x + screenSize.x / 2. - 57),
			static_cast<int>(camera.y + screenSize.y / 2. - 124),
			52,
			84
		});

		screen.fillColor();
		screen.draw(
			this->_textures[this->_playerDeck[selected]],
			{
				camera.x + screenSize.x / 2.f - 55,
				camera.y + screenSize.y / 2.f - 122
			},
			{
				48,
				80
			}
		);

		for (size_t i = 1; i < this->_playerDeck.size(); i++) {
			selected += 1;
			selected %= this->_playerDeck.size();
			screen.draw(sf::IntRect{
				static_cast<int>(camera.x + screenSize.x / 2. - 57 - 33 * i),
				static_cast<int>(camera.y + screenSize.y / 2. - 84),
				28,
				44
			});

			screen.fillColor();
			screen.draw(
				this->_textures[this->_playerDeck[selected]],
				{
					camera.x + screenSize.x / 2.f - 55 - 33 * i,
					camera.y + screenSize.y / 2.f - 82
				},
				{
					24,
					40
				}
			);
		}
	}

	void HUD::_renderExpBar(Screen &screen)
	{
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();

		screen.fillColor(sf::Color{120, 120, 120});
		screen.textSize(15);
		screen.draw("Level " + std::to_string(this->_level), {
			camera.x - screenSize.x / 2.f + 5,
			camera.y + screenSize.y / 2.f - 69,
		});

		screen.fillColor(sf::Color{100, 100, 100});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 5),
			static_cast<int>(camera.y + screenSize.y / 2. - 50),
			100,
			10
		});

		screen.fillColor(sf::Color{0, 255, 0});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 5),
			static_cast<int>(camera.y + screenSize.y / 2. - 50),
			static_cast<int>(this->_exp),
			10
		});
	}

	void HUD::_renderManaBar(Screen &screen)
	{
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();

		screen.fillColor(sf::Color{200, 200, 200});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x + screenSize.x / 2. - 215),
			static_cast<int>(camera.y + screenSize.y / 2. - 35),
			210,
			30
		});

		screen.fillColor(sf::Color{50, 50, 50});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x + screenSize.x / 2. - 210),
			static_cast<int>(camera.y + screenSize.y / 2. - 30),
			static_cast<int>(200),
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

	void HUD::_renderLifeBar(Screen &screen)
	{
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();

		screen.fillColor(sf::Color{200, 200, 200});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 5),
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

		screen.fillColor(sf::Color{255, 0, 0});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 10),
			static_cast<int>(camera.y + screenSize.y / 2. - 30),
			static_cast<int>(this->_playerLife * 2),
			20
		});
	}

	void HUD::_renderPlayerHUD(Screen &screen)
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
			camera.x - screenSize.x / 2.f + 115,
			camera.y + screenSize.y / 2.f - 57,
		});

		this->_renderExpBar(screen);
		this->_renderManaBar(screen);
		this->_renderLifeBar(screen);
		this->_renderPlayerDeck(screen);
	}

	void HUD::_renderBossHUD(Screen &screen)
	{
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();

		screen.fillColor(sf::Color::Black);
		screen.textSize(10);
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2.),
			static_cast<int>(camera.y - screenSize.y / 2.),
			static_cast<int>(screenSize.x),
			22
		});

		screen.fillColor(sf::Color{0xFF, 0xD7, 0x00});
		screen.draw(this->_bossName, {
			camera.x - screenSize.x / 2.f + 30,
			camera.y - screenSize.y / 2.f + 9,
		});

		screen.fillColor(sf::Color{120, 120, 120, 120});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 31),
			static_cast<int>(camera.y - screenSize.y / 2. + 1),
			static_cast<int>(screenSize.x - 62),
			8
		});

		screen.fillColor(sf::Color{255, 0, 0, 120});
		screen.draw(sf::IntRect{
			static_cast<int>(camera.x - screenSize.x / 2. + 32),
			static_cast<int>(camera.y - screenSize.y / 2. + 2),
			static_cast<int>(this->_bossLife * (screenSize.x - 64) / 100),
			6
		});

		screen.textSize(20);
		screen.fillColor(sf::Color::White);
		screen.draw(std::to_string(this->_bossHpBars), {
			camera.x - screenSize.x / 2.f + (this->_bossHpBars >= 10 ? 2 : 17 ),
			camera.y - screenSize.y / 2.f - 2,
		});

		if (this->_displayedTime < 30)
			screen.fillColor(sf::Color(
				255,
				(this->_displayedTime - 10) * 255 / 20,
				std::max((this->_displayedTime - 20) * 255 / 10, 0)
			));
		else if (this->_displayedTime < 10)
			screen.fillColor(sf::Color(
				this->_displayedTime * 130 / 10 + 125,
				0,
				0
			));
		screen.draw(std::to_string(this->_displayedTime), {
			camera.x + screenSize.x / 2.f - 25,
			camera.y - screenSize.y / 2.f - 2,
		});
	}

	void HUD::_renderMusic(Screen &screen)
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

	void HUD::setDialogManager(TouhouFanGame::DialogMgr *manager)
	{
		this->_dialog = manager;
	}

	void HUD::draw(TouhouFanGame::Game &game)
	{
		if (this->_dispPlayer)
			this->_renderPlayerHUD(*game.resources.screen);

		if (this->_dispBoss)
			this->_renderBossHUD(*game.resources.screen);

		if (this->_musicNamePos)
			this->_renderMusic(*game.resources.screen);

		game.resources.screen->fillColor(sf::Color{255, 255, 255});
		if (this->_dialog) {
			this->_dialog->render(game);
			this->_dialog->update(game);
		}
	}

	void HUD::setDispBossHUD(bool dispBoss)
	{
		this->_dispBoss = dispBoss;
	}

	void HUD::setDispPlayerHUD(bool dispPlayer)
	{
		this->_dispPlayer = dispPlayer;
	}

	void HUD::setExpLevel(float exp)
	{
		this->_exp = exp;
	}

	void HUD::setCurrentLevel(unsigned int level)
	{
		this->_level = level;
	}

	void HUD::setPlayerDeck(const std::vector<std::string> &playerDeck)
	{
		this->_playerDeck = playerDeck;
	}

	void HUD::setSelectedCard(unsigned int selectedCard)
	{
		this->_selectedCard = selectedCard;
	}

	void HUD::setDisplayedTime(unsigned char displayedTime)
	{
		this->_displayedTime = std::min<unsigned char>(displayedTime, 99);
	}

	void HUD::setBossHpBars(unsigned char bossHpBars)
	{
		this->_bossHpBars = bossHpBars;
	}
}