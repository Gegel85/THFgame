//
// Created by Gegel85 on 26/09/2019.
//

#include "Map.hpp"
#include "Game.hpp"
#include "Exceptions.hpp"

namespace TouhouFanGame
{
	void Map::serialize(std::ostream &stream)
	{}

	void Map::unserialize(std::istream &stream)
	{}

	void Map::update()
	{}

	void Map::clear()
	{
		this->_core.clear();
		this->_objects.clear();
	}

	void Map::loadFromFile(const std::string &path)
	{
		std::ifstream stream{path};

		logger.debug("Loading map " + path);
		if (stream.fail())
			throw CorruptedMapException("Cannot open file " + path);

		this->unserialize(stream);
	}
}