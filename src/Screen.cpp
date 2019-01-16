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

Screen::Screen(const Screen &other)
{
	this->_window = new sf::RenderWindow(
		sf::VideoMode(other._window->getSize().x, other._window->getSize().y),
		"TH Fan Game"
	);
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


void	Screen::displayElement(sf::IntRect rect)
{
	this->_rect.setPosition(sf::Vector2f(rect.left, rect.width));
	this->_rect.setSize(sf::Vector2f(rect.width, rect.height));
	this->_window->draw(this->_rect);
}

void    Screen::fillColor(sf::Color color)
{
	this->_rect.setFillColor(color);
}