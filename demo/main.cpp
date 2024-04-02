#include <args_parse/BoolArg.hpp>
#include <args_parse/StringArg.hpp>
#include <args_parse/IntArg.hpp>
#include <args_parse/ArgsParser.hpp>

int main(int argc, const char** argv)
{
	args_parse::ArgsParser parser(argc, argv);

	std::unique_ptr<args_parse::Argument> help(new args_parse::BoolArg('h', "help"));
	help->SetDescription("Outputs a description of all added command line arguments");
	std::unique_ptr<args_parse::Argument> verbose(new args_parse::BoolArg('v', "verbose"));
	verbose->SetDescription("Assigns a boolean value to the argument");
	std::unique_ptr<args_parse::Argument> input(new args_parse::StringArg('i', "input"));
	input->SetDescription("Input");
	std::unique_ptr<args_parse::Argument> output(new args_parse::StringArg('o', "output"));
	output->SetDescription("Output");
	std::unique_ptr<args_parse::Argument> number(new args_parse::IntArg('n', "number"));
	number->SetDescription("Assigns a numeric value to an argument");

	parser.Add(std::move(help));
	parser.Add(std::move(verbose));
	parser.Add(std::move(input));
	parser.Add(std::move(output));
	parser.Add(std::move(number));

	parser.ShowHelp();

	if (parser.Parse()) {
		if (help->HasValue()) {
			parser.ShowHelp();
			return 0;
		}
	}
	return 0;
}