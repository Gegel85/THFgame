//
// Created by Gegel85 on 27/09/2019.
//

#ifndef THFGAME_COMPONENT_HPP
#define THFGAME_COMPONENT_HPP


#include <string>
#include "../Utils/BaseObject.hpp"

namespace TouhouFanGame::ECS
{
	//! @brief A Component linked to a System
	class Component : public BaseObject {
	private:
		//! @brief The name of this Component
		std::string _name;

	public:
		//! @param name The name of the Component
		Component(const std::string &name);

		virtual ~Component() override = default;

		//! @brief Fetch the name of the Entity.
		//! @return The name of this Entity.
		std::string getName() const;

		//! @brief Serialize to a stream.
		//! @param stream to load to.
		virtual void serialize(std::ostream &stream) const = 0;

		template<typename type>
		//! @brief Transforms this Component to the type.
		//! @warning When calling this, be SURE that this Component is the type given.
		//! If it isn't, it will cast it anyway and won't report any error.
		type &to()
		{
#ifdef _DEBUG
			return dynamic_cast<type &>(*this);
#else
			return reinterpret_cast<type &>(*this);
#endif
		}
	};
}

std::ostream &test(std::ostream &stream, const TouhouFanGame::ECS::Component &component);
std::ostream &operator<<(std::ostream &stream, const TouhouFanGame::ECS::Component &component);


#endif //THFGAME_COMPONENT_HPP
