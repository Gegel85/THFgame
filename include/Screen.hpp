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
	std::string		_title;

public:
	explicit Screen(const std::string &title = "TH Fan Game");
	Screen(const Screen &);
	~Screen();

	void			handleEvents();
	bool			isOpen() const;
	const std::string	&getTitle() const;
	void			setTitle(const std::string &);
	void			clear(const sf::Color &color = sf::Color(0, 0, 0, 255)) const;
	void			refresh() const;
	void			displayElement(sf::IntRect rect);
	void    		fillColor(sf::Color color = sf::Color(255, 255, 255, 255));
};


#endif //THFGAME_RESSOURCES_HPP
