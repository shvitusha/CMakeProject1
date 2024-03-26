#include "IntArg.hpp"

namespace args_parse {
	IntArg::IntArg(char shortName, const char* longName) : Argument(shortName, longName) {
		_shortName = shortName;
		_longName = longName;
		_isDefined = false;
		_value = 0;
	}

	IntArg::IntArg(const char* longName) : Argument(longName) {
		_shortName = '\O';
		_longName = longName;
		_isDefined = false;
		_value = 0;
	}

	bool IntArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			_isDefined = true;
			return true;
		}
		return false;
	}

	bool IntArg::IsDefined() const {
		return _isDefined;
	}

	int IntArg::getValue() const { return _value; }


}