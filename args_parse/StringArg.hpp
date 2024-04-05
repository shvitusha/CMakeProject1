#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class StringArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		/// @brief  конструктор производного класса.
		/// конструктор для случая, когда есть как короткое, так и длинное имя
		StringArg(char shortName, const char* longName);

		/// конструктор для случая, когда нет короткого имени
		StringArg(const char* longName);

		/// проверка соответствия переданного аргумента имени
		bool Matches(const std::string& arg) override;

		///получение строкового значения аргумента
		std::string GetValue();

		///присваивание строкового значения аргументу
		void SetValue(std::string& value) override;

		/// @brief метод для получения указателя на объект валидатора, связанного с аргументом.
		///если для данного аргумента не определен валидатор, метод возвращает nullptr.
		const Validator* GetValidator() const override;

	private:
		std::string _value;
	};
}