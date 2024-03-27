#pragma once
#include "argument.hpp"
#include <vector>

namespace args_parse {
	class ArgsParser {
	public:
		/// @brief Конструктор класса.
		/// Конструктор принимает количество аргументов и их значения
		ArgsParser(int argc, const char** argv);

		/// @brief Метод добавления аргумента командной строки в вектор
		void Add(const Argument& arg);

		/// @brief Метод парсинга аргументов командной строки.
		/// Он проходит по каждому аргументу командной строки и проверяет, был ли найден аргумент в векторе
		bool Parse();

		/// @brief Деструктор
		~ArgsParser();

		/// @brief Метод для вывода справки об использовании программы.
		/// Выводит описание всех добавленных аргументов командной строки
		void ShowHelp();

		Argument FindLongNameArg(std::string item, std::string& value) const;

		Argument FindShortNameArg(std::string item, std::string& value) const;

		std::string IsOperator(std::string operatString);

	private:
		/// Сколько всего аргументов.
		int _argc;
		/// Значения аргументов. Должно быть ровно @a argc.
		const char** _argv;
		/// Массив для хранения объектов аргументов командной строки
		std::vector<Argument> _args;
	};
}