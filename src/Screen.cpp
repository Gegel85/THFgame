//
// Created by Gegel85 on 15/01/2019.
//

#include "Logger.hpp"
#include "Screen.hpp"

Screen::Screen(const std::string &title) : _title(title)
{
	logger.info("Opening game window \"" + title + "\"");
	this->_window = new sf::RenderWindow(sf::VideoMode(640, 480), title);
	this->_window->setFramerateLimit(60);
}

Screen::Screen(const Screen &other)
{
	logger.info("Opening game window \"" + other.getTitle() + "\"");
	this->_title = other.getTitle();
	this->_window = new sf::RenderWindow(
		sf::VideoMode(other._window->getSize().x, other._window->getSize().y),
		other.getTitle()
	);
}

Screen::~Screen()
{
	logger.info("Destroying game window \"" + this->_title + "\"");
	delete this->_window;
}

const std::string& Screen::getTitle() const
{
	return this->_title;
}

void Screen::setTitle(const std::string &title)
{
	this->_title = title;
	this->_window->setTitle(title);
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