//
// Created by Gegel85 on 24/09/2019.
//

#include "Resources.hpp"
#include "Game.hpp"

namespace TouhouFanGame
{
	unsigned char Resources::playSound(const std::string &id)
	{
		static unsigned char lastSound = 127;

		lastSound = (lastSound + 1) % 128;

		try {
			this->sounds[lastSound].setBuffer(this->soundBuffers.at(id));
			this->sounds[lastSound].play();
		} catch (std::out_of_range &e) {
			logger.error("Cannot play sound " + id);
		}
		return lastSound;
	}

	void Resources::playMusic(const std::string &id)
	{
		this->stopMusic();
		try {
			this->musics.at(id).play();
		} catch (std::out_of_range &e) {
			logger.error("Cannot play sound " + id);
		}
	}

	void Resources::stopMusic()
	{
		for (auto &music : this->musics)
			music.second.stop();
	}
}