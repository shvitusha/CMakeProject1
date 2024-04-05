#pragma once
#include "argument.hpp"
#include <vector>

namespace args_parse {
	/// @brief ������������ ����� ��������� (�������, ��������, ��������������)
	enum class OperatorType {
		Long,
		Short,
		Nope
	};

	struct BaseParametrs {
		const std::string& argStr;
		std::string& argName;
		std::string& argValue;
	};

	class ArgsParser {
	public:
		/// @brief ����������� ������.
		/// ����������� ��������� ���������� ���������� � �� ��������
		ArgsParser(int argc, const char** argv);

		/// @brief ����� ���������� ��������� ��������� ������ � ������
		void Add(Argument* arg);

		/// @brief ����� �������� ���������� ��������� ������.
		/// �� �������� �� ������� ��������� ��������� ������ � ���������, ��� �� ������ �������� � �������
		bool Parse();

		/// @brief ����� ��� ������� ������� ���������� ��������� ������.
		/// ��������� ��� � �������� ��������� ��� ���������� ���������.
		void ParseLongArgument(BaseParametrs parametrs);

		/// @brief ����� ��� ������� �������� ���������� ��������� ������.
		/// ��������� ��� � �������� ��������� ��� ���������� ���������.
		void ParseShortArgument(BaseParametrs parametrs) const;

		/// @brief ����� ��� ��������� ������ ��������� ��������� ������.
		/// ����� ��������� ��� �������, ������� � ���� ��������, ���� ��, �� ��� ��������.
		void ProcessArgument(BaseParametrs parametrs, int& i) const;

		void ValidationValue(const Validator* validator, BaseParametrs& parametrs, Argument* arg, int& i) const;

		/// @brief ����� ������ ���������.
		/// � ����������� �� ��������� �������� ������ ������ ��������� ��� �������� �����.
		Argument* FindArgument(const std::string& argName) const;

		/// @brief ����������
		~ArgsParser();

		/// @brief ����� ��� ������ ������� �� ������������� ���������.
		/// ������� �������� ���� ����������� ���������� ��������� ������
		void ShowHelp() const;

		/// @brief ����� ��� ������ �������������� ������� �� ������������� ���������.
		/// ������� �������� ���� ����������� ����������, ����������� ��������, � ��� ������������.
		void ShowHelpVerbose() const;

		/// @brief ����� ��� ������ �������� �����, ���� ��� ����
		Argument* FindLongNameArg(std::string item) const;

		/// @brief ����� ������ ��������� �����, ���� ��� ����
		Argument* FindShortNameArg(std::string item) const;

		/// @brief �����, ������� ��������� �������� �� ������ ����������.
		/// ���������� ����� �������� ��� �����������
		OperatorType IsOperator(std::string operatString);

	private:
		/// ������� ����� ����������.
		int _argc;
		/// �������� ����������. ������ ���� ����� @a argc.
		const char** _argv;
		/// ������ ��� �������� �������� ���������� ��������� ������
		std::vector<Argument*> _args;
	};
}