//
// Created by Gegel85 on 04/01/2020.
//

#ifndef THFGAME_DIALOGMGR_HPP
#define THFGAME_DIALOGMGR_HPP


#include <string>
#include <vector>
#include <functional>
#include <map>
#include <TGUI/Vector2f.hpp>
#include "../ECS/Entity.hpp"

#define DIALOG_SPRITE_SIZE this->_dialogSpriteSize

namespace TouhouFanGame
{
	class Game;

	//! @brief Manages dialogs.
	class DialogMgr {
	private:
		//! @brief The holder of this Dialog.
		std::shared_ptr<ECS::Entity> _holder;

		sf::Vector2f _dialogSpriteSize;

		//! @brief The dialog currently selected.
		unsigned _selected = 0;

		//! @brief Whether this manager is waiting for the a user action.
		bool _waiting = false;

		//! @brief The string that is left to treat.
		std::string _left;

		//! The string currently displayed.
		std::string _displayed;

		//! @brief The currently loaded file.
		std::string _loaded;

		//! @brief All the dialogs loaded.
		std::vector<std::string> _dialogs;

		std::string _holderSprite;

		std::string _otherSprite;

		unsigned char _holderAnims = 0;

		unsigned char _otherAnims = 0;

		sf::Vector2f _holderPos = {25, 140};

		sf::Vector2f _otherPos = {25, 140};

		char _holderTimer = 0;

		char _otherTimer = 0;

		bool _holderFocus = false;

		bool _otherFocus = false;

		//! @brief Executes a command.
		//! @param cmd The command to execute.
		//! @param args The arguments given to the command.
		//! @throw BadCommandException, BadArgumentsException
		void _executeCommand(Game &game, const std::string &cmd, const std::vector<std::string> &args);

		//! @brief Parse a command.
		//! @return A vector containing the command at first position and then it's arguments.
		//! @throw UnfinishedCommandException, UnfinishedStringLiteralException
		std::vector<std::string> _parseCommand();

		//! @brief Consumes a character of a dialog.
		void _consumeCharacter(Game &game);

	public:
		DialogMgr();

		//! @brief Select a previously loaded dialog.
		//! @param dialog The dialog to select.
		void select(unsigned dialog);

		//! @brief Whether this manager is waiting for the a user action.
		bool waiting() const;

		//! @brief If this manager has finished it's job, it will return true and go to the next dialog available or loop back at the start.
		//!        If the manager hasn't finished, then it only returns false.
		bool finish();

		//! @brief Change the holder of this Dialog.
		void setHolder(const std::shared_ptr<ECS::Entity> &entity);

		//! @brief Get the currently selected dialog.
		unsigned getSelected() const;

		//! @brief Load dialogs from a stream.
		//! @throw InvalidDialogStringException
		void loadFromStream(std::istream &stream);

		//! @brief Load dialogs from a file.
		//! @throw InvalidDialogFileException
		void loadFromFile(const std::string &file);

		//! @brief Display the dialog box on the screen.
		void render(Game &game) const;

		//! @brief Updates the manager's state, advancing in the currently displayed dialog if needed.
		//! @param game Game state and resources.
		void update(Game &game);

		void resetSprites();
	};
}


#endif //THFGAME_DIALOGMGR_HPP
