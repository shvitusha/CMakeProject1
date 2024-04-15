#pragma once
#include "argument.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <string>
#include <string_view>

namespace args_parse {
	class ArgumentBase;
	template<typename T>
	class Argument;
	template<>
	class Argument<std::chrono::milliseconds>;

	/// @brief Перечисление типов оператора (длинный, короткий, неопределенный)
	enum class OperatorType {
		Long,
		Short,
		Nope
	};
	/// @brief Структура для определения параметров
	struct BaseParametrs {
		std::string_view argStr;
		std::string_view argName;
		std::string_view argValue;
	};

#pragma region Validation
	
	template<typename T>
	class Validator {
	public:
		Validator() = default;

		[[nodiscard]] bool ValidValue(const std::string& value) const {
			if (value.empty()) {
				return false;
			}
			std::istringstream iss(value);
			std::optional<T> value_t;

			if (iss >> value_t) {
				return Additional(value_t);
			}
			return false;
		}
	private:

		[[nodiscard]] bool Additional(const T& value) const {
			if constexpr (std::is_same_v<int, T>) {
				return (value == std::floor(value)) && (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max());
			}

			else if constexpr (std::is_same_v<float, T>) {
				return (value >= std::numeric_limits<float>::lowest() && value <= std::numeric_limits<float>::max());
			}

			else if constexpr (std::is_same_v<unsigned int, T>) {
				return (value >= 0 && value <= std::numeric_limits<unsigned int>::max());
			}

			else if constexpr (std::is_same_v<std::string, T>) {
				return true;
			}
			else {
				return false;
			}
			return true;
		}
	};

	template<>
	class Validator<std::chrono::milliseconds> {
	public:
		Validator<std::chrono::milliseconds>() = default;

		[[nodiscard]] bool ValidValue(const std::string& value) const {
			long long l_value;
			std::string unit;

			std::istringstream ss{ value };
			// Считываем значение и единицу измерения времени из потока
			ss >> l_value >> unit;

			std::chrono::milliseconds ms;

			// Преобразуем значение и единицу измерения времени в микросекунды
			if (unit == "ms") {
				ms = std::chrono::milliseconds(l_value);
			}
			else if (unit == "s") {
				ms = std::chrono::seconds(l_value);
			}
			else {
				std::cerr << "Invalid time unit: " << unit << std::endl;
				return false;
			}
			return true;
		}
	};

#pragma endregion

	class ArgsParser {
	public:
		/// @brief Конструктор класса.
		/// Конструктор принимает количество аргументов и их значения
		ArgsParser(int argc, const char** argv);

		/// @brief Метод добавления аргумента командной строки в вектор
		void Add(ArgumentBase* arg);

		/// @brief Метод парсинга аргументов командной строки.
		/// Он проходит по каждому аргументу командной строки и проверяет, был ли найден аргумент в векторе
		[[nodiscard]] bool Parse();

		/// @brief Метод для вывода справки об использовании программы.
		/// Выводит описание всех добавленных аргументов командной строки
		void ShowHelp() const;

		/// @brief Метод для вывода дополнительной справки об использовании программы.s
		/// Выводит описание всех добавленных аргументов, принимающих параметр, и как использовать.
		void ShowHelpVerbose() const;

		/// @brief Метод поиска аргумента.
		/// В зависимости от оператора вызывает методы поиска короткого или длинного имени.
		[[nodiscard]] ArgumentBase* FindArgument(BaseParametrs param) const;

	private:
		/// @brief Метод для разбора длинных аргументов командной строки.
		/// Извлекает имя и значение аргумента для дальнейшей обработки.
		[[nodiscard]] BaseParametrs ParseLongArgument(BaseParametrs p_param);

		/// @brief Метод для разбора коротких аргументов командной строки.
		/// Извлекает имя и значение аргумента для дальнейшей обработки.
		[[nodiscard]] BaseParametrs ParseShortArgument(BaseParametrs p_param) const;

		/// @brief Метод для обработки одного аргумента командной строки.
		/// Также проверяет его наличие, наличие у него значения, если да, то его проверку.
		void ProcessArgument(BaseParametrs p_param, int& i) const;

		/// @brief Метод валидации значения
		void ValidationValue(BaseParametrs p_param, ArgumentBase* arg, int& i) const;

		/// @brief Метод для поиска длинного имени, если оно есть
		[[nodiscard]] ArgumentBase* FindLongNameArg(std::string_view item) const;

		/// @brief Метод поиска короткого имени, если оно есть
		[[nodiscard]] ArgumentBase* FindShortNameArg(std::string_view item) const;

		/// @brief Метод, который проверяет является ли строка оператором.
		/// Возвращает какой оператор был использован
		[[nodiscard]] OperatorType IsOperator(std::string_view operatString);

		/// Сколько всего аргументов.
		int _argc;
		/// Значения аргументов. Должно быть ровно @a argc.
		const char** _argv;
		/// Массив для хранения объектов аргументов командной строки
		std::vector<ArgumentBase*> _args;
	};
}