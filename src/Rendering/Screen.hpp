//
// Created by Gegel85 on 15/01/2019.
//

#ifndef THFGAME_SCREEN_HPP
#define THFGAME_SCREEN_HPP


#include <SFML/Graphics.hpp>
#include "Entity.hpp"

namespace TouhouFanGame::Rendering
{
	class Screen : public sf::RenderWindow {
	private:
		sf::Vector2f		_camera{0, 0};
		sf::View		_view;
		std::vector<Entity>	_entities;
		sf::RectangleShape	_rect;
		sf::Text		_text;
		sf::Clock		_clock;
		sf::Sprite		_sprite;
		std::string		_title;
		double			_fps;
		sf::Vector2u		_size;

	public:

		explicit Screen(const std::string &title, unsigned int width = 640, unsigned int height = 480);
		Screen(const Screen &);
		~Screen() override;

		const std::string	&getTitle() const;
		void			setTitle(const std::string &);
		void    		fillColor(const sf::Color &color = sf::Color(255, 255, 255, 255));
		void			setFont(const sf::Font &font);
		void			textSize(const size_t &size);
		Entity			&addEntity(const std::string &configFile);
		void			deleteEntities();
		void			removeEntity(Entity &);
		void			renderEntities();
		void			setCamera(sf::Vector2f);
		void			draw(sf::IntRect rect);
		void			draw(const std::string &str, sf::Vector2f);
		void			draw(sf::Sprite &sprite, sf::Vector2f);
		void			draw(sf::Texture &texture, sf::Vector2f, sf::IntRect rect = {0, 0, 0, 0});
		double			getFPS();
		void			display();
	};
}


#endif //THFGAME_RESOURCES_HPP
