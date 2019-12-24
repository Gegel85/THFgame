//
// Created by Gegel85 on 23/12/2019.
//

#include "MapEditor.hpp"
#include "../Core/Utils.hpp"

namespace TouhouFanGame
{
	//! @brief The global logger
	Logger logger{"./latest.log", Logger::DEBUG};
}

int main()
{
	TouhouFanGame::MapEditor editor;

	try {
		editor.setup();
		return editor.run();
	} catch (std::exception &e) {
		TouhouFanGame::logger.fatal(getLastExceptionName() + ": " + e.what());
		TouhouFanGame::Utils::dispMsg(
			"Fatal Error",
			"An unrecoverable error occurred\n\n" +
			getLastExceptionName() + ":\n" + e.what() + "\n\n"
			"Click OK to close the application",
			MB_ICONERROR
		);
		return EXIT_FAILURE;
	}
}