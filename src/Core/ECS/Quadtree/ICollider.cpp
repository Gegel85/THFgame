//
// Created by anonymus-raccoon on 1/17/20.
//

#include <ostream>
#include <istream>
#include "ICollider.hpp"
#include "RectangleCollider.hpp"
#include "CircleCollider.hpp"
#include "../Exceptions.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../Components/ColliderComponent.hpp"


std::ostream &operator<<(std::ostream &stream, const TouhouFanGame::ECS::Quadtree::ICollider &collider)
{
	collider.serialize(stream);
	return stream;
}

std::istream &operator>>(std::istream &stream, std::unique_ptr<TouhouFanGame::ECS::Quadtree::ICollider> &collider)
{
	collider = TouhouFanGame::ECS::Quadtree::ICollider::deserialize(stream);
	return stream;
}

namespace TouhouFanGame::ECS::Quadtree
{
	ICollider::ICollider(float offsetX, float offsetY, float sizeX, float sizeY)
		: offset(offsetX, offsetY), size(sizeX, sizeY)
	{ }

	std::unique_ptr<ICollider> ICollider::deserialize(std::istream &stream)
	{
		int colliderType;
		float x, y, w, h, angle, size;

		stream >> colliderType;
		switch (colliderType) {
		case 0:
			stream >> x >> y >> size;
			if (stream.fail())
				throw InvalidSerializedString("Invalid Collision Component Values");
			return std::make_unique<CircleCollider>(x, y, size);
		case 1:
			stream >> x >> y >> w >> h >> angle;
			if (stream.fail())
				throw InvalidSerializedString("Invalid Collision Component Values");
			return std::make_unique<RectangleCollider>(x, y, w, h, angle);
		default:
			throw InvalidSerializedString("Invalid Collision Component collider type");
		}
	}

	bool ICollider::collideWithEntity(const std::shared_ptr<Entity> &entity) const
	{
		if (entity->hasComponent("Collision")) {
			auto &col = entity->getComponent("Collision").to<Components::CollisionComponent>();
			return this->getCollisionLayer(*col.collider) > 0;
		} else {
			auto &col = entity->getComponent("Collider").to<Components::ColliderComponent>();
			return this->getCollisionLayer(col.colliders) > 0;
		}
	}
}