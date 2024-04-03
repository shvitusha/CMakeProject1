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

	class ArgsParser {
	public:
		/// @brief ����������� ������.
		/// ����������� ��������� ���������� ���������� � �� ��������
		ArgsParser(int argc, const char** argv);

		/// @brief ����� ���������� ��������� ��������� ������ � ������
		void Add(std::unique_ptr<Argument> arg);

		/// @brief ����� �������� ���������� ��������� ������.
		/// �� �������� �� ������� ��������� ��������� ������ � ���������, ��� �� ������ �������� � �������
		bool Parse();

		void ParseLongArgument(const std::string& argStr, std::string& argName, std::string& argValue);

		void ParseShortArgument(const std::string& argStr, std::string& argName, std::string& argValue);

		void ProcessArgument(const std::string& argStr, const std::string& argName, std::string& argValue, int& i) const;

		std::unique_ptr<Argument> FindArgument(const std::string& argName) const;

		/// @brief ����������
		~ArgsParser();

		/// @brief ����� ��� ������ ������� �� ������������� ���������.
		/// ������� �������� ���� ����������� ���������� ��������� ������
		void ShowHelp();

		/// @brief ����� ��� ������ �������� �����, ���� ��� ����
		std::unique_ptr<Argument> FindLongNameArg(std::string item) const;

		/// @brief ����� ������ ��������� �����, ���� ��� ����
		std::unique_ptr<Argument> FindShortNameArg(std::string item) const;

		/// @brief �����, ������� ��������� �������� �� ������ ����������.
		/// ���������� ����� �������� ��� �����������
		OperatorType IsOperator(std::string operatString);

	private:
		/// ������� ����� ����������.
		int _argc;
		/// �������� ����������. ������ ���� ����� @a argc.
		const char** _argv;
		/// ������ ��� �������� �������� ���������� ��������� ������
		std::vector<std::unique_ptr<Argument>> _args;
	};
}