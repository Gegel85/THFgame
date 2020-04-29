//
// Created by Gegel85 on 28/04/2020.
//

#include "ProjectileComponent.hpp"
#include "../../Utils/Utils.hpp"
#include "../../ExternalCode/ExternalModuleFactory.hpp"

namespace TouhouFanGame::ECS::Components
{
	ProjectileComponent::ProjectileComponent(Game &game, std::istream &stream) :
		Component("Projectile")
	{
		stream >> this->_modulePath >> this->damages;

		this->effect.reset(ExternalModuleFactory::build(this->_modulePath));
		Utils::callExternalModule<void>(*this->effect, "onLoad", *this, game, stream);
	}

	ProjectileComponent::ProjectileComponent(Game &game, std::string modulePath, unsigned damages, std::weak_ptr<Entity> entity, const std::vector<std::string> &&targets) :
		Component("Projectile"),
		_modulePath(std::move(modulePath)),
		damages(damages),
		owner(std::move(entity)),
		targets(targets),
		effect(ExternalModuleFactory::build(this->_modulePath))
	{
		Utils::callExternalModule<void>(*this->effect, "onCreate", *this, game);
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