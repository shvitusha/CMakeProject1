#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class IntArg : public Argument {
	public:
		/// @brief ����������� ������������ ������.
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		IntArg(char shortName, const char* longName, int value);

		/// ����������� ��� ������, ����� ��� ��������� �����
		IntArg(const char* longName, int value);

		///������������ ������������ �������� ������
		using Argument::Argument;

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg);

		///��������� ��������� �������� ���������
		int getValue() const;

		///������������ ��������� �������� ���������
		void setValue(int value);

	private:
		///�������� ���������
		int _value;
	};
}