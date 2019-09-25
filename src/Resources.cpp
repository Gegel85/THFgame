//
// Created by Gegel85 on 24/09/2019.
//

#include "Resources.hpp"

unsigned char Game::Resources::playSound(const std::string &id)
{
	static char lastSound = 127;

	lastSound++;
	if (lastSound < 0)
		lastSound = 0;

	this->sounds[lastSound].setBuffer(this->soundBuffers.at(id));
	this->sounds[lastSound].play();
	return lastSound;
}