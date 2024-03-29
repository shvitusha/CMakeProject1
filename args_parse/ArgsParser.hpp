#pragma once
#include "argument.hpp"
#include <vector>

namespace args_parse {
	class ArgsParser {
	public:
		/// @brief ����������� ������.
		/// ����������� ��������� ���������� ���������� � �� ��������
		ArgsParser(int argc, const char** argv);

		/// @brief ����� ���������� ��������� ��������� ������ � ������
		void Add(const Argument& arg);

		/// @brief ����� �������� ���������� ��������� ������.
		/// �� �������� �� ������� ��������� ��������� ������ � ���������, ��� �� ������ �������� � �������
		bool Parse();

		/// @brief ����������
		~ArgsParser();

		/// @brief ����� ��� ������ ������� �� ������������� ���������.
		/// ������� �������� ���� ����������� ���������� ��������� ������
		void ShowHelp();

		/// @brief ����� ��� ������ �������� �����, ���� ��� ����
		Argument FindLongNameArg(std::string item, std::string& value) const;

		/// @brief ����� ������ ��������� �����, ���� ��� ����
		Argument FindShortNameArg(std::string item, std::string& value) const;

		/// @brief �����, ������� ��������� �������� �� ������ ����������.
		/// ���������� ����� �������� ��� �����������
		OperatorType IsOperator(std::string operatString);

	private:
		/// ������� ����� ����������.
		int _argc;
		/// �������� ����������. ������ ���� ����� @a argc.
		const char** _argv;
		/// ������ ��� �������� �������� ���������� ��������� ������
		std::vector<Argument> _args;
	};

	/// @brief ������������ ����� ��������� (�������, ��������, ��������������)
	enum class OperatorType {
		Long,
		Short,
		Nope
	};
}