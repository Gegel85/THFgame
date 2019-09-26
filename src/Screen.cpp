//
// Created by Gegel85 on 15/01/2019.
//

#include "Game.hpp"
#include "Screen.hpp"

Screen::Screen(const std::string &title, unsigned int width, unsigned int height) :
	sf::RenderWindow(sf::VideoMode(width, height), title),
	_title(title),
	_fps(60)
{
	TouhouFanGame::logger.info("Opening window \"" + title + "\"");
	this->setFramerateLimit(60);
	this->_text.setOutlineThickness(0);
	this->_rect.setOutlineThickness(0);
}

Screen::Screen(const Screen &other) :
	Screen(other.getTitle(), other.getSize().x, other.getSize().y)
{
}

Screen::~Screen()
{
	TouhouFanGame::logger.info("Destroying window \"" + this->_title + "\"");
}

const std::string &Screen::getTitle() const
{
	return this->_title;
}

void Screen::setTitle(const std::string &title)
{
	this->_title = title;
	sf::RenderWindow::setTitle(title);
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

void	Screen::draw(sf::IntRect rect)
{
	this->_rect.setPosition(sf::Vector2f(rect.left, rect.width));
	this->_rect.setSize(sf::Vector2f(rect.width, rect.height));
	sf::RenderWindow::draw(this->_rect);
}

void	Screen::draw(const std::string &str, sf::Vector2f pos)
{
	this->_text.setPosition(pos);
	this->_text.setString(str);
	sf::RenderWindow::draw(this->_text);
}

void	Screen::draw(sf::Sprite &sprite, sf::Vector2f pos)
{
	sprite.setPosition(pos);
	sf::RenderWindow::draw(sprite);
}

void	Screen::draw(sf::Texture &texture, sf::Vector2f pos, sf::IntRect rect)
{
	if (!rect.width)
		rect.width = texture.getSize().x - rect.left;

	if (!rect.height)
		rect.height = texture.getSize().y - rect.top;

	this->_sprite.setTexture(texture, true);
	this->_sprite.setTextureRect(rect);
	this->draw(this->_sprite, pos);
}