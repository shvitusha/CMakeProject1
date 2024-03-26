#include <iostream>

namespace args_parse {
	class Argument {
	public:
		/// @brief ����������� ������
		/// ����������� ��� ������, ����� ���� ��� ��������, ��� � ������� ���
		Argument(char shortName, const char* longName);

		/// ����������� ��� ������, ����� ��� ��������� �����
		Argument(const char* longName);

		/// @brief ����������
		virtual ~Argument() {}

		/// @brief ������� ��� �������� ������������ ��������� ��������� ������. 
		/// �������� ���������� � �������� ���������.
		/// ���������� ������� ��������
		virtual bool Matches(const std::string& arg) const;

		/// @brief get() ��� ��������� �������� ����, ��������������� � ������
		std::string GetLongName() const;

		/// @brief ����� set() ��� ������������ �������� ����, ��������������� � ������
		std::string SetLongName(const char* longName) const;

		/// @brief get() ��� ��������� �������� ����, ��������������� � ������
		std::string GetShortName() const;

		/// @brief ����� set() ��� ������������ �������� ����, ��������������� � ������
		std::string SetShortName(const char shortName) const;

		/// @brief get() ��� ��������� �������� ����, ��������������� � ������
		std::string GetDescription() const;

		/// @brief ����� set() ��� ������������ �������� ����, ��������������� � ������
		std::string SetDescription(const std::string& description) const;

	protected:
		///�������� �������� ���������
		char _shortName;
		///������� �������� ���������
		std::string _longName;
		///�������������� �������� ���������
		std::string _description;
	};
}