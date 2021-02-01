//
// Created by Gegel85 on 24/09/2019.
//

#include <filesystem>
#include "Loader.hpp"
#include "../Exceptions.hpp"
#include "../Input/SFMLKeyboard.hpp"
#include "../Inventory/ItemFactory.hpp"
#include "../Utils/Utils.hpp"
#include "../Input/SFMLJoypad.hpp"

namespace TouhouFanGame
{
	bool Loader::loadFile(Settings &, sf::Image &buffer, nlohmann::json &path)
	{
		return buffer.loadFromFile("assets/" + path.get<std::string>());
	}

	bool Loader::loadFile(Settings &, sf::Texture &buffer, nlohmann::json &path)
	{
		return buffer.loadFromFile("assets/" + path.get<std::string>());
	}

	bool Loader::loadFile(Settings &, sf::SoundBuffer &buffer, nlohmann::json &path)
	{
		return buffer.loadFromFile("assets/" + path.get<std::string>());
	}

	bool Loader::loadFile(Settings &settings, std::pair<sf::Music, std::string> &music, nlohmann::json &obj)
	{
		bool result = music.first.openFromFile("assets/" + obj["path"].get<std::string>());

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

	void Loader::saveSettings(TouhouFanGame::Settings &settings)
	{
		std::filesystem::create_directories("saves");

		std::ofstream stream("saves/settings.sav");

		settings.input->serialize(stream);
		stream << std::endl << settings.musicVolume << std::endl << settings.sfxVolume;
		stream.close();
	}

	void Loader::loadSettings(Game &game)
	{
		std::ifstream stream("saves/settings.sav");

		logger.info("Loading settings");
		game.state.settings.input.reset(new Inputs::SFMLKeyboard(&*game.resources.screen));
		if (stream.fail()) {
			logger.error("Cannot open file save/settings.sav " + std::string(strerror(errno)));
			game.state.settings.musicVolume = 100;
			game.state.settings.sfxVolume = 100;
		} else {
			game.state.settings.input->unserialize(stream);
			stream >> game.state.settings.musicVolume >> game.state.settings.sfxVolume;
		}
		game.resources.setMusicVolume(game.state.settings.musicVolume);
		game.resources.setSoundVolume(game.state.settings.sfxVolume);
	}

	void Loader::loadItems(TouhouFanGame::Game &game)
	{
		std::ifstream stream{"assets/items.json"};
		nlohmann::json objs;

		if (stream.fail())
			throw CorruptedAssetsListException("Cannot open assets list from assets/items.json");
		stream >> objs;
		stream.close();

		if (!objs.is_array())
			throw CorruptedAssetsListException("Items list must be an array");

		for (unsigned i = 0; i < objs.size(); i++)
			game.resources.items.emplace_back(ItemFactory::buildItem(i, objs[i]["type"].is_null() ? "Classic" : objs[i]["type"], objs[i]));
	}

	void Loader::loadAssets(Game &game)
	{
		std::ifstream stream{"assets/list.json"};
		nlohmann::json data;
		GLenum err = glewInit();

		if (err != GLEW_OK)
		{
			//Problem: glewInit failed, something is seriously wrong.
			std::cerr << "glewInit failed, aborting." << std::endl;
			throw InitFailedException("glewInit()", err);
		}

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
			else if (!game.resources.icon.loadFromFile("assets/" + data["icon"].get<std::string>()))
				logger.error("Cannot load file assets/" + data["icon"].get<std::string>());
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

			logger.debug("Loading textures");
			loadAssetsFromJson(game.state.settings, "Textures", data["textures"], game.resources.modelTextures);

			logger.debug("Loading models");
			loadAssetsFromJson(game, "Models", data["meshes"], game.resources.models);

			logger.debug("Loading items json");
			loadItems(game);
		} catch (nlohmann::detail::parse_error &e) {
			throw CorruptedAssetsListException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw CorruptedAssetsListException("The JSON values are invalid: " + std::string(e.what()));
		}
	}

	void Loader::loadAssetsFromJson(Game &game, const std::string &dataName, nlohmann::json &paths, std::map<std::string, Rendering::MeshObject> &data)
	{
		if (paths.is_null())
			logger.warn("No " + dataName + " is marked for loading");

		logger.debug("Loading " + std::to_string(paths.size()) + " " + dataName);
		for (auto &value : paths.items()) {
			logger.debug("Loading value " + value.value().dump() + " at key " + value.key());
			try {
				data.at(value.key());
				logger.error("A " + dataName + " is already loaded with key " + value.key());
				return;
			} catch (std::out_of_range &) {}

			try {
				data.try_emplace(value.key(), game.resources.modelTextures, "assets/" + std::string(value.value()));
			} catch (std::exception &e) {
				logger.error("Cannot load element " + value.value().dump());
				logger.error(getLastExceptionName() + ": " + e.what());
			}
		}
	}
}