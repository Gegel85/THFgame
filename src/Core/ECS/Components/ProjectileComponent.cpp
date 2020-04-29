//
// Created by Gegel85 on 28/04/2020.
//

#include "ProjectileComponent.hpp"
#include "../../Utils/Utils.hpp"
#include "../../ExternalCode/ExternalModuleFactory.hpp"

namespace TouhouFanGame::ECS::Components
{
	ProjectileComponent::ProjectileComponent(std::istream &stream) :
		Component("Projectile")
	{
		stream >> this->_modulePath >> this->damages;

		this->effect.reset(ExternalModuleFactory::build(this->_modulePath));
		Utils::callExternalModule<void>(*this->effect, "onLoad", *this, stream);
	}

	ProjectileComponent::ProjectileComponent(const std::string &modulePath, unsigned damages, const std::weak_ptr<Entity> &entity, const std::vector<std::string> &&targets) :
		Component("Projectile"),
		_modulePath(modulePath),
		damages(damages),
		owner(entity),
		targets(targets),
		effect(ExternalModuleFactory::build(this->_modulePath))
	{
		Utils::callExternalModule<void>(*this->effect, "onCreate", *this);
	}

	ProjectileComponent::~ProjectileComponent()
	{
		Utils::callExternalModule<void>(*this->effect, "onDelete", *this);
	}

	void ProjectileComponent::serialize(std::ostream &stream) const
	{
		Utils::callExternalModule<void>(*this->effect, "onSave", *this, stream);
		stream << this->_modulePath << " " << damages;
	}
}