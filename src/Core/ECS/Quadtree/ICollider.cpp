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
#include "ColliderFactory.hpp"


std::ostream &operator<<(std::ostream &stream, const TouhouFanGame::ECS::Quadtree::ICollider &collider)
{
	collider.serialize(stream);
	return stream;
}

std::istream &operator>>(std::istream &stream, std::unique_ptr<TouhouFanGame::ECS::Quadtree::ICollider> &collider)
{
	std::string name;

	stream >> name;
	collider.reset(TouhouFanGame::ECS::Quadtree::ColliderFactory::build(name, stream));
	return stream;
}

namespace TouhouFanGame::ECS::Quadtree
{
	ICollider::ICollider(const std::string &&name, std::istream &stream) :
		_name(name)
	{

	}

	ICollider::ICollider(const std::string &&name, Vector2f offset, Vector2u size, float angle, Vector2f origin) :
		ICollider(static_cast<const std::string &&>(name), offset, offset + size / 2, angle, origin)
	{
	}

	ICollider::ICollider(const std::string &&name, Vector2f offset, Vector2f center, float angle, Vector2f origin) :
		_angle(angle),
		_origin(origin),
		_offset(offset),
		_center(center),
		_name(name)
	{
	}

	/*std::unique_ptr<ICollider> ICollider::deserialize(std::istream &stream)
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
	}*/

	bool ICollider::collideWith(const std::shared_ptr<Entity> &entity) const
	{
		if (entity->hasComponent("Collision")) {
			auto &col = entity->getComponent(Collision);
			return this->collideWith(*col.collider);
		} else {
			auto &col = entity->getComponent(Collider);
			return this->getCollisionLayer(col.colliders) >= 0;
		}
	}

	void ICollider::link(const Components::PositionComponent &pos)
	{
		if (pos.angle != this->_angle) {
			this->_center = pos.position + pos.size / 2;
			this->setRotation(pos.angle);
		}
		this->setOrigin(pos.position);
	}

	void ICollider::serialize(std::ostream &stream) const
	{
		stream << this->_origin << " " << this->_center << " " << this->_angle << " " << this->_offset;
		this->_serialize(stream);
	}

	const Vector2f &ICollider::getOrigin() const
	{
		return this->_origin;
	}

	const Vector2f &ICollider::getCenter() const
	{
		return this->_center;
	}

	const std::string &ICollider::getName() const
	{
		return this->_name;
	}

	void ICollider::setOrigin(const Vector2f &origin)
	{
		this->_origin = origin;
	}

	void ICollider::setOffset(const Vector2f &offset)
	{
		this->_center += offset - this->_offset;
		this->_offset = offset;
	}

	void ICollider::setRotation(float angle)
	{
		this->_angle = angle;
	}

	int ICollider::getCollisionLayer(const std::vector<std::unique_ptr<ICollider>> &colliders) const
	{
		int layer = 0;

		for (auto &collider : colliders)
			if (collider->collideWith(*this))
				return layer;
			else
				layer++;
		return -1;
	}
}