#include <args_parse/argument.hpp>
#include <args_parse/ArgsParser.hpp>
#include <iostream>

int main(int argc, const char** argv)
{
	args_parse::ArgsParser parser(argc, argv);

	args_parse::Argument<bool> help('h', "help", false);
	help.SetDescription("Outputs a description of all added command line arguments");
	args_parse::Argument<bool> verbose('v', "verbose", false);
	verbose.SetDescription("Outputs a verbose of all added command line arguments");
	args_parse::Argument<std::string> input('i', "input", true);
	input.SetDescription("Input (filename)");
	args_parse::Argument<std::string> output('o', "output", true);
	output.SetDescription("Output (filename)");
	args_parse::Argument<int> number('n', "number", true);

	args_parse::Argument<float> parametr('p', "parametr", true);
	parametr.SetDescription("Definition of constant/precision/parameter with floating sign");
	args_parse::Argument<unsigned int> thread_pool('t', "thread-pool", true);
	thread_pool.SetDescription("Sets the number of threads (number)");
	args_parse::Argument<unsigned int> debug_sleep('d', "debug-sleep", true);
	debug_sleep.SetDescription("Defines a user input of the argument type (ms/s)");

	parser.Add(&help);
	parser.Add(&verbose);
	parser.Add(&input);
	parser.Add(&output);
	parser.Add(&number);
	parser.Add(&parametr);
	parser.Add(&thread_pool);
	parser.Add(&debug_sleep);

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
			std::cout << "Input n value: " << number.GetValue() << std::endl;
		}
		if (input.GetIsDefined()) {
			std::cout << "Input i value: " << input.GetValue() << std::endl;
		}
		if (thread_pool.GetIsDefined()) {
			std::cout << "Input t value: " << thread_pool.GetValue() << std::endl;
		}
		if (debug_sleep.GetIsDefined()) {
			//logic input type argument
			std::cout << "Input p value (float): " << debug_sleep.GetValue() << std::endl;
		}
		if (parametr.GetIsDefined()) {
			std::cout << "Input p value (float): " << parametr.GetValue() << std::endl;
		}
	}
	return 0;
}