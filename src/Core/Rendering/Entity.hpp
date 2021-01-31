//
// Created by Gegel85 on 23/09/2019
//

#ifndef THFGAME_RENDERING_ENTITY_HPP
#define THFGAME_RENDERING_ENTITY_HPP


#include <SFML/Graphics.hpp>
#include "../DataType/Vector.hpp"

namespace TouhouFanGame
{
	struct Resources;
}

namespace TouhouFanGame::Rendering
{
	class Screen;

	//! @brief All the animations
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

	//! @brief All the direction of an entity
	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
	};

	//! @brief An entity that can be rendered on a Screen
	class Entity {
	private:
		//! @brief The configs of an entity
		struct Config {
			//! @param resources Game Resources.
			//! @param path The path to the file to be loaded.
			Config(Resources &resources, const std::string &path);

			//! @brief Fetch the position on the sprite sheet of a tile.
			//! @param index The index of the tile.
			//! @return The position on the sprite sheet of that tile.
			Vector2u getPositionFromAnimationIndex(unsigned index);

			//! @brief Loads a file.
			void loadFile(Resources &resources, const std::string &path);

			//! @brief The texture index.
			std::string	texture;

			//! @brief The texture size.
			Vector2u	textureSize;

			//! @brief The size of a single tile in pixel.
			Vector2u	tileSize;

			//! @brief The number of tiles for each animation.
			std::vector<unsigned>	animations;

			//! @brief The start of each animation's first tile.
			std::vector<unsigned>	animationStart;

			//! @brief The time to wait before switching to the next tile of this animation.
			std::vector<unsigned>	delays;

			bool ignoreDirections;
			bool noIdleAnimation;
		};

		//! @brief The resources this Entity can use.
		Resources &_resources;

		//! @brief Used to draw the entity on the Screen.
		sf::Sprite	_sprite;

		//! @brief The current position oon the Screen.
		Vector2f	_pos{0, 0};

		//! @brief The current size.
		Vector2u	_size{0, 0};

		//! @brief The current animation.
		Animation	_animation{IDLE};

		//! @brief The direction the entity is facing.
		Direction 	_dir{NORTH};

		//! @brief Internal clock to prevent idle animation to start to early.
		unsigned int	_idleDelay{0};

		//! @brief Internal clock used to know when to switch to the next tile.
		unsigned int	_delay{0};

		//! @brief The current tile used of this animation.
		unsigned int	_animationState{0};

		//! @brief The sprite orientation.
		float		_angle = 0;

		//! @brief The configs for this entity.
		Config		_configs;

	public:
		//! @param resources Game Resources.
		//! @param configPath Path to the JSON config file to load.
		explicit Entity(Resources &resources, const std::string &configPath);

		//! @brief Changes the current animation.
		//! @param newAnimation The new animation to use.
		//! @param forceReset Skip the checks and reset the animation anyway.
		//! @details This function also resets the current animation tile used.
		//! Some checks are made to prevent unwanted resets.
		//! (check if the animation is the one currently used or if trying to IDLE during and IDLEANIM).
		//! This can cause issues if you want to reset back to IDLE while the entity is doing and IDLEANIM.
		//! If you want to override this behaviour, set forceReset to true.
		//! It will discard the check results and change the animation no matter what.
		void setAnimation(Animation newAnimation, bool forceReset = true);

		//! @brief Change the position of the entity on the Screen.
		void setPosition(Vector2f newPos);

		//! @brief Sets the size of the entity.
		void setSize(Vector2u newSize);

		//! @brief Set the sprite orientation (in radian).
		void setSpriteAngle(float newAngle);

		//! @brief Sets the facing direction of the entity.
		void setDirection(Direction newDir);

		//! @brief Render and entity on the screen.
		void render(Screen &screen);

		//! @brief Updates the entity's state.
		void update();

		//! @brief Loads a new config file to replace the old configs.
		void setConfigs(const std::string &path);
	};
}


#endif //THFGAME_RENDERING_ENTITY_HPP
