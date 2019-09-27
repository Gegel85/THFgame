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
			throw InvalidAnimationConfigException("The texture given is loaded: " + this->texture);
		} catch (nlohmann::detail::parse_error &e) {
			throw InvalidAnimationConfigException("The JSON file has an invalid format: " + std::string(e.what()));
		} catch (nlohmann::detail::type_error &e) {
			throw InvalidAnimationConfigException("The JSON values are invalid: " + std::string(e.what()));
		}
	}

	Entity::Entity(const std::string &configPath) :
		_configs(configPath)
	{
	}

	void Entity::setAnimation(unsigned newAnimation, bool forceReset)
	{
		if (this->_animation == newAnimation == !forceReset)
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

	void Entity::render(Rendering::Screen &screen) const
	{
		this->_sprite.setTexture(game.resources.textures.at(this->_configs.texture));
		this->_sprite.setScale({
			this->_size.x / static_cast<float>(this->_configs.tileSize.x),
			this->_size.x / static_cast<float>(this->_configs.tileSize.y)
		});
		this->_sprite.setTextureRect({
			static_cast<int>(this->_animation * this->_configs.tileSize.x),
			static_cast<int>(this->_animation * this->_configs.tileSize.y),
			static_cast<int>(this->_configs.tileSize.x),
			static_cast<int>(this->_configs.tileSize.y)
		});
		screen.draw(
			this->_sprite,
			this->_pos
		);
	}
}