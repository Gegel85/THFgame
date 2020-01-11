//
// Created by Gegel85 on 04/01/2020.
//

#include <stdexcept>
#include "DialogMgr.hpp"
#include "../Game.hpp"
#include "../Exceptions.hpp"
#include "../ECS/Components/NameComponent.hpp"

namespace TouhouFanGame
{
	DialogMgr::DialogMgr()
	{
		std::ifstream stream{"assets/dialogSize.txt"};

		stream >> this->_dialogSpriteSize.x >> this->_dialogSpriteSize.y,
		stream.close();
	}

	void DialogMgr::select(unsigned dialog)
	{
		this->_displayed = "";
		this->_waiting = false;
		try {
			this->_left = this->_dialogs.at(dialog);
			this->_selected = dialog;
		} catch (std::out_of_range &e) {
			this->_left = "";
			throw DialogNotFoundException("Invalid dialog number (" + std::to_string(dialog) + ") for file \"" + this->_loaded + "\": " + e.what());
		}
	}

	bool DialogMgr::waiting() const
	{
		return this->_waiting;
	}

	bool DialogMgr::finish()
	{
		if (this->_left.empty() && !this->_waiting) {
			try {
				this->select(this->_selected + 1);
			} catch (DialogNotFoundException &) {
				this->select(0);
			}
			return true;
		}
		return false;
	}

	void DialogMgr::resetSprites()
	{
		this->_holderSprite.clear();
		this->_otherSprite.clear();
		this->_holderAnims = 0;
		this->_otherAnims = 0;
		this->_holderPos = {25, 140};
		this->_otherPos = {25, 140};
		this->_holderTimer = 0;
		this->_otherTimer = 0;
		this->_holderFocus = false;
		this->_otherFocus = false;
	}

	void DialogMgr::render(TouhouFanGame::Game &game) const
	{
		if (!game.resources.screen)
			return;

		auto &screen = *game.resources.screen;
		auto camera = screen.getCameraCenter();
		auto screenSize = screen.getSize();
		sf::Text text;

		if (!this->_holderSprite.empty()) {
			screen.fillColor({
				255,
				255,
				255,
				static_cast<sf::Uint8>(this->_holderFocus ? 255 -  this->_holderTimer * 4 : 95 - this->_holderTimer * 4)
			});
			screen.draw(
				game.resources.textures[this->_holderSprite],
				{
					camera.x + screenSize.x / 2.f - this->_holderPos.x - DIALOG_SPRITE_SIZE.x,
					camera.y - screenSize.y / 2.f + this->_holderPos.y
				},
				{
					static_cast<unsigned>(DIALOG_SPRITE_SIZE.x * screenSize.x / 640),
					static_cast<unsigned>(DIALOG_SPRITE_SIZE.y * screenSize.y / 480)
				},
				{
					static_cast<int>(this->_holderAnims * DIALOG_SPRITE_SIZE.x),
					0,
					static_cast<int>(DIALOG_SPRITE_SIZE.x),
					static_cast<int>(DIALOG_SPRITE_SIZE.y)
				}
			);
		}

		if (!this->_otherSprite.empty()) {
			screen.fillColor({
				255,
				255,
				255,
				static_cast<sf::Uint8>(this->_otherFocus ? 255 - this->_otherTimer * 4 : 95 - this->_otherTimer * 4)
			});
			screen.draw(
				game.resources.textures[this->_otherSprite],
				{
					camera.x - screenSize.x / 2.f + this->_otherPos.x,
					camera.y - screenSize.y / 2.f + this->_otherPos.y
				},
				{
					static_cast<unsigned>(DIALOG_SPRITE_SIZE.x * screenSize.x / 640),
					static_cast<unsigned>(DIALOG_SPRITE_SIZE.y * screenSize.y / 480)
				},
				{
					static_cast<int>(this->_otherAnims * DIALOG_SPRITE_SIZE.x),
					0,
					static_cast<int>(DIALOG_SPRITE_SIZE.x),
					static_cast<int>(DIALOG_SPRITE_SIZE.y)
				}
			);
		}

		screen.fillColor();

		screen.draw(game.resources.textures["dialog_box"], {
			camera.x - screenSize.x / 2.f,
			camera.y + 2.f * screenSize.y / 6.f,
		}, {
			screenSize.x,
			screenSize.y / 6
		});
		text.setFont(game.resources.font);
		text.setString(this->_displayed);
		text.setPosition(camera.x - screenSize.x / 2.f + 32, camera.y + 2.f * screenSize.y / 6.f + 10);
		text.setScale({screenSize.x / 800.f, screenSize.y / 640.f});
		static_cast<sf::RenderWindow &>(screen).draw(text);
	}

	unsigned DialogMgr::getSelected() const
	{
		return this->_selected;
	}

	void DialogMgr::setHolder(const std::shared_ptr<ECS::Entity> &entity)
	{
		this->_holder = entity;
	}

	void DialogMgr::update(Game &game)
	{
		if (this->waiting()) {
			this->_waiting = !game.state.settings.input->actionPressed(Input::DIALOG);
			if (!this->_waiting)
				this->_displayed.clear();
			return;
		}
		if (this->_left.empty())
			return;
		for (int i = game.state.settings.input->actionPressed(Input::SPRINT) * 2 + 1; i != 0 && !this->waiting(); i--)
			this->_consumeCharacter(game);

		if (this->_holderTimer > 0) {
			this->_holderTimer--;
			this->_holderPos.x += 3;
			this->_holderPos.y -= 3;
		} else if (this->_holderTimer < 0) {
			this->_holderTimer++;
			this->_holderPos.x -= 3;
			this->_holderPos.y += 3;
		}

		if (this->_otherTimer < 0) {
			this->_otherTimer++;
			this->_otherPos.x -= 3;
			this->_otherPos.y += 3;
		} else if (this->_otherTimer > 0) {
			this->_otherTimer--;
			this->_otherPos.x += 3;
			this->_otherPos.y -= 3;
		}
	}

