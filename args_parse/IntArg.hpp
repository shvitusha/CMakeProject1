#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class IntArg : public Argument {
	public:
		/// @brief  онструктор производного класса.
		///  онструктор дл€ случа€, когда есть как короткое, так и длинное им€
		IntArg(char shortName, const char* longName, int value);

		///  онструктор дл€ случа€, когда нет короткого имени
		IntArg(const char* longName, int value);

		///наследование конструктора базового класса
		using Argument::Argument;

		/// ѕроверка соответстви€ переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///ѕолучение числового значени€ аргумента
		int getValue();

		///ѕрисваивание числового значени€ аргументу
		void setValue(int value);

		bool ValidValue(const std::string& value) override;
		
		bool HasValue() const override;

	private:
		///«начение аргумента
		int _value;
	};
}