#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class IntArg : public Argument {
	public:
		/// @brief  онструктор производного класса.
		///  онструктор дл€ случа€, когда есть как короткое, так и длинное им€
		IntArg(char shortName, const char* longName);

		///  онструктор дл€ случа€, когда нет короткого имени
		IntArg(const char* longName);

		///наследование конструктора базового класса
		using Argument::Argument;

		/// ѕроверка соответстви€ переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///ѕолучение числового значени€ аргумента
		int getValue();

		///ѕрисваивание числового значени€ аргументу
		///value после валидации
		void SetValue(std::string& value) override;

		/// @brief ћетод дл€ получени€ указател€ на объект валидатора, св€занного с аргументом.
		///≈сли дл€ данного аргумента не определен валидатор, метод возвращает nullptr.
		const Validator* GetValidator() const override;

	private:
		///«начение аргумента
		int _value;
	};
}