#include "argument.hpp"

namespace args_parse {
	Argument::Argument(char shortName, const char* longName, bool isValue) :
		_shortName(shortName), _longName(longName), _isValue(isValue), _description(""), _isDefined(false) {}

	Argument::Argument(const char* longName, bool isValue) : 
		Argument('\0',longName, isValue){}

	Argument::Argument() : Argument('\0', "", false) {}

	std::string Argument::GetLongName() const { return _longName; }

	void Argument::SetLongName(const char* longName) { _longName = longName; }

	char Argument::GetShortName() const { return _shortName; }

	void Argument::SetShortName(const char shortName) { _shortName = shortName; }

	std::string Argument::GetDescription() const { return _description; };

	void Argument::SetDescription(const std::string& description) { _description = description; }

	void Argument::SetIsDefined(const bool isDefined) { _isDefined = isDefined; }
}