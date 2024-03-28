#include "ArgsParser.hpp"
#include <iostream>
#include <string>

namespace args_parse {
	std::string o_type;

	ArgsParser::ArgsParser(int argc, const char** argv) {
		_argc = argc;
		_argv = argv;
	}

	ArgsParser::~ArgsParser() {
		_args.clear();
	}

	void ArgsParser::Add(const Argument& arg) {
		_args.push_back(arg);
	}

	/*bool ArgsParser::Parse() {
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
	}*/

	void ArgsParser::ShowHelp()
	{
		std::cout << "Supported commands:" << std::endl;
		for (const auto& arg : _args)
		{
			if (arg.GetShortName() == '\0')
				std::cout << " -" << arg.GetShortName() << " ";
			std::cout << " --" << arg.GetLongName() << "\t" << arg.GetDescription() << std::endl;
		}
	}


	std::string ArgsParser::IsOperator(std::string operatString)
	{
		size_t position = operatString.find("--");

		if (position != std::string::npos && position == 0)
		{
			return o_type = "long";
		}

		position = operatString.find("-");

		if (position != std::string::npos && position == 0)
		{
			return o_type = "short";
		}

		return o_type = "no";
	}

	Argument ArgsParser::FindLongNameArg(std::string item, std::string& value) const
	{
		for (auto arg : _args)
		{
			auto longArg = arg.GetLongName();
			size_t equalSignPosition = item.find(longArg);

			if (equalSignPosition != std::string::npos && equalSignPosition == 0 && longArg.length() < item.length())
			{
				if (value != "")
				{
					throw std::invalid_argument("Transferring multiple values");
				}

				value = item.substr(longArg.length());

				return arg;
			}

			if (longArg == item)
			{
				return arg;
			}
		}

		throw std::invalid_argument("Not found");
	}

	Argument ArgsParser::FindShortNameArg(std::string item, std::string& value) const
	{
		for (auto arg : _args)
		{
			size_t position = item.find(arg.GetShortName());
			if (position == 0)
			{
				if (position + 1 < item.length())
				{
					if (value != "")
					{
						throw std::invalid_argument("Transferring multiple values");
					}

					value = item.substr(position + 1);
				}

				return arg;
			}
		}

		throw std::invalid_argument("Transferring multiple values");
	}

	bool ArgsParser::Parse()
	{
		for (int i = 1; i < _argc; ++i) {
			std::string argStr(_argv[i]);
			o_type = IsOperator(argStr);
			std::string argName;
			std::string argValue;

			if (o_type == "long") {
				argName = argStr.substr(2);
			}
			else if (o_type == "short") {
				argName = argStr.substr(2);
				if (argStr.length() > 2 && argStr.substr(2, 1) == "=") {
					argValue = argStr.substr(3);
				}
				else if(argStr.length() > 2)
				{
					argValue = argStr.substr(2);
				}
			}
			else
			{
				std::string errorMessage = "Invalid argument format: " + argStr;
				throw std::invalid_argument(errorMessage);
			}

			try
			{
				if (o_type == "long") {
					Argument arg = FindLongNameArg(argName, argValue);
					if (!arg.ValidValue(argValue)) {
						std::cerr << "" << argStr << std::endl;
					}
				}
				else if (o_type == "short") {
					Argument arg = FindShortNameArg(argName, argValue);
					if (!arg.ValidValue(argValue)) {
						std::cerr << "" << argStr << std::endl;
					}
				}
			}
			catch (const std::invalid_argument& e)
			{
				std::string errorMessage = e.what();
				throw std::invalid_argument(errorMessage);
			}
		}
		return true;
	}
}