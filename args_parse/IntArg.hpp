#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class IntArg : public Argument {
	public:
		/// @brief конструктор производного класса.
		/// конструктор для случая, когда есть как короткое, так и длинное им¤
		IntArg(char shortName, const char* longName);

		/// конструктор для случая, когда нет короткого имени
		IntArg(const char* longName);

		///наследование конструктора базового класса
		using Argument::Argument;

		/// проверка соответствия переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///получение числового значени¤ аргумента
		int getValue();

		///присваивание числового значения аргументу
		///value после валидации
		void SetValue(std::string& value) override;

		/// @brief метод для получения указателя на объект валидатора, связанного с аргументом.
		///если для данного аргумента не определен валидатор, метод возвращает nullptr.
		const Validator* GetValidator() const override;

	private:
		///«начение аргумента
		int _value;
	};
}