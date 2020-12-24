//
// Created by Gegel85 on 24/09/2019.
//

#include "Resources.hpp"
#include "Game.hpp"

namespace TouhouFanGame
{
	unsigned char Resources::playSound(const std::string &id) const
	{
		this->_lastPlayedSound = (this->_lastPlayedSound + 1) % this->sounds.size();
		try {
			this->sounds[this->_lastPlayedSound].setBuffer(this->soundBuffers.at(id));
			this->sounds[this->_lastPlayedSound].play();
		} catch (std::out_of_range &e) {
			logger.error("Cannot play sound " + id);
		}
		return this->_lastPlayedSound;
	}

	void Resources::playMusic(const std::string &id)
	{
		try {
			if (this->musics.at(id).first.getStatus() == sf::Music::Playing)
				return;
		} catch (std::out_of_range &e) {
			return logger.error("Cannot play music " + id);
		}

		this->stopMusic();
		this->musics.at(id).first.play();
	}

	void Resources::stopMusic()
	{
		for (auto &music : this->musics)
			music.second.first.stop();
	}

	void Resources::setMusicVolume(float newVolume)
	{
		for (auto &music : this->musics)
			music.second.first.setVolume(newVolume);
	}

	void Resources::setSoundVolume(float newVolume)
	{
		for (auto &sound : this->sounds)
			sound.setVolume(newVolume);
	}
}