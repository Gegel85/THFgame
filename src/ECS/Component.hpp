//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_COMPONENT_HPP
#define THFGAME_COMPONENT_HPP


#include <string>

namespace TouhouFanGame::ECS
{
	class Component {
	private:
		std::string _name;

	public:
		Component(const std::string &name);
		virtual ~Component() = default;
		std::string getName() const;
		virtual void serialize(std::ostream &) const = 0;
		virtual void unserialize(std::istream &) = 0;

		template<typename type>
		type &to()
		{
			return reinterpret_cast<type &>(*this);
		}
	};
}

std::ostream	&operator<<(std::ostream &stream, const TouhouFanGame::ECS::Component &component);
std::istream	&operator>>(std::istream &stream, TouhouFanGame::ECS::Component &component);

#endif //THFGAME_COMPONENT_HPP
