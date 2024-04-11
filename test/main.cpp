#include <catch2/catch_all.hpp>

#include <args_parse/argument.hpp>
#include <args_parse/ArgsParser.hpp>

#include <iostream>
#include <memory>

//static args_parse::ArgsParser getTestParser(int argc, const char** argv) {
//	args_parse::ArgsParser parser(argc, argv);
//	args_parse::Argument<bool> help('h', "help", false);
//	args_parse::Argument<bool> verbose('v', "verbose", false);
//	args_parse::Argument<std::string> output('o', "output", true);
//	args_parse::Argument<int> number('n', "number", true);
//
//	//vector.push_back(std::make_unique<args_parse::BoolArg>(help));
//	//vector.push_back(std::make_unique<args_parse::BoolArg>(verbose));
//	//vector.push_back(std::make_unique<args_parse::StringArg>(output));
//	//vector.push_back(std::make_unique<args_parse::IntArg>(number));
//	parser.Add(&help);
//	parser.Add(&verbose);
//	parser.Add(&output);
//	parser.Add(&number);
//	/*
//	for (auto& arg : vector)
//	{
//		parser.Add(arg.get());
//	}*/
//	return parser;
//}

TEST_CASE("Parse value", "[ArgsParser]") {
	args_parse::Argument<bool> help('h', "help", false);
	args_parse::Argument<bool> verbose('v', "verbose", false);
	args_parse::Argument<std::string> output('o', "output", true);
	args_parse::Argument<int> number('n', "number", true);

	const char* argv[] = { "program", "-h", "--output=file.txt", "-n25", "--number=2", "--string", "--output-path=path" };
	int argc = 7;
	args_parse::ArgsParser parser(argc, argv);
	parser.Add(&help);
	parser.Add(&verbose);
	parser.Add(&output);
	parser.Add(&number);

	SECTION("Parsing arguments") {
		REQUIRE(parser.Parse() == true);

		REQUIRE_THROWS_AS(parser.Parse(), std::invalid_argument);
	}

	args_parse::Argument<bool> newArg('t', "test", false);
	parser.Add(&newArg);

	SECTION("Find new added argument") {
		REQUIRE(parser.FindArgument("t") != nullptr);
		REQUIRE(parser.FindArgument("te") != nullptr);
		REQUIRE(parser.FindArgument("test") != nullptr);
	}

	args_parse::Validator<int>* IntValidator = new args_parse::Validator<int>();

	SECTION("Valid integer values") {
		REQUIRE(IntValidator->ValidValue("10") == true);
		REQUIRE(IntValidator->ValidValue("-5") == true);
	}

	SECTION("Invalid integer values") {
		REQUIRE(IntValidator->ValidValue("") == false);
		REQUIRE(IntValidator->ValidValue("abc") == false);
	}

	args_parse::Validator<std::string>* StringValidator = new args_parse::Validator<std::string>();

	SECTION("Valid string values") {
		REQUIRE(StringValidator->ValidValue("hello") == true);
		REQUIRE(StringValidator->ValidValue("world") == true);
	}

	SECTION("Invalid string values") {
		REQUIRE(StringValidator->ValidValue("") == false);
	}

	/*const char* argv[] = { "program", "-h", "--output=file.txt", "-n25", "--number=2", "--string", "--output-path=path" };
	int argc = 7;
	args_parse::ArgsParser parser(argc, argv);*/

	SECTION("Finding existing arguments") {
		REQUIRE(parser.FindArgument("h") != nullptr);
		REQUIRE(parser.FindArgument("output") != nullptr);
	}

	args_parse::Argument<std::string> longArg("", "string");
	parser.Add(&longArg);
	args_parse::Argument<std::string> nonUnique("", "output-path");

	SECTION("Non-unique argument addition") {
		REQUIRE_THROWS_AS(parser.Add(&nonUnique), std::invalid_argument);
	}

	SECTION("Finding non-existing arguments") {
		REQUIRE_THROWS_AS(parser.FindArgument("x"), std::invalid_argument);
		REQUIRE_THROWS_AS(parser.FindArgument("invalid"), std::invalid_argument);
		REQUIRE_THROWS_AS(parser.FindArgument("s"), std::invalid_argument);
	}

	/*static std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::ArgumentBase>>> getTestParser(int argc, const char** argv) {
	std::vector<std::unique_ptr<args_parse::ArgumentBase>> vector;
	args_parse::ArgsParser parser(argc, argv);
	args_parse::Argument<bool> help('h', "help", false);
	args_parse::Argument<bool> verbose('v', "verbose", false);
	args_parse::Argument<std::string> output('o', "output", true);
	args_parse::Argument<int> number('n', "number", true);

	parser.Add(&help);
	parser.Add(&verbose);
	parser.Add(&output);
	parser.Add(&number);
	return { parser, move(vector) };
}

TEST_CASE("Parse value", "[ArgsParser]") {
	const char* argv[] = { "program", "-v", "--output=file.txt", "-n10", "--number=27" };
	int argc = 5;
	std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::ArgumentBase>>> pair = getTestParser(argc, argv);
	args_parse::ArgsParser parser = pair.first;

	SECTION("Parsing valid arguments") {
		REQUIRE(parser.Parse() == true);
	}

	SECTION("Parsing invalid arguments") {
		const char* invalidArgv[] = { "program", "-x", "--input" };
		int invalidArgc = 3;
		std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::ArgumentBase>>> pair = getTestParser(invalidArgc, invalidArgv);
		args_parse::ArgsParser invalidParser = pair.first;

		REQUIRE_THROWS_AS(invalidParser.Parse(), std::invalid_argument);
	}

	args_parse::Argument<bool> newArg('t', "test", false);
	parser.Add(&newArg);

	SECTION("Find new added argument") {
		REQUIRE(parser.FindArgument("t") != nullptr);
		REQUIRE(parser.FindArgument("te") != nullptr);
		REQUIRE(parser.FindArgument("test") != nullptr);
	}
}

TEST_CASE("Int ValidValue", "[IntValidValue]") {
	args_parse::Validator<int> validator;

	SECTION("Valid integer values") {
		REQUIRE(validator.ValidValue("10") == true);
		REQUIRE(validator.ValidValue("-5") == true);
	}

	SECTION("Invalid integer values") {
		REQUIRE(validator.ValidValue("") == false);
		REQUIRE(validator.ValidValue("abc") == false);
	}
}

TEST_CASE("String ValidValue", "[StringValidator]") {
	args_parse::Validator<std::string> validator;

	SECTION("Valid string values") {
		REQUIRE(validator.ValidValue("hello") == true);
		REQUIRE(validator.ValidValue("world") == true);
	}

	SECTION("Invalid string values") {
		REQUIRE(validator.ValidValue("") == false);
	}
}

TEST_CASE("FindArgument", "[ArgsParser]") {
	const char* argv[] = { "program", "-h", "--output=file.txt", "-n25", "--number=2", "--string", "--output-path=path" };
	int argc = 7;
	std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::ArgumentBase>>> pair = getTestParser(argc, argv);
	args_parse::ArgsParser parser = pair.first;

	SECTION("Finding existing arguments") {
		REQUIRE(parser.FindArgument("h") != nullptr);
		REQUIRE(parser.FindArgument("output") != nullptr);
	}

	args_parse::Argument<std::string> longArg("", "string");
	parser.Add(&longArg);
	args_parse::Argument<std::string> nonUnique("", "output-path");

	SECTION("Non-unique argument addition") {
		REQUIRE_THROWS_AS(parser.Add(&nonUnique), std::invalid_argument);
	}

	SECTION("Finding non-existing arguments") {
		REQUIRE_THROWS_AS(parser.FindArgument("x"), std::invalid_argument);
		REQUIRE_THROWS_AS(parser.FindArgument("invalid"), std::invalid_argument);
		REQUIRE_THROWS_AS(parser.FindArgument("s"), std::invalid_argument);
	}
}*/
}