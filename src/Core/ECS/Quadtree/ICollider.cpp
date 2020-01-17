//
// Created by anonymus-raccoon on 1/17/20.
//

#include <ostream>
#include <istream>
#include "ICollider.hpp"
#include "RectangleCollider.hpp"
#include "CircleCollider.hpp"
#include "../Exceptions.hpp"

namespace TouhouFanGame::ECS::Quadtree
{
	std::ostream &operator<<(std::ostream &stream, const ICollider &collider)
	{
		collider.serialize(stream);
		return stream;
	}

	std::istream &operator>>(std::istream &stream, std::unique_ptr<ICollider> &collider)
	{
		collider = ICollider::deserialize(stream);
		return stream;
	}

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
}