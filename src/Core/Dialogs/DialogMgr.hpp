//
// Created by Gegel85 on 04/01/2020.
//

#ifndef THFGAME_DIALOGMGR_HPP
#define THFGAME_DIALOGMGR_HPP


#include <string>
#include <vector>
#include "../ECS/Entity.hpp"

namespace TouhouFanGame
{
	class Game;

	//! @brief Manages dialogs.
	class DialogMgr {
	private:
		//! @brief The holder of this Dialog.
		ECS::Entity &_holder;

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

		//! @brief Executes a command.
		//! @param cmd The command to execute.
		//! @param args The arguments given to the command.
		//! @throw BadCommandException, BadArgumentsException
		void _executeCommand(Game &game, const std::string &cmd, const std::vector<std::string> args);

		//! @brief Parse a command.
		//! @return A vector containing the command at first position and then it's arguments.
		//! @throw UnfinishedCommandException, UnfinishedStringLiteralException
		std::vector<std::string> _parseCommand();

		//! @brief Consumes a character of a dialog.
		void _consumeCharacter(Game &game);

	public:
		//! @brief Constructor.
		DialogMgr(ECS::Entity &holder);

		//! @brief Select a previously loaded dialog.
		//! @param dialog The dialog to select.
		void select(unsigned dialog);

		//! @brief Whether this manager is waiting for the a user action.
		bool waiting() const;

		//! @brief Whether this manager has finished his job (The dialog has come to an end).
		bool finished() const;

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
		//! @param skip Is the skip key pressed ?
		//! @param fast Is the faster dialog key pressed ?
		void update(Game &game, bool skip, bool fast);
	};
}


#endif //THFGAME_DIALOGMGR_HPP
