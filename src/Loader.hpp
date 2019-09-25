//
// Created by Gegel85 on 24/09/2019.
//

#ifndef THFGAME_LOADER_HPP
#define THFGAME_LOADER_HPP


#include "nlohmann/json.hpp"
using nlohmann::json;

#include "Game.hpp"

namespace Game
{
	class Loader {
	public:
		static bool loadFile(sf::SoundBuffer &buffer, const std::string &path);
		static bool loadFile(sf::Music &music, const std::string &path);
		static bool loadFile(sf::Texture &texture, const std::string &path);
		static void loadAssets();

		template<typename dataType>
		static void loadAssetsFromJson(const std::string &dataName, json &paths, std::map<std::string, dataType> &data)
		{
			if (paths.is_null())
				logger.warn("No " + dataName + " is marked for loading");

			logger.debug("Loading " + std::to_string(paths.size()) + " " + dataName);
			for (auto &value : paths.items())
				try {
					logger.debug("Loading file " + static_cast<std::string>(value.value()) + " at key " + value.key());
					try {
						data.at(value.key());
						logger.warn("A sound is already loaded with key " + value.key());
					} catch (std::out_of_range &) {}

					if (!loadFile(data[value.key()], "assets/" + static_cast<std::string>(value.value())))
						logger.error("Cannot load file " + static_cast<std::string>(value.value()));

				} catch (std::exception &e) {
					logger.error(e.what());
				}
		}
	};
}


#endif //THFGAME_LOADER_HPP
