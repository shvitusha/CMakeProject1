#include <catch2/catch_all.hpp>

#include <args_parse/BoolArg.hpp>
#include <args_parse/StringArg.hpp>
#include <args_parse/IntArg.hpp>
#include <args_parse/ArgsParser.hpp>

#include <iostream>
#include <memory>

static std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::Argument>>> getTestParser(int argc, const char** argv) {
	std::vector<std::unique_ptr<args_parse::Argument>> vector;
	args_parse::ArgsParser parser(argc, argv);
	args_parse::BoolArg help('h', "help");
	args_parse::BoolArg verbose('v', "verbose");
	args_parse::StringArg output('o', "output");
	args_parse::IntArg number('n', "number");

	vector.push_back(std::make_unique<args_parse::BoolArg>(help));
	vector.push_back(std::make_unique<args_parse::BoolArg>(verbose));
	vector.push_back(std::make_unique<args_parse::StringArg>(output));
	vector.push_back(std::make_unique<args_parse::IntArg>(number));

	for (auto& arg : vector)
	{
		parser.Add(arg.get());
	}
	return { parser, move(vector) };
}

TEST_CASE("Parse value", "[ArgsParser]") {
	const char* argv[] = { "program", "-v", "--output=file.txt", "-n10", "--number=27" };
	int argc = sizeof(argv) / sizeof(const char*);
	std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::Argument>>> pair = getTestParser(argc, argv);
	args_parse::ArgsParser parser = pair.first;

	SECTION("Parsing valid arguments") {
		REQUIRE(parser.Parse() == true);
	}

	SECTION("Parsing invalid arguments") {
		const char* invalidArgv[] = { "program", "-x", "--input" };
		int invalidArgc = sizeof(invalidArgv) / sizeof(const char*);
		std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::Argument>>> pair = getTestParser(invalidArgc, invalidArgv);
		args_parse::ArgsParser invalidParser = pair.first;

		REQUIRE_THROWS_AS(invalidParser.Parse(), std::invalid_argument);
	}

	args_parse::BoolArg newArg('t', "test");
	parser.Add(&newArg);

	SECTION("Find new added argument") {
		REQUIRE(parser.FindArgument("t") != nullptr);
		REQUIRE(parser.FindArgument("te") != nullptr);
		REQUIRE(parser.FindArgument("test") != nullptr);
	}
}

TEST_CASE("Int ValidValue", "[IntValidValue]") {
	args_parse::IntValidator validator;

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
	args_parse::StringValidator validator;

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
	int argc = sizeof(argv) / sizeof(const char*);
	std::pair<args_parse::ArgsParser, std::vector<std::unique_ptr<args_parse::Argument>>> pair = getTestParser(argc, argv);
	args_parse::ArgsParser parser = pair.first;

	SECTION("Finding existing arguments") {
		REQUIRE(parser.FindArgument("h") != nullptr);
		REQUIRE(parser.FindArgument("output") != nullptr);
	}

	args_parse::StringArg longArg('\0', "string");
	parser.Add(&longArg);
	args_parse::StringArg nonUnique('\0', "output-path");

	SECTION("Non-unique argument addition") {
		REQUIRE_THROWS_AS(parser.Add(&nonUnique), std::invalid_argument);
	}

	SECTION("Finding non-existing arguments") {
		REQUIRE_THROWS_AS(parser.FindArgument("x"), std::invalid_argument);
		REQUIRE_THROWS_AS(parser.FindArgument("invalid"), std::invalid_argument);
		REQUIRE_THROWS_AS(parser.FindArgument("s"), std::invalid_argument);
	}
}