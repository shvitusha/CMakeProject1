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

	void ArgsParser::ShowHelp() {
		std::cout << "Поддерживаемые команды:" << std::endl;
		for (const auto& arg : _args) {
			if (arg.GetShortName() == '\0')
				std::cout << " -" << arg.GetShortName() << " ";
			std::cout << " --" << arg.GetLongName() << "\t" << arg.GetDescription() << std::endl;
		}
	}


	std::string ArgsParser::IsOperator(std::string operatString)
	{
		size_t position = operatString.find("--");

		if (position != std::string::npos && position == 0) {
			return o_type = "long";
		}

		position = operatString.find("-");

		if (position != std::string::npos && position == 0) {
			return o_type = "short";
		}

		return o_type = "no";
	}

	Argument ArgsParser::FindLongNameArg(std::string item, std::string& value) const
	{
		for (auto arg : _args) {
			auto longArg = arg.GetLongName();
			size_t equalSignPosition = item.find(longArg);

			if (equalSignPosition != std::string::npos && equalSignPosition == 0 && longArg.length() < item.length()) {
				if (value != "")
				{
					throw std::invalid_argument("Передача нескольких значений");
				}

				value = item.substr(longArg.length());

				return arg;
			}

			if (longArg == item)
			{
				return arg;
			}
		}

		throw std::invalid_argument("Не найден");
	}

	Argument ArgsParser::FindShortNameArg(std::string item, std::string& value) const
	{
		for (auto arg : _args) {
			size_t position = item.find(arg.GetShortName());
			if (position == 0) {
				if (position + 1 < item.length()) {
					if (value != "")
					{
						throw std::invalid_argument("Передача нескольких значений");
					}

					value = item.substr(position + 1);
				}

				return arg;
			}
		}

		throw std::invalid_argument("Передача нескольких значений");
	}

	bool ArgsParser::Parse()
	{
		std::vector<Argument, std::string> vector;

		for (int i = 1; i < _argc; ++i)
		{
			auto item = _argv[i];
			std::string strItem(item);
			std::string operatorType = IsOperator(strItem);

			std::string value = "";
			size_t equalSignPosition = strItem.find('=');

			if (equalSignPosition != std::string::npos) {
				value = strItem.substr(equalSignPosition + 1);
				item = strItem.substr(0, equalSignPosition).c_str();
			}

			if (operatorType == "long")
			{
				item = strItem.erase(0, 2).c_str();
				Argument arg = FindLongNameArg(item, value);

			}

			if (operatorType == "short")
			{
				strItem.erase(0, 1);
				Argument arg = FindShortNameArg(item, value);

			}

			auto nextElement = _argv[i + 1];
			if (value != ""){
				throw std::invalid_argument("Передача нескольких значений");
			}
			value = nextElement;
			i++;

			if (value == ""){
				throw std::invalid_argument("Оператор должен иметь значение");
			}
		}
		return true;
		//try {
		//	for (int i = 1; i < _argc; ++i) {
		//		std::string item(_argv[i]);
		//		// Определяем тип оператора (длинный или короткий)
		//		std::string operatorType = IsOperator(item);
		//		// Получаем оператор и его значение (если есть)
		//		std::string value;
		//		if (operatorType == "long") {
		//			auto foundOperator = FindLongNameArg(item, value);
		//		}
		//		else if (operatorType == "short") {
		//			auto foundOperator = FindShortNameArg(item, value);
		//		}
		//		else {
		//			throw std::invalid_argument("Invalid operator");
		//		}
		//		// Обрабатываем значение (если оно есть)
		//		// ...
		//		// Далее можно выполнить дополнительные действия с найденным оператором и его значением
		//	}
		//	return true;
		//}
		//catch (const std::exception& e) {
		//	std::cerr << "Error during parsing: " << e.what() << std::endl;
		//	return false;
		//}
	}
}