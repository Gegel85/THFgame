//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_RESOURCES_HPP
#define THFGAME_RESOURCES_HPP

#include <SFML/Audio.hpp>
#include <random>
#include <json.hpp>
#include "Rendering/Screen.hpp"
#include "Inventory/Item.hpp"

namespace TouhouFanGame
{
	//! @brief The main Resources needed by the game
	struct Resources {
		//! @brief The icon of the screen
		sf::Image icon;

		//! @brief A random generator
		std::mt19937 random;

		//! @brief The main window
		std::unique_ptr<Rendering::Screen> screen;

		//! @brief The loaded musics
		std::map<std::string, std::pair<sf::Music, std::string>> musics;

		//! @brief The loaded sprites
		std::map<std::string, sf::Texture> textures;

		//! @brief The loaded sfx
		std::map<std::string, sf::SoundBuffer> soundBuffers;

		//! @brief The sound objects used to play sfx
		sf::Sound sounds[128];

		//! @brief The items JSON file loaded.
		std::vector<std::shared_ptr<Item>> items;

		//! @brief Plays a sound effect
		//! @param id The id of the sound effect to play
		//! @return The sound index assigned to this sfx
		unsigned char playSound(const std::string &id);

		//! @brief Plays a music
		//! @param id The id of the music to play
		void playMusic(const std::string &id);

		//! @brief Stops any music currently playing
		void stopMusic();
	};
}

#endif //THFGAME_RESOURCES_HPP
