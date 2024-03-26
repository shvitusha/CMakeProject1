#include "BoolArg.hpp"

namespace args_parse {
	BoolArg::BoolArg(char shortName, const char* longName) : Argument(shortName, longName) {
		_shortName = shortName;
		_longName = longName;
		_isDefined = false;
	}

	BoolArg::BoolArg(const char* longName) : Argument(longName) {
		_shortName = '\O';
		_longName = longName;
		_isDefined = false;
	}

	bool BoolArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			_isDefined = true;
			return true;
		}
		return false;
	}

	bool BoolArg::IsDefined() const {
		return _isDefined;
	}
}