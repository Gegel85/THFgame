//
// Created by Gegel85 on 15/01/2019.
//

#ifndef THFGAME_LOGGER_HPP
#define THFGAME_LOGGER_HPP


#include <fstream>
#include <string>

namespace TouhouFanGame
{
	class Logger {
	public:
		enum LogLevel {
			DEBUG,
			INFO,
			WARNING,
			ERROR,
			CRITICAL,
			NONE,
		};

		explicit Logger(const std::string &filepath = "./latest.log", LogLevel level = INFO) noexcept;
		~Logger() noexcept;

		void msg(const std::string &content, const std::string &prepend = "") noexcept;
		void debug(const std::string &content) noexcept;
		void info(const std::string &content) noexcept;
		void warn(const std::string &content) noexcept;
		void error(const std::string &content) noexcept;
		void fatal(const std::string &content) noexcept;

	private:
		std::ofstream _file;
		LogLevel _level;
	};
}


#endif //THFGAME_LOGGER_HPP
