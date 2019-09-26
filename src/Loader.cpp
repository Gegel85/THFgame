//
// Created by Gegel85 on 24/09/2019.
//

#include "Loader.hpp"
#include "Exceptions.hpp"

namespace TouhouFanGame
{
	bool Loader::loadFile(sf::SoundBuffer &buffer, const std::string &path)
	{
		return buffer.loadFromFile(path);
	}

	bool Loader::loadFile(sf::Music &music, const std::string &path)
	{
		bool result = music.openFromFile(path);

		music.setLoop(true);
		music.setVolume(100);
		music.play();
		return result;
	}

	bool Loader::loadFile(sf::Texture &texture, const std::string &path)
	{
		return texture.loadFromFile(path);
	}

	void Loader::loadAssets()
	{
		std::ifstream stream{"assets/list.json"};
		json data;

		logger.debug("Opening file assets/list.json");
		if (stream.fail())
			throw CorruptedAssetsListException("Cannot open assets list from assets/list.json");

		logger.debug("Opening main window");
		game.resources.screen.reset(new Screen{"THFgame"});

		try {
			logger.debug("Parsing json");
			stream >> data;

			logger.debug("Loading icon");
			if (data["icon"].is_null())
				logger.warn("No Icon is marked for loading");
			else if (!game.resources.icon.loadFromFile("assets/" + static_cast<std::string>(data["icon"])))
				logger.error("Cannot load file assets/" + static_cast<std::string>(data["icon"]));
			else
				game.resources.screen->setIcon(
					game.resources.icon.getSize().x,
					game.resources.icon.getSize().y,
					game.resources.icon.getPixelsPtr()
				);

			logger.debug("Loading musics");
			loadAssetsFromJson("Musics", data["musics"], game.resources.musics);

			logger.debug("Loading sfx");
			loadAssetsFromJson("Sound effects", data["sfx"], game.resources.soundBuffers);

			logger.debug("Loading sprites");
			loadAssetsFromJson("Sprites", data["sprites"], game.resources.textures);
		} catch (nlohmann::detail::parse_error &e) {
			throw CorruptedAssetsListException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw CorruptedAssetsListException("The JSON values are invalid: " + std::string(e.what()));
		}
	}
}