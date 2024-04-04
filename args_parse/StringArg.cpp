#include "StringArg.hpp"

namespace args_parse {
	StringArg::StringArg(char shortName, const char* longName) : Argument(shortName, longName, true) {}

	StringArg::StringArg(const char* longName) : Argument(longName, true) {}

	bool StringArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			//_isDefined = true;
			return true;
		}
		return false;
	}

	std::string StringArg::getValue() { return _value; }

	void StringArg::setValue(std::string value) { _value = value; }

	const Validator* StringArg::GetValidator() const {
		static StringValidator validator;
		return &validator;
	}
}