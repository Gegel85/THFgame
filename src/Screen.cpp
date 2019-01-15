//
// Created by Gegel85 on 15/01/2019.
//

#include "Logger.hpp"
#include "Screen.hpp"

Screen::Screen()
{
	logger.info("Opening game window");
	this->_window = new sf::RenderWindow(sf::VideoMode(640, 480), "TH Fan Game");
	this->_window->setFramerateLimit(60);
}

Screen::~Screen()
{
	logger.info("Destroying game window");
	delete this->_window;
}

void	Screen::handleEvents()
{
	sf::Event	event;

	while (this->_window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			this->_window->close();
}

bool	Screen::isOpen() const
{
	return this->_window->isOpen();
}

void	Screen::clear(const sf::Color &color) const
{
	this->_window->clear(color);
}

void	Screen::refresh() const
{
	this->_window->display();
}