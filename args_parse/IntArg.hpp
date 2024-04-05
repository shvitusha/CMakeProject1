#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class IntArg : public Argument {
	public:
		/// @brief ����������� ������������ ������.
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		IntArg(char shortName, const char* longName);

		/// ����������� ��� ������, ����� ��� ��������� �����
		IntArg(const char* longName);

		///������������ ������������ �������� ������
		using Argument::Argument;

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg) override;

		///��������� ��������� �������� ���������
		int getValue();

		///������������ ��������� �������� ���������
		///value ����� ���������
		void SetValue(std::string& value) override;

		/// @brief ����� ��� ��������� ��������� �� ������ ����������, ���������� � ����������.
		///���� ��� ������� ��������� �� ��������� ���������, ����� ���������� nullptr.
		const Validator* GetValidator() const override;

	private:
		///�������� ���������
		int _value;
	};
}