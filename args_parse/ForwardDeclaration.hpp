#pragma once
//
//#include "ArgsParser.hpp"
//#include "argument.hpp"
#include <chrono>

 //forward declarations
namespace args_parser {
	class SharedValidator;
	class ArgumentBase;
	template<typename T>
	class Argument;
	template<>
	class Argument<std::chrono::milliseconds>;
	class ArgsParser;
	template<typename T>
	class Validator;
	template<>
	class Validator<std::chrono::milliseconds>;
	enum class OperatorType;
	struct BaseParametrs;
}