#include "IntArg.hpp"
#include <string>

using namespace std;

namespace args_parse {

	IntArg::IntArg(char shortName, const char* longName, int value) : Argument(shortName, longName) {
		_value = value;
	}

	IntArg::IntArg(const char* longName, int value) : Argument(longName) {
		_value = value;
	}

	bool IntArg::Matches(const string& arg) {
		if (arg == string(1, _shortName) || arg == _longName) {
			_isDefined = true;
			return true;
		}
		return false;
	}

	int IntArg::getValue() { return _value; }

	void IntArg::setValue(int value) { _value = value; }

	bool IntArg::ValidValue(const string& value) {
		try
		{
			_value = stoi(value);
			return true;
		}
		catch (const invalid_argument&)
		{
			return false;
		}
	}
}