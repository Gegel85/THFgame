//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_RESOURCES_HPP
#define THFGAME_RESOURCES_HPP

#include <SFML/Audio.hpp>
#include "Screen.hpp"

namespace Game
{
	struct Resources {
		std::unique_ptr<Screen> screen;
		std::map<std::string, sf::Music> musics;
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::SoundBuffer> soundBuffers;
		sf::Sound sounds[128];

		unsigned char playSound(const std::string &id);
	};
}

#endif //THFGAME_RESOURCES_HPP
