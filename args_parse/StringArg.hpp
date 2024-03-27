#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class StringArg : public Argument {
	public:
		///������������ ������������ �������� ������
		using Argument::Argument;

		/// @brief ����������� ������������ ������.
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		StringArg(char shortName, const char* longName, std::string value);

		/// ����������� ��� ������, ����� ��� ��������� �����
		StringArg(const char* longName, std::string value);

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg);

		///��������� ���������� �������� ���������
		std::string getValue() const;

		///������������ ���������� �������� ���������
		void setValue(std::string value);

	private:
		std::string _value;
	};
}