#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class BoolArg : public Argument {
	public:
		///������������ ������������ �������� ������
		using Argument::Argument;

		/// @brief ����������� ������������ ������.
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		BoolArg(char shortName, const char* longName);

		/// ����������� ��� ������, ����� ��� ��������� �����
		BoolArg(const char* longName);

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg) override;

		const Validator* GetValidator() const override;
		//	///��������� �������� �������� ���������
		//	bool getValue();

		//	///������������ �������� �������� ���������
		//	void setValue(bool value);

		//	bool ValidValue(const std::string& value) override;

		//private:
		//	bool _value;
	};
}