#pragma once
#include "argument.hpp"
#include <vector>

namespace args_parse {
	/// @brief Перечисление типов оператора (длинный, короткий, неопределенный)
	enum class OperatorType {
		Long,
		Short,
		Nope
	};
	/// @brief Структура для определения параметров
	struct BaseParametrs {
		const std::string& argStr;
		std::string& argName;
		std::string& argValue;
	};

	class ArgsParser {
	public:
		/// @brief Конструктор класса.
		/// Конструктор принимает количество аргументов и их значения
		ArgsParser(int argc, const char** argv);

		/// @brief Метод добавления аргумента командной строки в вектор
		void Add(Argument* arg);

		/// @brief Метод парсинга аргументов командной строки.
		/// Он проходит по каждому аргументу командной строки и проверяет, был ли найден аргумент в векторе
		[[nodiscard]] bool Parse();

		/// @brief Метод поиска аргумента.
		/// В зависимости от оператора вызывает методы поиска короткого или длинного имени.
		[[nodiscard]] Argument* FindArgument(const std::string& argName) const;

		/// @brief Метод для вывода справки об использовании программы.
		/// Выводит описание всех добавленных аргументов командной строки
		void ShowHelp() const;

		/// @brief Метод для вывода дополнительной справки об использовании программы.
		/// Выводит описание всех добавленных аргументов, принимающих параметр, и как использовать.
		void ShowHelpVerbose() const;

	private:
		/// @brief Метод для разбора длинных аргументов командной строки.
		/// Извлекает имя и значение аргумента для дальнейшей обработки.
		void ParseLongArgument(BaseParametrs& p_param);

		/// @brief Метод для разбора коротких аргументов командной строки.
		/// Извлекает имя и значение аргумента для дальнейшей обработки.
		void ParseShortArgument(BaseParametrs& p_param) const;

		/// @brief Метод для обработки одного аргумента командной строки.
		/// Также проверяет его наличие, наличие у него значения, если да, то его проверку.
		void ProcessArgument(BaseParametrs& p_param, int& i) const;

		void ValidationValue(const Validator* validator, BaseParametrs& p_param, Argument* arg, int& i) const;

		/// @brief Метод для поиска длинного имени, если оно есть
		[[nodiscard]] Argument* FindLongNameArg(std::string item) const;

		/// @brief Метод поиска короткого имени, если оно есть
		[[nodiscard]] Argument* FindShortNameArg(std::string item) const;

		/// @brief Метод, который проверяет является ли строка оператором.
		/// Возвращает какой оператор был использован
		[[nodiscard]] OperatorType IsOperator(std::string operatString);

	private:
		/// Сколько всего аргументов.
		int _argc;
		/// Значения аргументов. Должно быть ровно @a argc.
		const char** _argv;
		/// Массив для хранения объектов аргументов командной строки
		std::vector<Argument*> _args;
	};
}