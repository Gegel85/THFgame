//
// Created by Gegel85 on 05/01/2020.
//

#include <iostream>
#include "DialogComponent.hpp"

namespace TouhouFanGame::ECS::Components
{
	DialogComponent::DialogComponent(const std::string &dialogPath) :
		Component("Dialog"),
		_dialogPath(dialogPath)
	{
		this->manager.loadFromFile(dialogPath);
	}

	DialogComponent::DialogComponent() :
		Component("Dialog")
	{
	}

	DialogComponent::DialogComponent(std::istream &stream) :
		Component("Dialog")
	{
		unsigned selected;

		std::getline(stream, this->_dialogPath, '\0');
		stream >> selected;
		while (!this->_dialogPath.empty() && std::isspace(this->_dialogPath[0]))
			this->_dialogPath = this->_dialogPath.substr(1);
		try {
			this->manager.loadFromFile(this->_dialogPath);
			this->manager.select(selected);
		} catch (std::exception &) {}
	}

	std::string DialogComponent::getDialogPath() const
	{
		return this->_dialogPath;
	}

	void DialogComponent::setDialogPath(const std::string &path)
	{
		this->_dialogPath = path;
		this->manager.loadFromFile(path);
	}

	void DialogComponent::serialize(std::ostream &stream) const
	{
		stream << this->_dialogPath << '\0' << this->manager.getSelected();
	}
}