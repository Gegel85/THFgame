//
// Created by Gegel85 on 23/09/2019.
//

#ifndef THFGAME_RESOURCES_HPP
#define THFGAME_RESOURCES_HPP

#include <SFML/Audio.hpp>
#include <random>
#include <json.hpp>
#include "../Rendering/Screen.hpp"
#include "../Inventory/Item.hpp"

#define MAX_PLAYING_SFX 128

namespace TouhouFanGame
{
	//! @brief The main Resources needed by the game
	struct Resources : public BaseObject {
	private:
		//! @brief The ID of the last played sound
		mutable unsigned _lastPlayedSound = 0;

	public:
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
		mutable std::array<sf::Sound, MAX_PLAYING_SFX> sounds;

		//! @brief The items JSON file loaded.
		std::vector<std::shared_ptr<Item>> items;

		//! @brief The global font
		sf::Font font;

		//! @brief Plays a sound effect
		//! @param id The id of the sound effect to play
		//! @return The sound index assigned to this sfx
		unsigned char playSound(const std::string &id) const;

		//! @brief Plays a music
		//! @param id The id of the music to play
		void playMusic(const std::string &id);

		//! @brief Stops any music currently playing
		void stopMusic();

		//! @brief Changes the volume of all the musics.
		//! @param newVolume New volume.
		void setMusicVolume(float newVolume);

		//! @brief Changes the volume of all the sounds.
		//! @param newVolume New volume.
		void setSoundVolume(float newVolume);

		~Resources() override = default;
	};
}

#endif //THFGAME_RESOURCES_HPP
