//
// Created by Gegel85 on 15/01/2019.
//

#include "Game.hpp"
#include "Screen.hpp"

Screen::Screen(const std::string &title, unsigned int width, unsigned int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title), _title(title)
{
	Game::logger.info("Opening window \"" + title + "\"");
	this->setFramerateLimit(60);
}

Screen::Screen(const Screen &other) :
	sf::RenderWindow(sf::VideoMode(other.getSize().x, other.getSize().y), other.getTitle())
{
	Game::logger.info("Opening window \"" + other.getTitle() + "\"");
	this->_title = other.getTitle();
	this->setFramerateLimit(60);
	this->setSize(other.getSize());
	this->setPosition(other.getPosition());
}

Screen::~Screen()
{
	Game::logger.info("Destroying window \"" + this->_title + "\"");
}

const std::string& Screen::getTitle() const
{
	return this->_title;
}

void Screen::setTitle(const std::string &title)
{
	this->_title = title;
	sf::RenderWindow::setTitle(title);
}

void	Screen::displayElement(sf::IntRect rect)
{
	this->_rect.setPosition(sf::Vector2f(rect.left, rect.width));
	this->_rect.setSize(sf::Vector2f(rect.width, rect.height));
	this->draw(this->_rect);
}

void    Screen::fillColor(const sf::Color &color)
{
	this->_rect.setFillColor(color);
	this->_text.setFillColor(color);
}

void	Screen::setFont(const sf::Font &font)
{
	this->_text.setFont(font);
}

void	Screen::textSize(const size_t &size)
{
	this->_text.setCharacterSize(size);
}

void	Screen::displayElement(const std::string &str, sf::Vector2f pos)
{
	this->_text.setPosition(pos);
	this->_text.setString(str);
	this->draw(this->_text);
}

void	Screen::displayElement(sf::Sprite &sprite, sf::Vector2f pos)
{
	sprite.setPosition(pos);
	this->draw(sprite);
}

void	Screen::displayElement(sf::Texture &texture, sf::Vector2f pos)
{
	this->_sprite.setPosition(pos);
	this->_sprite.setTexture(texture, true);
	this->draw(this->_sprite);
}