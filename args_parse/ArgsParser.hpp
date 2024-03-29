#pragma once
#include "argument.hpp"
#include <vector>

namespace args_parse {
	class ArgsParser {
	public:
		/// @brief  онструктор класса.
		///  онструктор принимает количество аргументов и их значени€
		ArgsParser(int argc, const char** argv);

		/// @brief ћетод добавлени€ аргумента командной строки в вектор
		void Add(const Argument& arg);

		/// @brief ћетод парсинга аргументов командной строки.
		/// ќн проходит по каждому аргументу командной строки и провер€ет, был ли найден аргумент в векторе
		bool Parse();

		/// @brief ƒеструктор
		~ArgsParser();

		/// @brief ћетод дл€ вывода справки об использовании программы.
		/// ¬ыводит описание всех добавленных аргументов командной строки
		void ShowHelp();

		/// @brief ћетод дл€ поиска длинного имени, если оно есть
		Argument FindLongNameArg(std::string item, std::string& value) const;

		/// @brief ћетод поиска короткого имени, если оно есть
		Argument FindShortNameArg(std::string item, std::string& value) const;

		/// @brief ћетод, который провер€ет €вл€етс€ ли строка оператором.
		/// ¬озвращает какой оператор был использован
		OperatorType IsOperator(std::string operatString);

	private:
		/// —колько всего аргументов.
		int _argc;
		/// «начени€ аргументов. ƒолжно быть ровно @a argc.
		const char** _argv;
		/// ћассив дл€ хранени€ объектов аргументов командной строки
		std::vector<Argument> _args;
	};

	/// @brief ѕеречисление типов оператора (длинный, короткий, неопределенный)
	enum class OperatorType {
		Long,
		Short,
		Nope
	};
}