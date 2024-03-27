#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class BoolArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		/// Проверка соответствия переданного аргумента имени
		bool Matches(const std::string& arg);

		///Получение булевого значения аргумента
		bool getValue() const;

		///Присваивание булевого значения аргументу
		void setValue(bool value);

	private:
		bool _value;
	};
}