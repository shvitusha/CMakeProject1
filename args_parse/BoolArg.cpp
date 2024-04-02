#include "BoolArg.hpp"

namespace args_parse {
	BoolArg::BoolArg(char shortName, const char* longName) : Argument(shortName, longName, false) {}

	BoolArg::BoolArg(const char* longName) : Argument(longName, false) {}

	bool BoolArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			//_isDefined = true;
			return true;
		}
		return false;
	}

	/*bool BoolArg::getValue(){ return _value; }

	void BoolArg::setValue(bool value){ _value = value; }

	bool BoolArg::ValidValue(const std::string& value) {
		if (value == "true" || value == "True" || value == "TRUE") {
			_value = true;
			return true;
		}
		else if (value == "false" || value == "False" || value == "FALSE") {
			_value = false;
			return true;
		}
		return false;
	}*/
	const Validator* BoolArg::GetValidator() const {
		return Argument::GetValidator();
	}
}