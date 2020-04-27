//
// Created by anonymus-raccoon on 1/16/20.
//

#ifndef THFGAME_ICOLLIDER_HPP
#define THFGAME_ICOLLIDER_HPP


#include "../Entity.hpp"
#include "../Components/PositionComponent.hpp"
#include "../../Rendering/Screen.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	class ICollider {
	protected:
		float _angle;
		Vector2f _origin;
		Vector2f _offset;
		Vector2f _center;
		std::string _name;

		ICollider(const std::string &&name, std::istream &stream);
		ICollider(const std::string &&name, Vector2f offset, Vector2u size, float angle = 0, Vector2f origin = {0, 0});
		ICollider(const std::string &&name, Vector2f offset, Vector2f center, float angle = 0, Vector2f origin = {0, 0});

		virtual void _serialize(std::ostream &stream) const = 0;

	public:
		const Vector2f &getOrigin() const;
		const Vector2f &getCenter() const;
		const std::string &getName() const;

		void link(const Components::PositionComponent &pos);
		virtual void setOrigin(const Vector2f &origin);
		virtual void setOffset(const Vector2f &offset);
		virtual void setRotation(float angle);

		bool collideWith(const std::shared_ptr<Entity> &entity) const;

		virtual bool collideWith(const class CircleCollider &col) const = 0;
		virtual bool collideWith(const class RectangleCollider &col) const = 0;
		virtual bool collideWith(const ICollider &col) const = 0;

		int getCollisionLayer(const std::vector<std::unique_ptr<ICollider>> &colliders) const;

		void serialize(std::ostream &stream) const;
		virtual void draw(Rendering::Screen &screen) const = 0;

		virtual bool operator>(const ICollider &) const = 0;
		virtual bool operator>(const class CircleCollider &) const = 0;
		virtual bool operator>(const class RectangleCollider &) const = 0;
	};
}

std::ostream &operator<<(std::ostream &stream, const TouhouFanGame::ECS::Quadtree::ICollider &collider);
std::istream &operator>>(std::istream &stream, std::unique_ptr<TouhouFanGame::ECS::Quadtree::ICollider> &collider);

#endif //THFGAME_ICOLLIDER_HPP
