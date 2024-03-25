#pragma once

namespace args_parse {
	class Argument {
	public:
		/// @brief Конструктор класса
		/// Конструктор принимает короткое и длинное имя
		Argument(
			const std::string& shortName, const std::string& longName) {
			_shortName = shortName;
			_longName = longName;
			_description = "";
		}
		/// @brief Деструктор
		virtual ~Argument(){}
		/// @brief Функция для проверки соответствия аргумента командной строки 
		/// Аргумент передается в качестве параметра и равен какому-либо из флагов
		/// Возвращает булевое значение
		virtual bool Matches(const std::string& arg) const {
			return arg == _shortName || arg = _longName;
		}

		std::string GetDescription() const { return _description; }
		std::string SetDescription(const std::string& description) const { _description = description; }

	protected:
		///Короткое описание аргумента
		std::string _shortName;
		///Длинное описание аргумента
		std::string _longName;
		///Дополнительное описание аргумента
		std::string _description;
	};
}