//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_VECTOR_HPP
#define THFGAME_VECTOR_HPP

#include <ostream>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "../Utils/BaseObject.hpp"

namespace TouhouFanGame
{
	template<typename T>
	class Vector2 : public BaseObject {
	public:
		T x;
		T y;

		Vector2<T>()
			: x(0), y(0) {}

		Vector2<T>(T x, T y)
			: x(x), y(y) {}

		template <typename T2>
		Vector2<T>(Vector2<T2> v)
			: x(v.x), y(v.y) {}

		Vector2<T>(sf::Vector2<T> v)
			: x(v.x), y(v.y) {}

		~Vector2() override = default;

		template <typename T2>
		operator sf::Vector2<T2>()
		{
			return sf::Vector2<T2>(this->x, this->y);
		}

		template<typename T2>
		Vector2<T> &operator+=(const Vector2<T2> &vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			return *this;
		}

		template<typename T2>
		Vector2<T> operator+(const Vector2<T2> &vec) const
		{
			return Vector2<T>(this->x + vec.x, this->y + vec.y);
		}

		template<typename T2>
		Vector2<T> &operator-=(const Vector2<T2> &vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			return *this;
		}

		template<typename T2>
		Vector2<T> operator-(const Vector2<T2> &vec) const
		{
			return Vector2<T>(this->x - vec.x, this->y - vec.y);
		}

		template<typename T2>
		Vector2<T> &operator*=(T2 d)
		{
			this->x *= d;
			this->y *= d;
			return *this;
		}

		template<typename T2>
		Vector2<T> operator*(T2 d) const
		{
			return Vector2<T>(this->x * d, this->y * d);
		}

		template<typename T2>
		T operator*(Vector2<T2> &b) const
		{
			return this->x * b.x + this->y * b.y;
		}

		template<typename T2>
		Vector2<T> operator/=(Vector2<T2> &b)
		{
			this->x /= b.x;
			this->y /= b.y;
			return this;
		}

		template<typename T2>
		Vector2<T> operator/(Vector2<T2> &b) const
		{
			return Vector2<T>(this->x / b.x, this->y / b.y);
		}

		template<typename T2>
		Vector2<T> operator/=(T2 b)
		{
			this->x /= b;
			this->y /= b;
			return this;
		}

		template<typename T2>
		Vector2<T> operator/(T2 b) const
		{
			return Vector2<T>(this->x / b, this->y / b);
		}

		template<typename T2>
		double distance(const Vector2<T2> &o) const
		{
			return std::sqrt(std::pow(this->x - o.x, 2) + std::pow(this->y - o.y, 2));
		}

		double magnitude() const
		{
			return (std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2)));
		}

		double angle(const Vector2<T> &o) const
		{
			return (std::atan(std::abs(o.y - this->y) / std::abs(o.x - this->x)));
		}

		Vector2<T> normalize()
		{
			double mag = this->magnitude();

			this->x /= mag;
			this->y /= mag;
			return *this;
		}

		Vector2<T> normalized() const
		{
			T mag = this->magnitude();

			return Vector2<T>(this->x / mag, this->y / mag);
		}

		Vector2<T> projection(const Vector2<T> &point) const
		{
			return (point * this) / std::pow(this->magnitude(), 2) * this;
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned> Vector2u;
	typedef Vector2<int> Vector2i;
}

template<typename T>
std::ostream &operator<<(std::ostream &s, const TouhouFanGame::Vector2<T> &v)
{
	s << v.x << " " << v.y;
	return s;
}

template<typename T>
std::istream &operator>>(std::istream &s, TouhouFanGame::Vector2<T> &v)
{
	s >> v.x >> v.y;
	return s;
}


#endif //THFGAME_VECTOR_HPP
