//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_RESOURCES_HPP
#define THFGAME_RESOURCES_HPP

#include <SFML/Audio.hpp>
#include "Rendering/Screen.hpp"

namespace TouhouFanGame
{
	struct Resources {
		sf::Image icon;
		std::unique_ptr<Rendering::Screen> screen;
		std::map<std::string, sf::Music> musics;
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::SoundBuffer> soundBuffers;
		sf::Sound sounds[128];

		unsigned char playSound(const std::string &id);
		void playMusic(const std::string &id);
		void stopMusic();
	};
}

#endif //THFGAME_RESOURCES_HPP
