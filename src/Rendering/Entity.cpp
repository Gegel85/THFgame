//
// Created by Gegel85 on 23/09/2019
//

#include <fstream>
#include "Entity.hpp"
#include "Exceptions.hpp"
#include "../nlohmann/json.hpp"
#include "../Game.hpp"

namespace TouhouFanGame::Rendering
{
	Entity::Config::Config(const std::string &texture, const sf::Vector2f &tileSize, const std::vector<unsigned> &animation) :
		texture(texture),
		tileSize(tileSize),
		animations(animation)
	{}

	Entity::Config::Config(const std::string &path)
	{
		std::ifstream stream{path};
		nlohmann::json value;

		if (stream.fail())
			throw InvalidAnimationConfigException("Cannot open file " + path);

		try {
			stream >> value;
			this->texture = value["texture"];
			this->tileSize = {value["tileSize"]["x"], value["tileSize"]["y"]};
			for (auto &val : value["animations"])
				this->animations.push_back(val);
			game.resources.textures.at(this->texture);
		} catch (std::out_of_range &) {
			throw InvalidAnimationConfigException("The texture given is not loaded: " + this->texture);
		} catch (nlohmann::detail::parse_error &e) {
			throw InvalidAnimationConfigException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw InvalidAnimationConfigException("The JSON values are invalid: " + std::string(e.what()));
		}
		if (this->animations.size() < IDLEANIM2 * 4 + 1)
			throw InvalidAnimationConfigException(
				"Not enough animations are present in the file (Expected at least " +
				std::to_string(IDLEANIM2 * 4 + 1) + " but found " + std::to_string(this->animations.size()) + ")"
			);
	}

	Entity::Entity(const std::string &configPath) :
		_configs(configPath)
	{
	}

	void Entity::setAnimation(Animation newAnimation, bool forceReset)
	{
		if (this->_animation == newAnimation && !forceReset)
			return;

		if ((this->_animation == IDLEANIM2 || this->_animation == IDLEANIM1) && newAnimation == IDLE && !forceReset)
			return;

		this->_animation = newAnimation;
		this->_animationState = 0;
	}

	void Entity::setSize(sf::Vector2u newSize)
	{
		this->_size = newSize;
	}

	void Entity::setPosition(sf::Vector2f newPos)
	{
		this->_pos = newPos;
	}

	void Entity::setDirection(TouhouFanGame::Rendering::Direction newDir)
	{
		this->_dir = newDir;
	}

	void Entity::render(Rendering::Screen &screen)
	{
		this->_sprite.setTexture(game.resources.textures.at(this->_configs.texture));
		this->_sprite.setScale({
			this->_size.x / static_cast<float>(this->_configs.tileSize.x),
			this->_size.x / static_cast<float>(this->_configs.tileSize.y)
		});
		this->_sprite.setTextureRect({
			static_cast<int>(this->_animationState * this->_configs.tileSize.x),
			static_cast<int>(this->_animation * this->_configs.tileSize.y * 4 + ((this->_animation != DEAD) * this->_dir * this->_configs.tileSize.y)),
			static_cast<int>(this->_configs.tileSize.x),
			static_cast<int>(this->_configs.tileSize.y)
		});
		screen.draw(
			this->_sprite,
			this->_pos
		);

		if (!this->_delay) {
			std::uniform_int_distribution distribution{0, 59};
			std::uniform_int_distribution distribution2{0, 1};

			switch (this->_animation) {
			case IDLE:
				if (!distribution(game.resources.random)) {
					this->_delay = 1;
					this->_animation = static_cast<Animation>(IDLEANIM1 + distribution2(game.resources.random));
					this->_animationState = -1;
				} else
					this->_delay = 20;
				break;
			case WALK:
			case RUN:
			case ATTACKING:
				this->_delay = 5;
				break;
			case IDLEANIM1:
			case IDLEANIM2:
				this->_delay = 5;
				if (this->_animationState + 1 == this->_configs.animations[this->_animation * 4 + ((this->_animation != DEAD) * this->_dir)])
					this->_animation = IDLE;
				break;
			case HIT:
				this->_delay = 5 - (this->_animationState + 2 == this->_configs.animations[this->_animation * 4 + ((this->_animation != DEAD) * this->_dir)]) * 3;
				if (this->_animationState + 1 == this->_configs.animations[this->_animation * 4 + ((this->_animation != DEAD) * this->_dir)])
					this->_animation = IDLE;
				break;
			case DEAD:
				this->_delay = 5 - (this->_animationState + 2 == this->_configs.animations[this->_animation * 4 + ((this->_animation != DEAD) * this->_dir)]) * 3;
				break;
			}
			this->_animationState = (this->_animationState + 1) % this->_configs.animations[this->_animation * 4 + ((this->_animation != DEAD) * this->_dir)];
		} else
			this->_delay--;
	}
}