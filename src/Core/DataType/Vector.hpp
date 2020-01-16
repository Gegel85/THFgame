//
// Created by anonymus-raccoon on 1/15/20.
//

#ifndef THFGAME_VECTOR_HPP
#define THFGAME_VECTOR_HPP

#include <ostream>
#include <cmath>

namespace TouhouFanGame {
	template<typename T>
	class Vector2 {
	public:
		T x;
		T y;

		template<typename T2>
		Vector2<T> &operator+=(const Vector2<T2> &vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			return *this;
		}

		template<typename T2>
		Vector2<T> &operator-=(const Vector2<T2> &vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			return *this;
		}

		template<typename T2>
		Vector2<T> &operator*=(T2 d)
		{
			this->x *= d;
			this->y *= d;
			return *this;
		}

		template<typename T2>
		T Distance(const Vector2<T2> &o) const
		{
			return sqrt(pow(this->x - o.x, 2), pow(this->u - o.y, 2));
		}
	};

	template<typename T>
	std::ostream &operator<<(std::ostream &s, const Vector2<T> &v)
	{
		s << "(" << v.x << "," << v.y << ")";
		return s;
	}

	typedef Vector2<float> Vector2f;
}

#endif //THFGAME_VECTOR_HPP
