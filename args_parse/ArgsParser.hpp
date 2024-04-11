#pragma once
#include "argument.hpp"
#include <vector>
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
		class Validator {
		public:
			virtual bool ValidValue(const std::string& value) const = 0;
		};

		class IntValidator : public Validator {
		public:
			bool ValidValue(const std::string& value) const override {
				if (value.empty()) {
					return false;
				}
				// Создание потока для преобразования строки в int
				std::istringstream iss(value);
				int intValue;
				// Попытка преобразования строки в int
				if (iss >> intValue) {
					// Проверка наличия дополнительных символов после числа
					char remaining;
					if (iss >> remaining) {
						return false; // Дополнительные символы присутствуют
					}
					// Проверка на выход за пределы диапазона int
					if (intValue >= std::numeric_limits<int>::min() && intValue <= std::numeric_limits<int>::max()) {
						return true;
					}
				}
				return false;
			}
		};

		class StringValidator : public Validator {
		public:
			bool ValidValue(const std::string& value) const override {
				//значение может быть пустым
				if (value.empty()) {
					return false;
				}
				// Создание потока для преобразования строки
				std::istringstream iss(value);
				std::string strValue;
				// Попытка преобразования строки
				if (iss >> strValue)
					return true;
				return false;
			}
		};
	#pragma endregion

	class ArgsParser {
		public:
			/// @brief Конструктор класса.
			/// Конструктор принимает количество аргументов и их значения
			ArgsParser(int argc, const char** argv);

			/// @brief Метод добавления аргумента командной строки в вектор
			template<typename T>
			void Add(Argument<T>* arg);

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
			void ValidationValue(const Validator* validator, BaseParametrs& p_param, ArgumentBase* arg, int& i) const;

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