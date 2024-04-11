#include "argument.hpp"
#include <string>

namespace args_parse {
	template<typename T>
	Argument<T>::Argument(char shortName, const char* longName, bool isValue) :
		_shortName(shortName), _longName(longName), _isValue(isValue), _description(""), _isDefined(false) {}

	template<typename T>
	Argument<T>::Argument(const char* longName, bool isValue) :
		_shortName('\0'), _longName(longName), _isValue(isValue), _description(""), _isDefined(false) {}

	template<typename T>
	Argument<T>::Argument() : _shortName('\0'), _isValue(false), _description(""), _isDefined(false) {}

	template<typename T>
	std::string Argument<T>::GetLongName() const { return _longName; }

	template<typename T>
	void Argument<T>::SetLongName(const char* longName) { _longName = longName; }

	template<typename T>
	char Argument<T>::GetShortName() const { return _shortName; }

	template<typename T>
	void Argument<T>::SetShortName(const char shortName) { _shortName = shortName; }

	template<typename T>
	std::string Argument<T>::GetDescription() const { return _description; };

	template<typename T>
	void Argument<T>::SetDescription(const std::string& description) { _description = description; }

	template<typename T>
	void Argument<T>::SetIsDefined(const bool isDefined) { _isDefined = isDefined; }


#pragma region stringArg
	std::string StringArg::GetValue() { return _value; }

	void StringArg::SetValue(const std::string& value)
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

	void IntArg::SetValue(const std::string& value)
	{
		_value = stoi(value);
	}

	const Validator* IntArg::GetValidator() const {
		static IntValidator validator;
		return &validator;
	}
#pragma endregion

}