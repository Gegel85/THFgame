//
// Created by Gegel85 on 24/09/2019.
//

#include "Loader.hpp"

namespace Game
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
		std::ifstream stream;
		json data;

		stream.exceptions(stream.exceptions() | std::ios::failbit);
		logger.debug("Opening file assets/list.json");
		stream.open("assets/list.json");

		logger.debug("Opening main window");
		game.resources.screen.reset(new Screen{"THFgame"});

		logger.debug("Parsing json");
		stream >> data;

		logger.debug("Loading musics");
		loadAssetsFromJson("Musics", data["musics"], game.resources.musics);

		logger.debug("Loading sfx");
		loadAssetsFromJson("Sound effects", data["sfx"], game.resources.soundBuffers);

		logger.debug("Loading sprites");
		loadAssetsFromJson("Sprites", data["sprites"], game.resources.textures);
	}
}