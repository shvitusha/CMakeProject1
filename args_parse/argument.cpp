#include "argument.hpp"

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

	std::string Argument::GetLongName() const { return _longName; }

	void Argument::SetLongName(const char* longName) { _longName = longName; }

	char Argument::GetShortName() const { return _shortName; }

	void Argument::SetShortName(const char shortName) { _shortName = shortName; }

	std::string Argument::GetDescription() const { return _description; };

	void Argument::SetDescription(const std::string& description) { _description = description; }

	bool Argument::Matches(const std::string& arg) const{
		return arg == _shortName || arg == _longName;
	}

	bool Argument::IsDefined() const {
		return _isDefined;
	}
}