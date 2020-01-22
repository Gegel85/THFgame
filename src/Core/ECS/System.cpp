//
// Created by Gegel85 on 27/09/2019.
//

#include "System.hpp"
#include "Exceptions.hpp"

namespace TouhouFanGame::ECS
{
	System::System(Core &core, const std::string &&name, const std::vector<std::string> &&dependencies) :
		_name(name),
		_deps(dependencies),
		_core(core)
	{
	}

	std::string System::getName() const
	{
		return this->_name;
	}

	void System::update()
	{
	}

	void System::checkDependencies(const TouhouFanGame::ECS::Entity &entity) const
	{
		for (auto &dep : this->_deps)
			if (!entity.hasComponent(dep))
				throw MissingDependencyException(
					"Entity n°" + std::to_string(entity.getID()) +
					" is missing a " + dep + "Component required by " +
					this->_name + "System"
				);
	}

	const std::vector<std::string> &System::getDependencies() const
	{
		return this->_deps;
	}
}