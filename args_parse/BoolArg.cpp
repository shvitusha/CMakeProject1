#include "BoolArg.hpp"

namespace args_parse {

	bool BoolArg::Matches(const std::string& arg) {
		if (arg == std::string(1, _shortName) || arg == _longName) {
			_isDefined = true;
			return true;
		}
		return false;
	}

	bool BoolArg::getValue(){ return _value; }

	void BoolArg::setValue(bool value){ _value = value; }
}