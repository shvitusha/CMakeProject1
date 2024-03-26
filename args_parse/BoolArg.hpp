#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class BoolArg : public Argument {
	public:
		/// @brief  онструктор производного класса.
		///  онструктор дл€ случа€, когда есть как короткое, так и длинное им€
		BoolArg(char shortName, const char* longName) : Argument(shortName, longName) {}

		///  онструктор дл€ случа€, когда нет короткого имени
		BoolArg(const char* longName) : Argument(longName) {}

		/// ѕроверка был ли определен аргумент
		bool IsDefined() const;

		/// ѕроверка соответстви€ переданного аргумента имени
		bool Matches(const std::string& arg);

	private:
		///‘лаг дл€ проверки определен ли аргумент
		bool _isDefined;
		/// ороткое описание аргумента
		char _shortName;
		///ƒлинное описание аргумента
		std::string _longName;
	};
}