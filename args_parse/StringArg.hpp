#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class StringArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		/// @brief  онструктор производного класса.
		///  онструктор дл€ случа€, когда есть как короткое, так и длинное им€
		StringArg(char shortName, const char* longName);

		///  онструктор дл€ случа€, когда нет короткого имени
		StringArg(const char* longName);

		/// ѕроверка соответстви€ переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///ѕолучение строкового значени€ аргумента
		std::string getValue();

		///ѕрисваивание строкового значени€ аргументу
		void setValue(std::string value);

		/// @brief ћетод дл€ получени€ указател€ на объект валидатора, св€занного с аргументом.
		///≈сли дл€ данного аргумента не определен валидатор, метод возвращает nullptr.
		const Validator* GetValidator() const override;

	private:
		std::string _value;
	};
}