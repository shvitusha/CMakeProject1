#include <args_parse/argument.hpp>
#include <args_parse/ArgsParser.hpp>
#include <iostream>

int main(int argc, const char** argv)
{
	args_parse::ArgsParser parser(argc, argv);

	args_parse::BoolArg help('h', "help", false);
	help.SetDescription("Outputs a description of all added command line arguments");
	args_parse::BoolArg verbose('v', "verbose", false);
	verbose.SetDescription("Outputs a verbose of all added command line arguments");
	args_parse::StringArg input('i', "input", true);
	input.SetDescription("Input (filename)");
	args_parse::StringArg output('o', "output", true);
	output.SetDescription("Output (filename)");
	args_parse::IntArg number('n', "number", true);
	number.SetDescription("Assigns a numeric value to an argument");

	parser.Add(&help);
	parser.Add(&verbose);
	parser.Add(&input);
	parser.Add(&output);
	parser.Add(&number);

	if (parser.Parse()) {
		if (help.GetIsDefined()) {
			parser.ShowHelp();
		}
		if (verbose.GetIsDefined()) {
			parser.ShowHelpVerbose();
		}
		if (output.GetIsDefined()) {
			std::cout << "Output o value: " << output.GetValue() << std::endl;
		}
		if (number.GetIsDefined()) {
			std::cout << "Input n value: " << number.getValue() << std::endl;
		}
		if (input.GetIsDefined()) {
			std::cout << "Input i value: " << input.GetValue() << std::endl;
		}
	}
	return 0;
}