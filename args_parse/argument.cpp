#include "argument.hpp"
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	Argument::Argument(char shortName, const char* longName) {
		_shortName = shortName;
		_longName = longName;
		_description = "";
		_isDefined = false;
	}

	Argument::Argument(const char* longName)
	{
		_shortName = '\O';
		_longName = longName;
		_description = "";
		_isDefined = false;
	}

	Argument::~Argument() {}

	std::string Argument::GetLongName() const { return _longName; }

	std::string Argument::SetLongName(const char* longName) const { _longName = longName; }

	std::string Argument::GetShortName() const { return _shortName; }

	std::string Argument::SetShortName(const char shortName) const { _shortName = shortName; }

	std::string Argument::GetDescription() const { return _description; };

	std::string Argument::SetDescription(const std::string& description) const { _description = description; }

	bool Argument::Matches(const std::string& arg) const {
		return arg == _shortName || arg == _longName;
	}

	bool Argument::IsDefined() const {
		return _isDefined;
	}
}