#pragma once
#include <sstream>
#include <string>

namespace args_parse {
	///����������� ������� ����� ��� ����������� ��������
	class Validator {
	public:
		virtual bool ValidValue(const std::string& value) const = 0;
	};

	class IntValidator : public Validator {
	public:
		bool ValidValue(const std::string& value) const override {
			/*try {
				std::stoi(value);
				return true;
			}
			catch (const std::exception&) {
				return false;
			}*/
			if (value.empty()) {
				return false;
			}
			// �������� ������ ��� �������������� ������ � int
			std::istringstream iss(value);
			int intValue;
			// ������� �������������� ������ � int
			if (iss >> intValue) {
				// �������� ������� �������������� �������� ����� �����
				char remaining;
				if (iss >> remaining) {
					return false; // �������������� ������� ������������
				}
				// �������� �� ����� �� ������� ��������� int
				if (intValue >= std::numeric_limits<int>::min() && intValue <= std::numeric_limits<int>::max()) {
					return true;
				}
			}
			return false;
		}
	};

	class StringValidator : public Validator {
	public:
		bool ValidValue(const std::string& value) const override {
			//�������� ����� ���� ������
			if (value.empty()) {
				return false;
			}
			// �������� ������ ��� �������������� ������
			std::istringstream iss(value);
			std::string strValue;
			// ������� �������������� ������
			if (iss >> strValue)
				return true;
			return false;
		}
	};
}