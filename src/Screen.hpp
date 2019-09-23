//
// Created by Gegel85 on 15/01/2019.
//

#ifndef THFGAME_SCREEN_HPP
#define THFGAME_SCREEN_HPP


#include <SFML/Graphics.hpp>

class Screen : public sf::RenderWindow {
private:
	sf::RectangleShape	_rect;
	sf::Text		_text;
	sf::Clock		_clock;
	sf::Sprite		_sprite;
	std::string		_title;

public:
	double	fps;

	explicit Screen(const std::string &title, unsigned int width = 640, unsigned int height = 480);
	Screen(const Screen &);
	~Screen() override;

	void			handleEvents();
	const std::string	&getTitle() const;
	void			setTitle(const std::string &);
	void    		fillColor(const sf::Color &color = sf::Color(255, 255, 255, 255));
	void			setFont(const sf::Font &font);
	void			textSize(const size_t &size);
	void			displayElement(sf::IntRect rect);
	void			displayElement(const std::string &str, sf::Vector2f);
	void			displayElement(sf::Sprite &sprite, sf::Vector2f);
	void			displayElement(sf::Texture &texture, sf::Vector2f);
};


#endif //THFGAME_RESOURCES_HPP
