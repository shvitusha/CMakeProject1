#include "StringArg.hpp"

namespace args_parse {
	StringArg::StringArg(char shortName, const char* longName) : Argument(shortName, longName, true) {}

	StringArg::StringArg(const char* longName) : Argument(longName, true) {}

	std::string StringArg::GetValue() { return _value; }

	void StringArg::SetValue( std::string& value)
	{
		_value = value;
	}

	const Validator* StringArg::GetValidator() const {
		static StringValidator validator;
		return &validator;
	}
	
}