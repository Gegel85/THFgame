//
// Created by Gegel85 on 23/09/2019
//

#include <fstream>
#include <iostream>
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
			unsigned counter = 0;

			stream >> value;
			this->texture = value["texture"];
			this->tileSize = {value["tileSize"]["x"], value["tileSize"]["y"]};
			for (auto &val : value["animations"]) {
				if (val == 0)
					throw InvalidAnimationConfigException("");
				this->animations.push_back(val);
			}
			for (auto &val : value["delays"])
				this->delays.push_back(val);
			for (int i = 0; i < DEAD; i++)
				for (int j = 0; j < 8; j++) {
					this->animationStart.emplace_back(counter);
					counter += this->animations[i];
				}
			this->animationStart.emplace_back(counter);
			this->textureSize = game.resources.textures.at(this->texture).getSize();
			if (this->textureSize.x % this->tileSize.x || this->textureSize.y % this->tileSize.y)
				throw InvalidAnimationConfigException(
					"The texture chosen (" + this->texture +
					") size isn't a perfect grid of " +
					std::to_string(this->tileSize.x) + "x" + std::to_string(this->tileSize.y) +
					" tiles"
				);
		} catch (std::out_of_range &) {
			throw InvalidAnimationConfigException("The texture given is not loaded: " + this->texture);
		} catch (nlohmann::detail::parse_error &e) {
			throw InvalidAnimationConfigException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw InvalidAnimationConfigException("The JSON values are invalid: " + std::string(e.what()));
		}
		if (this->animations.size() != DEAD + 1)
			throw InvalidAnimationConfigException(
				"Expected " + std::to_string(DEAD + 1) + " animations but found " + std::to_string(this->animations.size())
			);
		if (this->delays.size() != DEAD + 1)
			throw InvalidAnimationConfigException(
				"Expected " + std::to_string(DEAD + 1) + " delays but found " + std::to_string(this->delays.size())
			);
	}

	sf::Vector2u Entity::Config::getPositionFromAnimationIndex(unsigned index)
	{
		return {
			(this->tileSize.x * index) % this->textureSize.x,
			(this->tileSize.x * index) / this->textureSize.x * this->tileSize.y,
		};
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

		this->_idleDelay = 300;
		this->_animation = newAnimation;
		this->_animationState = 0;
		this->_delay = this->_configs.delays[newAnimation];
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
		unsigned char	dir = (this->_animation != DEAD) * this->_dir;
		unsigned char	animation = this->_animation * 8 + dir;
		sf::Vector2u	pos = this->_configs.getPositionFromAnimationIndex(this->_configs.animationStart[animation] + this->_animationState);

		this->_sprite.setTexture(game.resources.textures.at(this->_configs.texture));
		this->_sprite.setScale({
			this->_size.x / static_cast<float>(this->_configs.tileSize.x),
			this->_size.x / static_cast<float>(this->_configs.tileSize.y)
		});
		this->_sprite.setTextureRect({
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			static_cast<int>(this->_configs.tileSize.x),
			static_cast<int>(this->_configs.tileSize.y)
		});
		screen.draw(
			this->_sprite,
			this->_pos
		);
	}

	void Entity::update()
	{
		if (!this->_idleDelay) {
			std::uniform_int_distribution distribution{0, 59};
			std::uniform_int_distribution distribution2{0, 1};

			if (!distribution(game.resources.random)) {
				this->_animation = static_cast<Animation>(IDLEANIM1 + distribution2(game.resources.random));
				this->_animationState = 0;
				this->_delay = this->_configs.delays[this->_animation];
			}
			this->_idleDelay = 20;
		} else
			this->_idleDelay -= this->_animation == IDLE;

		if (!this->_delay) {
			this->_delay = this->_configs.delays[this->_animation];
			switch (this->_animation) {
				case IDLEANIM1:
				case IDLEANIM2:
				case HIT:
					if (this->_animationState + 1 == this->_configs.animations[this->_animation])
						this->_animation = IDLE;
					break;
				case DEAD:
					if (this->_animationState + 2 == this->_configs.animations[this->_animation])
						this->_delay = -1;
					break;
				default:
					break;
			}
			this->_animationState = (this->_animationState + 1) % this->_configs.animations[this->_animation];
		} else
			this->_delay--;
	}
}