#include <args_parse/BoolArg.hpp>
#include <args_parse/StringArg.hpp>
#include <args_parse/IntArg.hpp>
#include <args_parse/ArgsParser.hpp>

int main(int argc, const char** argv) 
{
    args_parse::ArgsParser parser(argc, argv);

    args_parse::BoolArg help('h', "help");
    help.SetDescription("Outputs a description of all added command line arguments");
    args_parse::BoolArg verbose('v', "verbose");
    verbose.SetDescription("Assigns a boolean value to the argument");
    args_parse::StringArg input('i', "input");
    input.SetDescription("Input");
    args_parse::StringArg output('o', "output");
    output.SetDescription("Output");
    args_parse::IntArg number('n', "number");
    number.SetDescription("Assigns a numeric value to an argument");

    parser.Add(help);
    parser.Add(verbose);
    parser.Add(input);
    parser.Add(output);
    parser.Add(number);

    parser.ShowHelp();

    if (parser.Parse()) {
        if (help.IsDefined()) {
            parser.ShowHelp();
            return 0;
        }
        if (!output.getValue().empty()) {
            std::cout << "Output value: " << output.getValue() << std::endl;
        }
        if (number.getValue() != 0) {
            std::cout << "Input value: " << number.getValue() << std::endl;
        }
    }
    return 0;
}