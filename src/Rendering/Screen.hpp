//
// Created by Gegel85 on 15/01/2019.
//

#ifndef THFGAME_SCREEN_HPP
#define THFGAME_SCREEN_HPP


#include <SFML/Graphics.hpp>

namespace Rendering
{
	class Screen : public sf::RenderWindow {
	private:
		sf::RectangleShape	_rect;
		sf::Text		_text;
		sf::Clock		_clock;
		sf::Sprite		_sprite;
		std::string		_title;
		double			_fps;

	public:

		explicit Screen(const std::string &title, unsigned int width = 640, unsigned int height = 480);
		Screen(const Screen &);
		~Screen() override;

		const std::string	&getTitle() const;
		void			setTitle(const std::string &);
		void    		fillColor(const sf::Color &color = sf::Color(255, 255, 255, 255));
		void			setFont(const sf::Font &font);
		void			textSize(const size_t &size);
		void			draw(sf::IntRect rect);
		void			draw(const std::string &str, sf::Vector2f);
		void			draw(sf::Sprite &sprite, sf::Vector2f);
		void			draw(sf::Texture &texture, sf::Vector2f, sf::IntRect rect = {0, 0, 0, 0});
	};
}


#endif //THFGAME_RESOURCES_HPP
