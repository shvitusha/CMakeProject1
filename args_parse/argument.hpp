#pragma once
#include "Validator.hpp"
#include <iostream>

namespace args_parse {
	class Argument {
	public:
		/// @brief ����������� ������
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		Argument(char shortName, const char* longName, bool isValue);

		/// ����������� ��� ������, ����� ��� ��������� �����
		Argument(const char* longName, bool isValue);

		/// ����������� �� ���������
		Argument();

		/// @brief  �������� ����� �� ���� � ��������� ��������
		bool HasValue() const { return _isValue; }

		virtual const Validator* GetValidator() const { return nullptr; }

		/// @brief ����������
		virtual ~Argument() {}

		/// @brief ������� ��� �������� ������������ ��������� ��������� ������.
		/// �������� ���������� � �������� ���������.
		/// ���������� ������� ��������
		virtual bool Matches(const std::string& arg) { return false; }

		/// @brief get() ��� ��������� �������� ����, ��������������� � ������
		std::string GetLongName() const;

		/// @brief ����� set() ��� ������������ �������� ����, ��������������� � ������
		void SetLongName(const char* longName);

		/// @brief get() ��� ��������� �������� ����, ��������������� � ������
		char GetShortName() const;

		/// @brief ����� set() ��� ������������ �������� ����, ��������������� � ������
		void SetShortName(const char shortName);

		/// @brief get() ��� ��������� �������� ����, ��������������� � ������
		std::string GetDescription() const;

		/// @brief ����� set() ��� ������������ �������� ����, ��������������� � ������
		void SetDescription(const std::string& description);

	protected:
		///�������� �������� ���������
		char _shortName;
		///������� �������� ���������
		std::string _longName;
		///�������������� �������� ���������
		std::string _description;
		///���� �� ������� ���������
		bool _isValue;
	};
}