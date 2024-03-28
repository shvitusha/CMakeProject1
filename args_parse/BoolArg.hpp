#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class BoolArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		/// Проверка соответствия переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///Получение булевого значения аргумента
		bool getValue();

		///Присваивание булевого значения аргументу
		void setValue(bool value);

		bool ValidValue(const std::string& value) override;

	private:
		bool _value;
	};
}