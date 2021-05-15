//
// Created by Gegel85 on 24/09/2019.
//

#include <filesystem>
#include <thread>
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
		LoaderStatus status;
		std::thread thread;
		auto loadingFct = [&stream, &game, &status]{
			nlohmann::json data;

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
				loadAssetsFromJson(status, game.state.settings, "Musics", data["musics"], game.resources.musics);

				logger.debug("Loading sfx");
				loadAssetsFromJson(status, game.state.settings, "Sound effects", data["sfx"], game.resources.soundBuffers);

				logger.debug("Loading sprites");
				loadAssetsFromJson(status, game.state.settings, "Sprites", data["sprites"], game.resources.textures);

				logger.debug("Loading items json");
				loadItems(game);
			} catch (nlohmann::detail::parse_error &e) {
				throw CorruptedAssetsListException("The JSON file has an invalid format: " + std::string(e.what()));
			} catch (nlohmann::detail::type_error &e) {
				throw CorruptedAssetsListException("The JSON values are invalid: " + std::string(e.what()));
			}
		};

		loadSettings(game);

		//We do this because on MinGW std::random_device always produce the same output
		//(also we don't need the most unpredictable seed)
		game.resources.random.seed(time(nullptr));

		thread = std::thread(loadingFct);

		while (status.step < 5) {
			if (game.resources.screen) {
				auto &size = game.resources.screen->getView().getSize();
				auto corner = game.resources.screen->getView().getCenter();
				
				corner.x -= size.x / 2;
				corner.y -= size.y / 2;

				game.resources.screen->clear();
				game.resources.screen->textSize(20);
				game.resources.screen->fillColor({200, 200, 200, 255});
				game.resources.screen->draw(status.stepName, {
					corner.x + size.x / 2 - game.resources.screen->getTextWidth(status.stepName) / 2,
					corner.y + size.y - 160
				});
				game.resources.screen->draw(status.miniStepName, {
					corner.x + size.x / 2 - game.resources.screen->getTextWidth(status.miniStepName) / 2,
					corner.y + size.y - 80
				});
				game.resources.screen->draw({
					static_cast<int>(corner.x + 10),
					static_cast<int>(corner.y + size.y - 130),
					static_cast<int>(size.x - 20),
					40
				});
				game.resources.screen->draw({
					static_cast<int>(corner.x + 10),
					static_cast<int>(corner.y + size.y - 50),
					static_cast<int>(size.x - 20),
					40
				});
				game.resources.screen->fillColor(sf::Color::Black);
				game.resources.screen->draw({
					static_cast<int>(corner.x + 15),
					static_cast<int>(corner.y + size.y - 125),
					static_cast<int>(size.x - 30),
					30
				});
				game.resources.screen->draw({
					static_cast<int>(corner.x + 15),
					static_cast<int>(corner.y + size.y - 45),
					static_cast<int>(size.x - 30),
					30
				});
				game.resources.screen->fillColor(sf::Color::Green);
				game.resources.screen->draw({
					static_cast<int>(corner.x + 15),
					static_cast<int>(corner.y + size.y - 125),
					static_cast<int>((size.x - 30) * status.step / 5.f),
					30
				});
				game.resources.screen->fillColor(sf::Color::Blue);
				game.resources.screen->draw({
					static_cast<int>(corner.x + 15),
					static_cast<int>(corner.y + size.y - 45),
					static_cast<int>((size.x - 30) * status.miniStep.first / status.miniStep.second),
					30
				});
				game.resources.screen->display();
			} else
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		if (thread.joinable())
			thread.join();
	}
}