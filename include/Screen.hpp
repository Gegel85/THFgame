//
// Created by Gegel85 on 15/01/2019.
//

#ifndef THFGAME_RESSOURCES_HPP
#define THFGAME_RESSOURCES_HPP


#include <SFML/Graphics.hpp>

class Screen {
private:
	sf::RenderWindow	*_window;
	sf::RectangleShape	_rect;

public:
	Screen();
	Screen(const Screen &);
	~Screen();

	void	handleEvents();
	bool	isOpen() const;
	void	clear(const sf::Color &color = sf::Color(0, 0, 0, 255)) const;
	void	refresh() const;
	void	displayElement(sf::IntRect rect);
	void    fillColor(sf::Color color = sf::Color(255, 255, 255, 255));
};


#endif //THFGAME_RESSOURCES_HPP
