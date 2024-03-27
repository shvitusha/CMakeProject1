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
		StringArg(char shortName, const char* longName, std::string value) : Argument(shortName, longName) {}

		/// ����������� ��� ������, ����� ��� ��������� �����
		StringArg(const char* longName, std::string value) : Argument(longName) {}

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