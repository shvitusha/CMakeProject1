#pragma once
#include <sstream>
#include <string>

namespace args_parse {
	class Validator {
	public:
		virtual bool ValidValue(const std::string& value) const = 0;
	};

	class IntValidator : public Validator {
	public:
		bool ValidValue(const std::string& value) const override {
			/*try {
				std::stoi(value);
				return true;
			}
			catch (const std::exception&) {
				return false;
			}*/
			if (value.empty()) {
				return false;
			}
			// Создание потока для преобразования строки в int
			std::istringstream iss(value);
			int intValue;
			// Попытка преобразования строки в int
			if (iss >> intValue) {
				// Проверка наличия дополнительных символов после числа
				char remaining;
				if (iss >> remaining) {
					return false; // Дополнительные символы присутствуют
				}

				// Проверка на выход за пределы диапазона int
				if (intValue >= std::numeric_limits<int>::min() && intValue <= std::numeric_limits<int>::max()) {
					return true;
				}
			}
			return false;
		}
	};

	class StringValidator : public Validator {
	public:
		bool ValidValue(const std::string& value) const override {
			if (value.length() <= 20)
				return true;
			else
				return false;
		}
	};
}