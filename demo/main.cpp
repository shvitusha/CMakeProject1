#include "args_parse/ArgsParser.hpp"


int main(int argc, const char** argv) {
	ArgsParser::ArgsParser parser(argc, argv);

	BoolArg help('h', "help");
	StringArg input('i', "input");
	StringArg output('o', "output");
	IntArg number('n', "number");

	return 0;