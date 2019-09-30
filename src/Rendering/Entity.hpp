//
// Created by Gegel85 on 23/09/2019
//

#ifndef THFGAME_RENDERING_ENTITY_HPP
#define THFGAME_RENDERING_ENTITY_HPP


#include <SFML/Graphics.hpp>

namespace TouhouFanGame::Rendering
{
	class Screen;

	enum Animation {
		IDLE,
		WALK,
		RUN,
		HIT,
		ATTACKING,
		IDLEANIM1,
		IDLEANIM2,
		DEAD
	};

	enum Direction {
		NORTH,
		NORTH_EAST,
		EAST,
		SOUTH_EAST,
		SOUTH,
		SOUTH_WEST,
		WEST,
		NORTH_WEST,
	};

	class Entity {
	private:
		struct Config {
			Config(const std::string &path);
			sf::Vector2u getPositionFromAnimationIndex(unsigned index);

			std::string		texture;
			sf::Vector2u		textureSize;
			sf::Vector2u		tileSize;
			std::vector<unsigned>	animations;
			std::vector<unsigned>	animationStart;
			std::vector<unsigned>	delays;
		};

		sf::Sprite	_sprite;
		sf::Vector2f	_pos{0, 0};
		sf::Vector2u	_size{0, 0};
		Animation	_animation{IDLE};
		Direction 	_dir{NORTH};
		unsigned int	_idleDelay{0};
		unsigned int	_delay{0};
		unsigned int	_animationState{0};
		Config		_configs;

	public:
		explicit Entity(const std::string &configPath);
		void setAnimation(Animation newAnimation, bool forceReset = true);
		void setPosition(sf::Vector2f newPos);
		void setSize(sf::Vector2u newSize);
		void setDirection(Direction newDir);
		void render(Screen &screen);
		void update();
	};
}


#endif //THFGAME_RENDERING_ENTITY_HPP
