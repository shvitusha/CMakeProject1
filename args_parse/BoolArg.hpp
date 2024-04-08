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
		BoolArg(char shortName, const char* longName) : Argument(shortName, longName, false) {}

		/// Конструктор для случая, когда нет короткого имени
		BoolArg(const char* longName) : Argument(longName, false) {}

		const Validator* GetValidator() const { return nullptr; }

		///Присваивание булевого значения аргументу
		void SetValue(std::string& value) override {
			_value = value;
		}

		private:
			std::string _value;
	};
}