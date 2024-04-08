#include "IntArg.hpp"
#include <string>

using namespace std;

namespace args_parse {
	IntArg::IntArg(char shortName, const char* longName) : Argument(shortName, longName, true) {}

	IntArg::IntArg(const char* longName) : Argument(longName, true) {}

	int IntArg::getValue() { return _value; }

	void IntArg::SetValue(std::string& value)
	{
		_value = stoi(value);
	}

	const Validator* IntArg::GetValidator() const {
		static IntValidator validator;
		return &validator;
	}
}