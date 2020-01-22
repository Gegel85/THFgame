//
// Created by Gegel85 on 27/09/2019.
//


#ifndef THFGAME_SYSTEM_HPP
#define THFGAME_SYSTEM_HPP


#include <string>
#include <vector>
#include "Entity.hpp"

namespace TouhouFanGame::ECS
{
	class Core;

	//! @brief A System, affecting Entities.
	//! The updateEntity method is called only if this Entity has the corresponding Component
	//! (a Component that has the same name as the System)
	class System {
	private:
		//! @brief The name of the System
		std::string _name;

		//! @brief All the Component required for this System to work
		std::vector<std::string> _deps;

	protected:
		//! @brief The Core the System is in
		Core &_core;

	public:
		//! @param _parent The Core the System is in
		//! @param name The name of the System
		//! @param dependencies All the Component required for this System to work
		System(Core &_parent, const std::string &&name, const std::vector<std::string> &&dependencies);

		//! @brief Check if the entity match the dependencies
		//! @param entity The entity to verify
		//! @throw MissingDependencyException
		void	checkDependencies(const Entity &entity) const;

		//! @brief Get the dependencies needed by this System.
		const std::vector<std::string> &getDependencies() const;

		//! @brief Gets the name of the System
		//! @return The name of the System
		std::string	getName() const;

		//! @brief Applies the System logic to the entity
		//! @param entity Entity to update
		virtual void	updateEntity(const std::shared_ptr<Entity> &entity) = 0;

		//! @brief Updates the System components if needed.
		virtual void	update();
	};
}


#endif //THFGAME_SYSTEM_HPP
