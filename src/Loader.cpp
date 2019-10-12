//
// Created by Gegel85 on 24/09/2019.
//

#include "Loader.hpp"
#include "Exceptions.hpp"
#include "Input/Keyboard.hpp"

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
		music.setVolume(game.state.musicVolume);
		music.play();
		return result;
	}

	bool Loader::loadFile(sf::Texture &texture, const std::string &path)
	{
		return texture.loadFromFile(path);
	}

	void Loader::loadSettings()
	{
		logger.info("Loading settings");
		game.state.input.reset(new Inputs::Keyboard(&*game.resources.screen));
		game.state.musicVolume = 100;
		game.state.sfxVolume = 100;
		for (auto &sound : game.resources.sounds)
			sound.setVolume(100);
	}

	void Loader::loadAssets()
	{
		std::ifstream stream{"assets/list.json"};
		json data;

		logger.debug("Opening main window");
		game.resources.screen.reset(new Rendering::Screen{"THFgame"});

		loadSettings();

		//We do this because on MinGW std::random_device always produce the same output
		//(also we don't need the most unpredictable seed)
		game.resources.random.seed(time(nullptr));

		logger.debug("Opening file assets/list.json");
		if (stream.fail())
			throw CorruptedAssetsListException("Cannot open assets list from assets/list.json");

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