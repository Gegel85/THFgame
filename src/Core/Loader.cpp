//
// Created by Gegel85 on 24/09/2019.
//

#include "Loader.hpp"
#include "../Exceptions.hpp"
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

	void Loader::loadItems(TouhouFanGame::Game &game)
	{
		std::ifstream stream{"assets/items.json"};

		if (stream.fail())
			throw CorruptedAssetsListException("Cannot open assets list from assets/items.json");
		stream >> game.resources.items;
		stream.close();

		if (!game.resources.items.is_array())
			throw CorruptedAssetsListException("Items list must be an array");

		for (nlohmann::json &obj : game.resources.items) {
			if (!obj.is_object())
				throw CorruptedAssetsListException("Items list must be an array of objects");
			if (!obj["name"].is_string())
				throw CorruptedAssetsListException("Items name must be string");
			if (!obj["icon"].is_string())
				throw CorruptedAssetsListException("Items icon must be string");
			if (!obj["description"].is_string())
				throw CorruptedAssetsListException("Items description must be string");
			if (!obj["effects"].is_object() && !obj["effects"].is_null())
				throw CorruptedAssetsListException("Items effects must be an object or null");
			if (obj["effects"].is_object() && !obj["effects"]["healing"].is_number() && !obj["effects"]["healing"].is_null())
				throw CorruptedAssetsListException("Items healing effect must be a number or null");
			if (obj["effects"].is_object() && !obj["effects"]["mana"].is_number() && !obj["effects"]["mana"].is_null())
				throw CorruptedAssetsListException("Items mana healing effect must be a number or null");
		}
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
			stream.close();

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

			logger.debug("Loading items json");
			loadItems(game);
		} catch (nlohmann::detail::parse_error &e) {
			throw CorruptedAssetsListException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw CorruptedAssetsListException("The JSON values are invalid: " + std::string(e.what()));
		}
	}
}