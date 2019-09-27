//
// Created by Gegel85 on 23/09/2019
//

#ifndef THFGAME_RENDERING_ENTITY_HPP
#define THFGAME_RENDERING_ENTITY_HPP


#include <SFML/Graphics.hpp>

namespace TouhouFanGame::Rendering
{
	class Screen;

	class Entity {
	private:
		struct Config {
			Config(const std::string &path);
			Config(const std::string &texture, const sf::Vector2f &tileSize, const std::vector<unsigned> &animation);

			std::string		texture;
			sf::Vector2f		tileSize;
			std::vector<unsigned>	animations;
		};

		mutable sf::Sprite	_sprite;
		sf::Vector2f		_pos{0, 0};
		sf::Vector2u		_size{0, 0};
		unsigned int		_animation{0};
		unsigned int		_animationState{0};
		Config			_configs;

	public:
		explicit Entity(const std::string &configPath);
		void setAnimation(unsigned newAnimation, bool forceReset = true);
		void setPosition(sf::Vector2f newPos);
		void setSize(sf::Vector2u newSize);
		void render(Screen &screen) const;
	};
}


#endif //THFGAME_RENDERING_ENTITY_HPP
