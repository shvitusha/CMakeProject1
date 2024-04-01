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
		bool Matches(const std::string& arg) override;

		///��������� ��������� �������� ���������
		int getValue();

		///������������ ��������� �������� ���������
		void setValue(int value);

		bool ValidValue(const std::string& value) override;
		
		bool HasValue() const override;

	private:
		///�������� ���������
		int _value;
	};
}