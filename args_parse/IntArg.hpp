#include "argument.hpp"
#include <iostream>

namespace args_parse {
	class IntArg : public Argument {
	public:
		/// @brief ����������� ������������ ������.
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		IntArg(char shortName, const char* longName) : Argument(shortName, longName) {}

		/// ����������� ��� ������, ����� ��� ��������� �����
		IntArg(const char* longName) : Argument(longName) {}

		/// �������� ��� �� ��������� ��������
		bool IsDefined() const;

		/// �������� ������������ ����������� ��������� �����
		bool Matches(const std::string& arg);

		///��������� ��������� �������� ����
		int getValue() const;

	private:
		///���� ��� �������� ��������� �� ��������
		bool _isDefined;
		///�������� �������� ���������
		char _shortName;
		///������� �������� ���������
		std::string _longName;
		///�������� ���������
		int _value;
	};
}