	void DialogMgr::loadFromFile(const std::string &file)
	{
		std::ifstream fstream{file};

		logger.info("Loading dialog file " + file);
		if (fstream.fail())
			throw InvalidDialogFileException("\"" + file + "\": " + strerror(errno));
		this->loadFromStream(fstream);
		fstream.close();
	}

	void DialogMgr::loadFromStream(std::istream &stream)
	{
		std::string line;

		while (!stream.eof()) {
			std::getline(stream, line, '\0');
			this->_dialogs.push_back(line);
			logger.debug("Loaded line " + line);
		}
	}

	void DialogMgr::_consumeCharacter(Game &game)
	{
		char c = this->_left[0];

		this->_left = this->_left.substr(1);
		switch (c) {
		case '\\':
			this->_displayed += this->_left[0];
			this->_left = this->_left.substr(1);
			break;
		default:
			this->_displayed += c;
			break;
		case '\n':
			this->_waiting = !this->_displayed.empty();
			break;
		case '%':
			auto elems = this->_parseCommand();
			auto cmd = elems[0];

			elems.erase(elems.begin());
			this->_executeCommand(game, cmd, elems);
			if (!this->_left.empty())
				this->_consumeCharacter(game);
		}
		this->_waiting |= this->_left.empty() && !this->_displayed.empty();
	}

	std::vector<std::string> DialogMgr::_parseCommand()
	{
		std::vector<std::string> result;
		int i = 0;
		char quote = 0;
		std::string token;
		char c = this->_left[i];

		try {
			while (c != '%') {
				switch (c) {
				case '"':
				case '\'':
					if (quote == c) {
						quote = 0;
						result.push_back(token);
						token.clear();
					} else if (!quote)
						quote = c;
					else
						token.push_back(c);
					break;
				case ' ':
				case '\t':
				case '\n':
					if (quote)
						token.push_back(c);
					else if (!token.empty()) {
						result.push_back(token);
						token.clear();
					}
					break;
				case '\\':
					token.push_back(this->_left.at(++i));
					break;
				default:
					token.push_back(c);
				}
				c = this->_left.at(++i);
			}
		} catch (std::out_of_range &) {
			if (quote)
				throw UnfinishedStringLiteralException("Unfinished string  found (starting here: " + std::string(&quote, 1) + token.substr(0, 6) + ")");
			throw UnfinishedCommandException("Unfinished command found (starting here: " + this->_left.substr(0, 6) + ")");
		}
		result.push_back(token);
		this->_left = this->_left.substr(i + 1);
		return result;
	}

	void DialogMgr::_executeCommand(Game &game, const std::string &cmdName, const std::vector<std::string> &args)
	{
		const std::map<std::string, std::pair<unsigned, std::function<void(const std::vector<std::string> &)>>> cmds{
			{"playerName", {0, [this, &game](const std::vector<std::string> &){
				this->_left = game.state.map.getPlayer()->getComponent("Name").to<ECS::Components::NameComponent>().name + this->_left;
			}}},
			{"holderName", {0, [this](const std::vector<std::string> &){
				this->_left = (this->_holder ? this->_holder->getComponent("Name").to<ECS::Components::NameComponent>().name : "(NULL)") + this->_left;
			}}},
			{"setMusic", {1, [&game](const std::vector<std::string> &args){
				game.resources.playMusic(args[0]);
			}}},
			{"setHolderSprite", {1, [this](const std::vector<std::string> &args){
				this->_holderSprite = args[0];
			}}},
			{"setPlayerSprite", {1, [this](const std::vector<std::string> &args){
				this->_otherSprite = args[0];
			}}},
			{"setHolderAnim", {1, [this](const std::vector<std::string> &args){
				this->_holderAnims = std::stol(args[0]);
			}}},
			{"setPlayerAnim", {1, [this](const std::vector<std::string> &args){
				this->_otherAnims = std::stol(args[0]);
			}}},
			{"toggleHolderFocus", {0, [this](const std::vector<std::string> &){
				this->_holderFocus = !this->_holderFocus;
				if (abs(this->_holderTimer + 10 * (this->_holderFocus ? 1 : -1)) <= 10)
					this->_holderTimer += 10 * (this->_holderFocus ? 1 : -1);
			}}},
			{"togglePlayerFocus", {0, [this](const std::vector<std::string> &){
				this->_otherFocus = !this->_otherFocus;
				if (abs(this->_otherTimer + 10 * (this->_otherFocus ? 1 : -1)) <= 10)
					this->_otherTimer += 10 * (this->_otherFocus ? 1 : -1);
			}}}
		};

		try {
			auto cmd = cmds.at(cmdName);

			if (cmd.first != args.size())
				throw InvalidArgumentsException("Expected " + std::to_string(cmd.first) + " argument for " + cmdName + " but " + std::to_string(args.size()) + " given.");
			cmd.second(args);
		} catch (std::out_of_range &) {
			throw BadCommandException("No command named \"" + cmdName + "\"");
		}
	}
}