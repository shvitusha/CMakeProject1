#pragma once
#include <string>

namespace args_parse {
	class Validator {
	public:
		virtual bool ValidValue(const std::string_view& value) const = 0;
	};

	class IntValidator : public Validator {
	public:
		bool ValidValue(const std::string_view& value) const override {
			try {
				std::stoi(std::string(value));
				return true;
			}
			catch (const std::exception&) {
				return false;
			}
		}
	};

	class StringValidator : public Validator {
	public:
		bool ValidValue(const std::string_view& value) const override {
			if (value.length() <= 20)
				return true;
			else
				return false;
		}
	};
}