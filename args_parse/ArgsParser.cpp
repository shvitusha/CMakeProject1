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
				std::cerr << "������� �� �������: " << _argv[i] << std::endl;
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

	std::unique_ptr<Argument> ArgsParser::FindLongNameArg(std::string item, std::string& value) const
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
				return std::make_unique<Argument>(arg);
			}

			/*if (longArg == item)
			{
				return arg;
			}*/
			if (item.compare(0, longArg.length(), longArg) == 0)
				return std::make_unique<Argument>(arg);
		}

		throw std::invalid_argument("Not found");
	}

	std::unique_ptr<Argument> ArgsParser::FindShortNameArg(std::string item, std::string& value) const
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
				return std::make_unique<Argument>(arg);
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

			/*if (o_type == OperatorType::Long) {
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
			}*/

			if (argStr.substr(0, 2) == "--")
			{
				ParseLongArgument(argStr, argName, argValue);
			}
			else if (argStr[0] == '-')
			{
				ParseShortArgument(argStr, argName, argValue);
			}
			else {
				std::string errorMessage = "Invalid argument format: " + argStr;
				throw std::invalid_argument(errorMessage);
			}

			ProcessArgument(argStr, argName, argValue, i);
			std::cout << "\nString: " << argStr << " ; Name: " << argName << " ;" << std::endl;
			if (!argValue.empty())
				std::cout << "Value: " << argValue << std::endl;
		}
		return true;
	}

	void ArgsParser::ParseLongArgument(const std::string& argStr, std::string& argName, std::string& argValue)
	{
		argName = argStr.substr(2);
		size_t equalPosition = argName.find('=');
		if (equalPosition != std::string::npos)
		{
			argValue = argName.substr(equalPosition + 1);
			argName = argName.substr(0, equalPosition);
		}
	}

	void ArgsParser::ParseShortArgument(const std::string& argStr, std::string& argName, std::string& argValue)
	{
		argName = argStr.substr(1, 1);
		if (argStr.length() > 2 && (argStr[2] == '=' || argStr[2] == ' '))
		{
			argValue = argStr.substr(3);
		}
		else if (argStr.length() > 2)
		{
			argValue = argStr.substr(2);
		}
	}

	void ArgsParser::ProcessArgument(const std::string& argStr, const std::string& argName, std::string& argValue, int& i) const
	{
		try {
			std::unique_ptr<Argument> arg = FindArgument(argName, argValue);

			if (arg != nullptr) {
				if (arg->HasValue()) {
					if (argValue.empty()) {
						if (i + 1 < _argc) {
							argValue = _argv[i + 1];
							++i;
						}
						else {
							std::string errorMessage = "Missing value for argument: " + argName;
							throw std::invalid_argument(errorMessage);
						}
					}
					if (!arg->ValidValue(argValue)) {
						std::cerr << "Invalid value for argument: " << argStr << std::endl;
					}
				}
			}
			else {
				std::cerr << "Unknown argument: " << argStr << std::endl;
			}
		}
		catch (const std::invalid_argument& e) {
			std::string errorMessage = e.what();
			throw std::invalid_argument(errorMessage);
		}
	}

	std::unique_ptr<Argument> ArgsParser::FindArgument(const std::string& argName, std::string& argValue) const
	{
		std::unique_ptr<Argument> arg = nullptr;
		if (o_type == OperatorType::Long) {
			arg = FindLongNameArg(argName, argValue);
			return arg;
		}
		else if (o_type == OperatorType::Short) {
			arg = FindShortNameArg(argName, argValue);
			return arg;
		}

		return nullptr;
	}
}