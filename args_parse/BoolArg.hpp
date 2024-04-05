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

		const Validator* GetValidator() const { return nullptr; }

		//	///��������� �������� �������� ���������
		//	bool getValue();

		///������������ �������� �������� ���������
		void SetValue(std::string& value) override;

		//	bool ValidValue(const std::string& value) override;

		private:
			std::string _value;
	};
}