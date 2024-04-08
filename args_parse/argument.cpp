#include "argument.hpp"
#include <string>

namespace args_parse {
	Argument::Argument(char shortName, const char* longName, bool isValue) :
		_shortName(shortName), _longName(longName), _isValue(isValue), _description(""), _isDefined(false) {}

	Argument::Argument(const char* longName, bool isValue) : 
		_shortName('\0'), _longName(longName), _isValue(isValue), _description(""), _isDefined(false) {}

	Argument::Argument() : _shortName('\0'), _isValue(false), _description(""), _isDefined(false) {}

	std::string Argument::GetLongName() const { return _longName; }

	void Argument::SetLongName(const char* longName) { _longName = longName; }

	char Argument::GetShortName() const { return _shortName; }

	void Argument::SetShortName(const char shortName) { _shortName = shortName; }

	std::string Argument::GetDescription() const { return _description; };

	void Argument::SetDescription(const std::string& description) { _description = description; }

	void Argument::SetIsDefined(const bool isDefined) { _isDefined = isDefined; }


#pragma region stringArg
	std::string StringArg::GetValue() { return _value; }

	void StringArg::SetValue(std::string& value)
	{
		_value = value;
	}

	const Validator* StringArg::GetValidator() const {
		static StringValidator validator;
		return &validator;
	}
#pragma endregion

#pragma region intArg
	int IntArg::getValue() { return _value; }

	void IntArg::SetValue(std::string& value)
	{
		_value = stoi(value);
	}

	const Validator* IntArg::GetValidator() const {
		static IntValidator validator;
		return &validator;
	}
#pragma endregion

}