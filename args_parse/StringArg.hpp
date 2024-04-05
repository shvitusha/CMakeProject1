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
		StringArg(char shortName, const char* longName);

		/// ����������� ��� ������, ����� ��� ��������� �����
		StringArg(const char* longName);

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg) override;

		///��������� ���������� �������� ���������
		std::string GetValue();

		///������������ ���������� �������� ���������
		void SetValue(std::string& value) override;

		/// @brief ����� ��� ��������� ��������� �� ������ ����������, ���������� � ����������.
		///���� ��� ������� ��������� �� ��������� ���������, ����� ���������� nullptr.
		const Validator* GetValidator() const override;

	private:
		std::string _value;
	};
}