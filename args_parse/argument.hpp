#pragma once
#include "Validator.hpp"
#include <iostream>

namespace args_parse {
	class Argument {
	public:
		/// @brief  онструктор класса
		///  онструктор дл€ случа€, когда есть как короткое, так и длинное им€
		Argument(char shortName, const char* longName, bool isValue);

		///  онструктор дл€ случа€, когда нет короткого имени
		Argument(const char* longName, bool isValue);

		///  онструктор по умолчанию
		Argument();

		/// @brief  ѕроверка может ли быть у аргумента значение
		bool HasValue() const { return _isValue; }

		///@brief ¬озвращает указатель на объект Validator, используемый дл€ проверки данных.
		///ѕри отсутствии валидатора возвращаетс€ nullptr.
		virtual const Validator* GetValidator() const { return nullptr; }

		/// @brief ƒеструктор
		virtual ~Argument() {}

		/// @brief ‘ункци€ дл€ проверки соответстви€ аргумента командной строки.
		/// јргумент передаетс€ в качестве параметра.
		/// ¬озвращает булевое значение
		virtual bool Matches(const std::string& arg) { return false; }

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		std::string GetLongName() const;

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		void SetLongName(const char* longName);

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		char GetShortName() const;

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		void SetShortName(const char shortName);

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		std::string GetDescription() const;

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		void SetDescription(const std::string& description);

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		void SetIsDefined(const bool isDefined);

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		bool GetIsDefined() const { return _isDefined; }

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		virtual void SetValue(const std::string& value) {
			value = NULL;
		}

	protected:
		/// ороткое описание аргумента
		char _shortName;
		///ƒлинное описание аргумента
		std::string _longName;
		///ƒополнительное описание аргумента
		std::string _description;
		///‘лаг на наличие параметра
		bool _isValue;
		///‘лаг на определение аргумента
		bool _isDefined;
	};
}