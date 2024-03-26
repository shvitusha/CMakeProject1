#include "argument.hpp"
#include <iostream>
#include "ArgsParser.hpp"

namespace args_parse{
	ArgsParser::ArgsParser(int argc, const char** argv) {
		_argc = argc;
		_argv = argv;
	}

	void ArgsParser::Add(const Argument& arg) {
		_args.push_back(arg);
	}

	bool ArgsParser::Parse() {
		for (int i = 1; i < _argc; i++) {
			bool isFound = false;
			for (const auto& arg : _args) {
				if (arg.Matches(_argv[i])) {
					isFound = true;
					break;
				}
			}
			if (!isFound) {
				std::cerr << "Команда не найдена: " << _argv[i] << std::endl;
				return false;
			}
		}
		return true;
	}

	void ArgsParser::ShowHelp() {
		std::cout << "Поддерживаемые команды:" << std::endl;
		for (const auto& arg : _args) {
			if (!arg.GetShortName().compare("\O"))
				std::cout << " -" << arg.GetShortName() << " ";
			std::cout << " --" << arg.GetLongName() << "\t" << arg.GetDescription() << std::endl;
		}
	}
}