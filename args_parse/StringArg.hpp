#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class StringArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		/// @brief Конструктор производного класса.
		/// Конструктор для случая, когда есть как короткое, так и длинное имя
		StringArg(char shortName, const char* longName, std::string value);

		/// Конструктор для случая, когда нет короткого имени
		StringArg(const char* longName, std::string value);

		/// Проверка соответствия переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///Получение строкового значения аргумента
		std::string getValue();

		///Присваивание строкового значения аргументу
		void setValue(std::string value);

		bool ValidValue(const std::string& value) override;

		bool HasValue() const override;

	private:
		std::string _value;
	};
}