#include "ArgsParser.hpp"
#include <iostream>
#include <string>
#include <algorithm>

namespace args_parse {
	OperatorType o_type;
	const int StartingPosition = 0;
	const int LenghtOneChar = 1;
	const int LenghtTwoChar = 2;

	ArgsParser::ArgsParser(int argc, const char** argv) : _argc(argc), _argv(argv) {}

	void ArgsParser::Add(ArgumentBase* arg) {
		// Такое имя аргумента может уже существовать
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
	//& string_view
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

	ArgumentBase* ArgsParser::FindLongNameArg(std::string item) const
	{
		ArgumentBase* foundArg = nullptr;
		int matchingCount = 0;

		for (const auto& arg : _args)
		{
			auto longArg = arg->GetLongName();
			//строка может быть префиксом
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

	ArgumentBase* ArgsParser::FindShortNameArg(std::string item) const
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
			BaseParametrs* p_param = &parametrs;
			//обработка длинного аргумента
			if (argStr.substr(StartingPosition, LenghtTwoChar) == "--")
				ParseLongArgument(*p_param);
			//обработка короткого аргумента
			else if (argStr[0] == '-')
				ParseShortArgument(*p_param);
			//строка может быть без аргументов
			else {
				std::string errorMessage = "Invalid argument format: " + p_param->argStr;
				throw std::invalid_argument(errorMessage);
			}
			ProcessArgument(*p_param, i);
		}
		return true;
	}

	void ArgsParser::ParseLongArgument(BaseParametrs& p_param)
	{
		p_param.argName = p_param.argStr.substr(LenghtTwoChar);
		size_t equalPosition = p_param.argName.find('=');
		size_t spacePosition = p_param.argName.find(' ');
		//может не содержать =
		if (equalPosition != std::string::npos)
		{
			p_param.argValue = p_param.argName.substr(equalPosition + LenghtOneChar);
			p_param.argName = p_param.argName.substr(StartingPosition, equalPosition);
		}
		//может не содержать пробел
		else if (spacePosition != std::string::npos)
		{
			p_param.argValue = p_param.argName.substr(spacePosition + LenghtOneChar);
			p_param.argName = p_param.argName.substr(StartingPosition, spacePosition);
		}
		// случай, когда не содержит ни одного из указанных разделителей
		else if (p_param.argStr.length() > 3)
			p_param.argValue = p_param.argStr.substr(p_param.argName.length() + LenghtTwoChar);
	}

	void ArgsParser::ParseShortArgument(BaseParametrs& p_param) const
	{
		p_param.argName = p_param.argStr.substr(LenghtOneChar, LenghtOneChar);
		if (p_param.argStr.length() > LenghtTwoChar && (p_param.argStr[2] == '=' || p_param.argStr[2] == ' '))
			p_param.argValue = p_param.argStr.substr(3);
		else if (p_param.argStr.length() > LenghtTwoChar)
			p_param.argValue = p_param.argStr.substr(LenghtTwoChar);
	}

	void ArgsParser::ProcessArgument(BaseParametrs& p_param, int& i) const
	{
		ArgumentBase* arg = FindArgument(p_param.argName);
		//ссылка может быть null
		if (arg != nullptr) {
			arg->SetIsDefined(true);
			//аргумент может не содержать параметр
			if (arg->HasValue()) {
				if (p_param.argValue.empty()) {
					std::string errorMessage = "Missing value for argument: " + p_param.argName;
					std::cerr << errorMessage << std::endl;
					return;
				}
				const SharedValidator* validator = arg->GetValidator();
				ValidationValue(validator, p_param, arg, i);
			}
		}
		else {
			std::cerr << "Unknown argument: " << p_param.argStr << std::endl;
		}
	}

	void ArgsParser::ValidationValue(const SharedValidator* validator, BaseParametrs& parametrs, ArgumentBase* arg, int& i) const {
		//валидатор может быть null
		if (validator != nullptr) {
			std::cout << "\nString: " << parametrs.argStr << " ; Name: " << parametrs.argName << " ;" << std::endl;
			//в случае, если аргумент принимает значение, значение может быть пустым
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

	ArgumentBase* ArgsParser::FindArgument(const std::string& argName) const
	{
		ArgumentBase* arg = nullptr;
		if (o_type == OperatorType::Long) {
			arg = FindLongNameArg(argName);
			//return arg;
		}
		else if (o_type == OperatorType::Short) {
			arg = FindShortNameArg(argName);
			//return arg;
		}
		return arg;
	}
}