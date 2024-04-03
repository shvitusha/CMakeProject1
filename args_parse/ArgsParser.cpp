#include "ArgsParser.hpp"
#include "Validator.hpp"
#include <iostream>
#include <string>
#include <algorithm>

namespace args_parse {
	OperatorType o_type;
	const int StartingPosition = 0;
	const int LenghtOneChar = 1;
	const int LenghtTwoChar = 2;

	ArgsParser::ArgsParser(int argc, const char** argv) : _argc(argc), _argv(argv) {}

	ArgsParser::~ArgsParser() {
		_args.clear();
	}

	void ArgsParser::Add(std::unique_ptr<Argument> arg) {
		_args.push_back(std::move(arg));
	}

	void ArgsParser::ShowHelp()
	{
		std::cout << "Supported commands:" << std::endl;
		for (const auto& arg : _args)
		{
			if (!(arg->GetShortName() == '\0'))
				std::cout << " -" << arg->GetShortName() << " ";
			std::cout << " --" << arg->GetLongName() << "\t" << arg->GetDescription() << std::endl;
		}
	}

	OperatorType ArgsParser::IsOperator(std::string operatString)
	{
		size_t position = operatString.find("--");
		if (position != std::string::npos && position == StartingPosition)
		{
			return OperatorType::Long;
		}

		position = operatString.find("-");
		if (position != std::string::npos && position == StartingPosition)
		{
			return OperatorType::Short;
		}
		return OperatorType::Nope;
	}

	std::unique_ptr<Argument> ArgsParser::FindLongNameArg(std::string item) const
	{
		for (const auto& arg : _args)
		{
			auto longArg = arg->GetLongName();
			//строка может быть префиксом
			if (item.length() <= longArg.length() && longArg.compare(StartingPosition, item.length(), item) == 0)
				return std::make_unique<Argument>(*arg);
		}
		throw std::invalid_argument("Not found");
	}

	std::unique_ptr<Argument> ArgsParser::FindShortNameArg(std::string item) const
	{
		for (const auto& arg : _args)
		{
			size_t position = item.find(arg->GetShortName());
			if (position == StartingPosition)
			{
				return std::make_unique<Argument>(*arg);
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

			if (argStr.substr(StartingPosition, LenghtTwoChar) == "--")
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
		argName = argStr.substr(LenghtTwoChar);
		size_t equalPosition = argName.find('=');
		size_t spacePosition = argName.find(' ');
		if (equalPosition != std::string::npos)
		{
			argValue = argName.substr(equalPosition + LenghtOneChar);
			argName = argName.substr(StartingPosition, equalPosition);
		}
		else if (spacePosition != std::string::npos)
		{
			argValue = argName.substr(spacePosition + LenghtOneChar);
			argName = argName.substr(StartingPosition, spacePosition);
		}
		else if (argStr.length() > 3)
		{
			argValue = argStr.substr(argName.length() + LenghtTwoChar);
		}
	}

	void ArgsParser::ParseShortArgument(const std::string& argStr, std::string& argName, std::string& argValue)
	{
		argName = argStr.substr(LenghtOneChar, LenghtOneChar);
		if (argStr.length() > LenghtTwoChar && (argStr[2] == '=' || argStr[2] == ' '))
		{
			argValue = argStr.substr(3);
		}
		else if (argStr.length() > LenghtTwoChar)
		{
			argValue = argStr.substr(LenghtTwoChar);
		}
	}

	void ArgsParser::ProcessArgument(const std::string& argStr, const std::string& argName, std::string& argValue, int& i) const
	{
		try {
			std::unique_ptr<Argument> arg = std::move(FindArgument(argName));

			if (arg != nullptr) {
				if (arg->HasValue()) {
					const Validator* validator = arg->GetValidator();
					if (validator != nullptr) {
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
						if (!argValue.empty() && !validator->ValidValue(argValue)) {
							std::cerr << "Invalid value for argument: " << argStr << std::endl;
						}
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

	std::unique_ptr<Argument> ArgsParser::FindArgument(const std::string& argName) const
	{
		std::unique_ptr<Argument> arg = nullptr;
		if (o_type == OperatorType::Long) {
			arg = std::move(FindLongNameArg(argName));
			return arg;
		}
		else if (o_type == OperatorType::Short) {
			arg = std::move(FindShortNameArg(argName));
			return arg;
		}
		return nullptr;
	}
}