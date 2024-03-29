#include "ArgsParser.hpp"
#include <iostream>
#include <string>

namespace args_parse {
	OperatorType o_type;
	const int StartingPosition = 0;
	const int LenghtOneChar = 1;
	const int LenghtTwoChar = 2;

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
			if (!arg.GetShortName() == '\0')
				std::cout << " -" << arg.GetShortName() << " ";
			std::cout << " --" << arg.GetLongName() << "\t" << arg.GetDescription() << std::endl;
		}
	}


	OperatorType ArgsParser::IsOperator(std::string operatString)
	{
		size_t position = operatString.find("--");

		if (position != std::string::npos && position == 0)
		{
			return OperatorType::Long;
		}

		position = operatString.find("-");

		if (position != std::string::npos && position == 0)
		{
			return OperatorType::Short;
		}

		return OperatorType::Nope;
	}

	Argument ArgsParser::FindLongNameArg(std::string item, std::string& value) const
	{
		for (const auto &arg : _args)
		{
			auto longArg = arg.GetLongName();
			size_t equalSignPosition = item.find(longArg);

			if (equalSignPosition != std::string::npos && equalSignPosition == StartingPosition && longArg.length() < item.length())
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
		for (const auto &arg : _args)
		{
			size_t position = item.find(arg.GetShortName());
			if (position == StartingPosition)
			{
				if (position + LenghtOneChar < item.length())
				{
					if (value != "")
					{
						throw std::invalid_argument("Transferring multiple values");
					}

					value = item.substr(position + LenghtOneChar);
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

			if (o_type == OperatorType::Long) {
				size_t equalPosition = argStr.find('=');
				size_t spacePosition = argStr.find(' ');

				if (equalPosition != std::string::npos) {
					argName = argStr.substr(LenghtTwoChar, equalPosition - LenghtTwoChar);
					argValue = argStr.substr(equalPosition + LenghtTwoChar);
					std::cout << argValue << std::endl;
				}
				else
				{
					if (spacePosition != std::string::npos) {
						argName = argStr.substr(LenghtTwoChar, spacePosition - LenghtTwoChar);
						argValue = argStr.substr(spacePosition + LenghtTwoChar);
						std::cout << argValue << std::endl;
					}
					else
					{
						argName = argStr.substr(LenghtTwoChar);
						if (argName.length() > 0) {
							argValue = argStr.substr(LenghtTwoChar + argName.length());
						}
					}
				}
			}
			else if (o_type == OperatorType::Short) {
				argName = argStr.substr(LenghtOneChar, 1);
				if (argStr.length() > LenghtTwoChar && (argStr.substr(LenghtTwoChar, 1) == "=" || argStr.substr(LenghtTwoChar, 1) == " ")) {
					argValue = argStr.substr(3);
					std::cout << argValue << std::endl;
				}
				else if (argStr.length() > LenghtTwoChar)
				{
					argValue = argStr.substr(LenghtTwoChar);
					std::cout << argValue << std::endl;
				}
			}
			else
			{
				std::string errorMessage = "Invalid argument format: " + argStr;
				throw std::invalid_argument(errorMessage);
			}

			try
			{
				if (o_type == OperatorType::Long) {
					Argument arg = FindLongNameArg(argName, argValue);
					if (!arg.ValidValue(argValue)) {
						std::cerr << "" << argStr << std::endl;
					}
				}
				else if (o_type == OperatorType::Short) {
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