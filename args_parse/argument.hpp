#pragma once

namespace args_parse {
	class Argument {
	public:
		/// @brief ����������� ������
		/// ����������� ��������� �������� � ������� ���
		Argument(
			const std::string& shortName, const std::string& longName) {
			_shortName = shortName;
			_longName = longName;
			_description = "";
		}
		/// @brief ����������
		virtual ~Argument(){}
		/// @brief ������� ��� �������� ������������ ��������� ��������� ������ 
		/// �������� ���������� � �������� ��������� � ����� ������-���� �� ������
		/// ���������� ������� ��������
		virtual bool Matches(const std::string& arg) const {
			return arg == _shortName || arg = _longName;
		}

		std::string GetDescription() const { return _description; }
		std::string SetDescription(const std::string& description) const { _description = description; }

	protected:
		///�������� �������� ���������
		std::string _shortName;
		///������� �������� ���������
		std::string _longName;
		///�������������� �������� ���������
		std::string _description;
	};
}