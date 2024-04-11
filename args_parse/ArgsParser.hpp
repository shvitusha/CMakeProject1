#pragma once
#include "argument.hpp"
#include <vector>
#include <chrono>
#include <sstream>
#include <string>

namespace args_parse {
	class ArgumentBase;

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

#pragma region Validation
	///Абстрактный базовый класс для валидаторов значений
	class SharedValidator {
	public:
		SharedValidator() = default;
		virtual ~SharedValidator() {}
		virtual bool ValidValue(const std::string& value) const = 0;
	};

	template<typename T>
	class Validator : public SharedValidator {
	public:
		using SharedValidator::SharedValidator;
		bool ValidValue(const std::string& value) const override {
			std::string str = value;
			if (str.empty()) {
				return false;
			}
			std::tuple<bool, std::string> chrono = CheckChronoValue(str);
			if (std::get<0>(chrono)) {
				str = std::get<1>(chrono);
			}
			std::istringstream iss(str);
			T value_t;
			if (iss >> value_t) {
				return Additional(value_t);
			}
			return false;
		}
	private:
		bool Additional(const T& value) const {
			if constexpr (std::is_same_v<int, T>) {
				if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max())
					return true;
			}
			else if constexpr (std::is_same_v<float, T>) {
				if (value >= std::numeric_limits<float>::lowest() && value <= std::numeric_limits<float>::max())
					return true;
			}
			else if constexpr (std::is_same_v<unsigned int, T>) {
				if (value <= std::numeric_limits<unsigned int>::max())
					return true;
			}
			else if constexpr (std::is_same_v<std::string, T>) {
				return true;
			}
			else {
				return false;
			}
		}

		std::tuple<bool, std::string> CheckChronoValue(const std::string& value) const {
			// Проверяем, содержит ли строка подстроку "ms" или "s"
			bool isMilliseconds = false;
			bool isSeconds = false;
			if (value.size() > 2) {
				std::string suffix = value.substr(value.size() - 2);
				if (suffix == "ms") {
					isMilliseconds = true;
				}
				else if (suffix == "s") {
					isSeconds = true;
				}
			}

			// Удаляем суффикс "ms" или "s" из строки, если он присутствует
			std::string strippedValue = value;
			if (isMilliseconds || isSeconds) {
				strippedValue = value.substr(0, value.size() - 2);
			}
			return std::make_tuple((isSeconds || isMilliseconds), strippedValue);
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
		bool Parse();

		/// @brief Метод для вывода справки об использовании программы.
		/// Выводит описание всех добавленных аргументов командной строки
		void ShowHelp() const;

		/// @brief Метод для вывода дополнительной справки об использовании программы.s
		/// Выводит описание всех добавленных аргументов, принимающих параметр, и как использовать.
		void ShowHelpVerbose() const;

		/// @brief Метод поиска аргумента.
		/// В зависимости от оператора вызывает методы поиска короткого или длинного имени.
		ArgumentBase* FindArgument(const std::string& argName) const;

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

		/// @brief Метод валидации значения
		void ValidationValue(const SharedValidator* validator, BaseParametrs& p_param, ArgumentBase* arg, int& i) const;

		/// @brief Метод для поиска длинного имени, если оно есть
		ArgumentBase* FindLongNameArg(std::string item) const;

		/// @brief Метод поиска короткого имени, если оно есть
		ArgumentBase* FindShortNameArg(std::string item) const;

		/// @brief Метод, который проверяет является ли строка оператором.
		/// Возвращает какой оператор был использован
		OperatorType IsOperator(std::string operatString);

		/// Сколько всего аргументов.
		int _argc;
		/// Значения аргументов. Должно быть ровно @a argc.
		const char** _argv;
		/// Массив для хранения объектов аргументов командной строки
		std::vector<ArgumentBase*> _args;
	};
}