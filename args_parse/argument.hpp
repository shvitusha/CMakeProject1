#pragma once
#include "Validator.hpp"
#include <iostream>

namespace args_parse {
	class Argument {
	public:
		/// @brief конструктор класса
		/// конструктор для случая, когда есть как короткое, так и длинное имя
		Argument(char shortName, const char* longName, bool isValue);

		/// конструктор для случая, когда нет короткого имени
		Argument(const char* longName, bool isValue);

		/// конструктор по умолчанию
		Argument();

		/// @brief проверка может ли быть у аргумента значение
		[[nodiscard]] bool HasValue() const { return _isValue; }

		///@brief возвращает указатель на объект Validator, используемый для проверки данных.
		///при отсутствии валидатора возвращается nullptr.
		[[nodiscard]] virtual const Validator* GetValidator() const { return nullptr; }

		/// @brief конструктор
		virtual ~Argument() {}

		/// @brief get() для получения значени¤ поля, соответстующего в классе
		std::string GetLongName() const;

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetLongName(const char* longName);

		/// @brief get() дл¤ получения значения поля, соответстующего в классе
		char GetShortName() const;

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetShortName(const char shortName);

		/// @brief get() для получения значения поля, соответстующего в классе
		std::string GetDescription() const;

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetDescription(const std::string& description);

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetIsDefined(const bool isDefined);

		/// @brief get() для получения значения поля, соответстующего в классе
		bool GetIsDefined() const { return _isDefined; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		virtual void SetValue(std::string& value) {}

	protected:
		///короткое описание аргумента
		char _shortName;
		///длинное описание аргумента
		std::string _longName;
		///дополнительное описание аргумента
		std::string _description;
		///флаг на наличие параметра
		bool _isValue;
		///флаг на определение аргумента
		bool _isDefined;
	};
}