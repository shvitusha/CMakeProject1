#include "IntArg.hpp"
#include <string>

using namespace std;

namespace args_parse {
	IntArg::IntArg(char shortName, const char* longName) : Argument(shortName, longName, true) {}

	IntArg::IntArg(const char* longName) : Argument(longName, true) {}

	bool IntArg::Matches(const string& arg) {
		if (arg == string(1, _shortName) || arg == _longName) {
			//_isDefined = true;
			return true;
		}
		return false;
	}

	int IntArg::getValue() { return _value; }

	void IntArg::setValue(int value) { _value = value; }

	/*bool IntArg::ValidValue(const string& value) {
		try
		{
			_value = stoi(value);
			return true;
		}
		catch (const invalid_argument&)
		{
			return false;
		}
	}*/

	const Validator* IntArg::GetValidator() const {
		static IntValidator validator;
		return &validator;
	}
}