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

	void ArgsParser::Add(Argument* arg) {
		// ����� ��� ��������� ����� ��� ������������
		for (const auto& existingArg : _args) {
			if (existingArg->GetLongName() == arg->GetLongName()) {
				throw std::invalid_argument("Argument with the same name already exists");
			}
		}
		_args.push_back(arg);
	}

	void ArgsParser::ShowHelp() const
	{
		std::cout << "\nSupported commands:" << std::endl;
		for (const auto& arg : _args)
		{
			if (!(arg->GetShortName() == '\0'))
				std::cout << " -" << arg->GetShortName() << " ";
			std::cout << " --" << arg->GetLongName() << "\t" << arg->GetDescription() << std::endl;
		}
	}

	void ArgsParser::ShowHelpVerbose() const
	{
		std::cout << "\nArguments, which must contain a value:" << std::endl;
		for (const auto& arg : _args)
		{
			if (arg->HasValue()) {
				if (!(arg->GetShortName() == '\0'))
					std::cout << " -" << arg->GetShortName() << " ";
				std::cout << " --" << arg->GetLongName() << "\t" << arg->GetDescription() << std::endl;
			}
		}
		std::cout << "To assign a value to an argument, enter a[-short] or [--long] name" << std::endl;
		std::cout << "and a parameter with an [parameter]/[=parametr]/[ parametr].\n" << std::endl;
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

	Argument* ArgsParser::FindLongNameArg(std::string item) const
	{
		Argument* foundArg = nullptr;
		int matchingCount = 0;

		for (const auto& arg : _args)
		{
			auto longArg = arg->GetLongName();
			//������ ����� ���� ���������
			if (item.length() > 1 && item.length() <= longArg.length()
				&& longArg.compare(StartingPosition, item.length(), item) == 0) {
				matchingCount++;
				foundArg = arg;
			}
		}
		if (matchingCount == 0) {
			throw std::invalid_argument("Not found");
		}
		else if (matchingCount > 1) {
			throw std::invalid_argument("Prefix is not unique");
		}

		return foundArg;
	}

	Argument* ArgsParser::FindShortNameArg(std::string item) const
	{
		for (const auto& arg : _args)
		{
			size_t position = item.find(arg->GetShortName());
			if (position == StartingPosition)
			{
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
			BaseParametrs parametrs{ argStr, argName, argValue };
			//��������� �������� ���������
			if (argStr.substr(StartingPosition, LenghtTwoChar) == "--")
				ParseLongArgument(parametrs);
			//��������� ��������� ���������
			else if (argStr[0] == '-')
				ParseShortArgument(parametrs);
			//������ ����� ���� ��� ����������
			else {
				std::string errorMessage = "Invalid argument format: " + parametrs.argStr;
				throw std::invalid_argument(errorMessage);
			}
			ProcessArgument(parametrs, i);
		}
		return true;
	}

	void ArgsParser::ParseLongArgument(BaseParametrs parametrs)
	{
		parametrs.argName = parametrs.argStr.substr(LenghtTwoChar);
		size_t equalPosition = parametrs.argName.find('=');
		size_t spacePosition = parametrs.argName.find(' ');
		//����� �� ��������� =
		if (equalPosition != std::string::npos)
		{
			parametrs.argValue = parametrs.argName.substr(equalPosition + LenghtOneChar);
			parametrs.argName = parametrs.argName.substr(StartingPosition, equalPosition);
		}
		//����� �� ��������� ������
		else if (spacePosition != std::string::npos)
		{
			parametrs.argValue = parametrs.argName.substr(spacePosition + LenghtOneChar);
			parametrs.argName = parametrs.argName.substr(StartingPosition, spacePosition);
		}
		// ������, ����� �� �������� �� ������ �� ��������� ������������
		else if (parametrs.argStr.length() > 3)
			parametrs.argValue = parametrs.argStr.substr(parametrs.argName.length() + LenghtTwoChar);
	}

	void ArgsParser::ParseShortArgument(BaseParametrs parametrs) const
	{
		parametrs.argName = parametrs.argStr.substr(LenghtOneChar, LenghtOneChar);
		if (parametrs.argStr.length() > LenghtTwoChar && (parametrs.argStr[2] == '=' || parametrs.argStr[2] == ' '))
			parametrs.argValue = parametrs.argStr.substr(3);
		else if (parametrs.argStr.length() > LenghtTwoChar)
			parametrs.argValue = parametrs.argStr.substr(LenghtTwoChar);
	}

	void ArgsParser::ProcessArgument(BaseParametrs parametrs, int& i) const
	{
		try {
			Argument* arg = FindArgument(parametrs.argName);
			//������ ����� ���� null
			if (arg != nullptr) {
				arg->SetIsDefined(true);
				//�������� ����� �� ��������� ��������
				if (arg->HasValue()) {
					const Validator* validator = arg->GetValidator();
					ValidationValue(validator, parametrs, arg, i);
				}
			}
			else {
				std::cerr << "Unknown argument: " << parametrs.argStr << std::endl;
			}
		}
		catch (const std::invalid_argument& e) {
			std::string errorMessage = e.what();
			throw std::invalid_argument(errorMessage);
		}
	}

	void ArgsParser::ValidationValue(const Validator* validator, BaseParametrs& parametrs, Argument* arg, int& i) const {
		//��������� ����� ���� null
		if (validator != nullptr) {
			std::cout << "\nString: " << parametrs.argStr << " ; Name: " << parametrs.argName << " ;" << std::endl;
			//� ������, ���� �������� ��������� ��������, �������� ����� ���� ������
			if (parametrs.argValue.empty()) {
				if (i + 1 < _argc) {
					parametrs.argValue = _argv[i + 1];
					++i;
				}
				else {
					std::string errorMessage = "Missing value for argument: " + parametrs.argName;
					throw std::invalid_argument(errorMessage);
				}
			}
			else if (!parametrs.argValue.empty() && validator->ValidValue(parametrs.argValue)) {
				arg->SetValue(parametrs.argValue);
				std::cout << "Value: " << parametrs.argValue << std::endl;
			}
			else if (!parametrs.argValue.empty() && !validator->ValidValue(parametrs.argValue)) {
				std::cerr << "Invalid value for argument: " << parametrs.argStr << std::endl;
			}
		}
	}

	Argument* ArgsParser::FindArgument(const std::string& argName) const
	{
		Argument* arg = nullptr;
		if (o_type == OperatorType::Long) {
			arg = FindLongNameArg(argName);
			return arg;
		}
		else if (o_type == OperatorType::Short) {
			arg = FindShortNameArg(argName);
			return arg;
		}
		return arg;
	}
}