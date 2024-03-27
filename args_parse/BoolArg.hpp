#pragma once
#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class BoolArg : public Argument {
	public:
		///������������ ������������ �������� ������
		using Argument::Argument;

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg);

		///��������� �������� �������� ���������
		bool getValue() const;

		///������������ �������� �������� ���������
		void setValue(bool value);

	private:
		bool _value;
	};
}