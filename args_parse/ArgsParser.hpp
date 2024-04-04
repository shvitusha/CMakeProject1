#pragma once
#include "argument.hpp"
#include <vector>

namespace args_parse {
	/// @brief ѕеречисление типов оператора (длинный, короткий, неопределенный)
	enum class OperatorType {
		Long,
		Short,
		Nope
	};

	class ArgsParser {
	public:
		/// @brief  онструктор класса.
		///  онструктор принимает количество аргументов и их значени€
		ArgsParser(int argc, const char** argv);

		/// @brief ћетод добавлени€ аргумента командной строки в вектор
		void Add(Argument* arg);

		/// @brief ћетод парсинга аргументов командной строки.
		/// ќн проходит по каждому аргументу командной строки и провер€ет, был ли найден аргумент в векторе
		bool Parse();

		/// @brief ћетод дл€ разбора длинных аргументов командной строки.
		/// »звлекает им€ и значение аргумента дл€ дальнейшей обработки.
		void ParseLongArgument(const std::string& argStr, std::string& argName, std::string& argValue);

		/// @brief ћетод дл€ разбора коротких аргументов командной строки.
		/// »звлекает им€ и значение аргумента дл€ дальнейшей обработки.
		void ParseShortArgument(const std::string& argStr, std::string& argName, std::string& argValue);

		/// @brief ћетод дл€ обработки одного аргумента командной строки.
		/// “акже провер€ет его наличие, наличие у него значени€, если да, то его проверку.
		void ProcessArgument(const std::string& argStr, const std::string& argName, std::string& argValue, int& i) const;

		/// @brief ћетод поиска аргумента.
		/// ¬ зависимости от оператора вызывает методы поиска короткого или длинного имени.
		Argument* FindArgument(const std::string& argName) const;

		/// @brief ƒеструктор
		~ArgsParser();

		/// @brief ћетод дл€ вывода справки об использовании программы.
		/// ¬ыводит описание всех добавленных аргументов командной строки
		void ShowHelp() const;

		/// @brief ћетод дл€ поиска длинного имени, если оно есть
		Argument* FindLongNameArg(std::string item) const;

		/// @brief ћетод поиска короткого имени, если оно есть
		Argument* FindShortNameArg(std::string item) const;

		/// @brief ћетод, который провер€ет €вл€етс€ ли строка оператором.
		/// ¬озвращает какой оператор был использован
		OperatorType IsOperator(std::string operatString);

	private:
		/// —колько всего аргументов.
		int _argc;
		/// «начени€ аргументов. ƒолжно быть ровно @a argc.
		const char** _argv;
		/// ћассив дл€ хранени€ объектов аргументов командной строки
		std::vector<Argument*> _args;
	};
}