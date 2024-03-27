#include "args_parse/ArgsParser.hpp"
#include "args_parse/BoolArg.hpp"
#include "args_parse/StringArg.hpp"
#include "args_parse/IntArg.hpp"

int main(int argc, const char** argv) {
    args_parse::ArgsParser parser(argc, argv);

    args_parse::BoolArg help('h', "help");
    help.SetDescription("������� �������� ���� ����������� ���������� ��������� ������");
    args_parse::BoolArg verbose('v', "verbose");
    verbose.SetDescription("����������� ��������� ������� ��������");
    args_parse::StringArg input('i', "input");
    input.SetDescription("�����");
    args_parse::StringArg output('o', "output");
    output.SetDescription("����");
    args_parse::IntArg number('n', "number");
    number.SetDescription("����������� ��������� �������� ��������");

    parser.Add(help);
    parser.Add(verbose);
    parser.Add(input);
    parser.Add(output);
    parser.Add(number);

    if (parser.Parse()) {
        if (help.IsDefined()) {
            parser.ShowHelp();
            return 0;
        }
    }
    return 0;
}