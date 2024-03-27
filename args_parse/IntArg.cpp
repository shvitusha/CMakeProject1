#include "IntArg.hpp"

namespace args_parse {

	IntArg::IntArg(char shortName, const char* longName, int value) : Argument(shortName, longName) {
		_value = value;
	}

	IntArg::IntArg(const char* longName, int value) : Argument(longName) {
		_value = value;
	}

	bool IntArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			_isDefined = true;
			return true;
		}
		return false;
	}

	int IntArg::getValue() { return _value; }

	void IntArg::setValue(int value) { _value = value; }
}