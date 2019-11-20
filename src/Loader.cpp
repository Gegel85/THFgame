//
// Created by Gegel85 on 24/09/2019.
//

#include "Loader.hpp"
#include "Exceptions.hpp"
#include "Input/Keyboard.hpp"

namespace TouhouFanGame
{
	bool Loader::loadFile(Settings &, sf::SoundBuffer &buffer, nlohmann::json &path)
	{
		return buffer.loadFromFile("assets/" + static_cast<std::string>(path));
	}

	bool Loader::loadFile(Settings &settings, std::pair<sf::Music, std::string> &music, nlohmann::json &obj)
	{
		bool result = music.first.openFromFile("assets/" + static_cast<std::string>(obj["path"]));

		music.second = obj["description"].is_null() ? "" : obj["description"];
		music.first.setLoop(true);
		if (!obj["loop_points"].is_null())
			music.first.setLoopPoints(sf::Music::TimeSpan{
				sf::milliseconds(obj["loop_points"]["offset"]),
				sf::milliseconds(obj["loop_points"]["length"])
			});

		music.first.setVolume(settings.musicVolume);
		return result;
	}

	bool Loader::loadFile(Settings &, sf::Texture &texture, nlohmann::json &path)
	{
		return texture.loadFromFile("assets/" + static_cast<std::string>(path));
	}

	void Loader::loadSettings(Game &game)
	{
		logger.info("Loading settings");
		game.state.settings.input.reset(new Inputs::Keyboard(&*game.resources.screen));
		game.state.settings.musicVolume = 100;
		game.state.settings.sfxVolume = 100;
		for (auto &sound : game.resources.sounds)
			sound.setVolume(100);
	}

	void Loader::loadAssets(Game &game)
	{
		std::ifstream stream{"assets/list.json"};
		nlohmann::json data;

		logger.debug("Opening main window");
		game.resources.screen.reset(new Rendering::Screen{game.resources, "THFgame"});

		loadSettings(game);

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
			loadAssetsFromJson(game.state.settings, "Musics", data["musics"], game.resources.musics);

			logger.debug("Loading sfx");
			loadAssetsFromJson(game.state.settings, "Sound effects", data["sfx"], game.resources.soundBuffers);

			logger.debug("Loading sprites");
			loadAssetsFromJson(game.state.settings, "Sprites", data["sprites"], game.resources.textures);
		} catch (nlohmann::detail::parse_error &e) {
			throw CorruptedAssetsListException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw CorruptedAssetsListException("The JSON values are invalid: " + std::string(e.what()));
		}
	}
}