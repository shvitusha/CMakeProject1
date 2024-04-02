#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class BoolArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		/// @brief Конструктор производного класса.
		/// Конструктор для случая, когда есть как короткое, так и длинное имя
		BoolArg(char shortName, const char* longName);

		/// Конструктор для случая, когда нет короткого имени
		BoolArg(const char* longName);

		/// Проверка соответствия переданного аргумента имени
		bool Matches(const std::string& arg) override;

		const Validator* GetValidator() const override;
		//	///Получение булевого значения аргумента
		//	bool getValue();

		//	///Присваивание булевого значения аргументу
		//	void setValue(bool value);

		//	bool ValidValue(const std::string& value) override;

		//private:
		//	bool _value;
	};
}