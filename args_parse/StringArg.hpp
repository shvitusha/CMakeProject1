#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class StringArg : public Argument {
	public:
		/// @brief ����������� ������������ ������.
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		StringArg(char shortName, const char* longName) : Argument(shortName, longName) {}

		/// ����������� ��� ������, ����� ��� ��������� �����
		StringArg(const char* longName) : Argument(longName) {}

		/// �������� ��� �� ��������� ��������
		bool IsDefined() const;

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg);

	private:
		///���� ��� �������� ��������� �� ��������
		bool _isDefined;
		///�������� �������� ���������
		char _shortName;
		///������� �������� ���������
		std::string _longName;
	};
}