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
		bool Matches(const std::string& arg) override;

		///��������� ���������� �������� ���������
		std::string getValue();

		///������������ ���������� �������� ���������
		void setValue(std::string value);

		bool ValidValue(const std::string& value) override;

		bool HasValue() const override;

	private:
		std::string _value;
	};
}