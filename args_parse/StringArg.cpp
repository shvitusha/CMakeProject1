#include "StringArg.hpp"

namespace args_parse {
	StringArg::StringArg(char shortName, const char* longName) : Argument(shortName, longName) {
		_shortName = shortName;
		_longName = longName;
		_isDefined = false;
	}

	StringArg::StringArg(const char* longName) : Argument(longName) {
		_shortName = '\O';
		_longName = longName;
		_isDefined = false;
	}

	bool StringArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			_isDefined = true;
			return true;
		}
		return false;
	}

	bool StringArg::IsDefined() const {
		return _isDefined;
	}
}