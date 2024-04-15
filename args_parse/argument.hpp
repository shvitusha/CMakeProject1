#pragma once
#include "ArgsParser.hpp"
#include <string>
#include <chrono>
#include <sstream>
#include <optional>

namespace args_parse {
	class SharedValidator;
	template<typename T>
	class Validator;
	template<>
	class Validator<std::chrono::milliseconds>;

	class ArgumentBase {
	public:
		/// @brief конструктор класса
		/// конструктор для случая, когда есть как короткое, так и длинное имя
		ArgumentBase(char shortName, const char* longName, bool isValue) :
			_shortName(shortName), _longName(longName), _isValue(isValue), _description(""), _isDefined(false) {}

		/// конструктор для случая, когда нет короткого имени
		ArgumentBase(const char* longName, bool isValue) : ArgumentBase('\0', longName, isValue) {}

		/// конструктор по умолчанию
		ArgumentBase() : ArgumentBase('\0', "", false) {}

		/// @brief проверка может ли быть у аргумента значение
		[[nodiscard]] bool HasValue() const { return _isValue; }

		/// @brief get() для получения значени¤ поля, соответстующего в классе
		[[nodiscard]] std::string GetLongName() const { return _longName; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetLongName(const char* longName) { _longName = longName; }

		/// @brief get() для получения значения поля, соответстующего в классе
		[[nodiscard]] char GetShortName() const { return _shortName; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetShortName(const char shortName) { _shortName = shortName; }

		/// @brief get() для получения значения поля, соответстующего в классе
		[[nodiscard]] std::string GetDescription() const { return _description; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetDescription(const std::string& description) { _description = description; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetIsDefined(const bool isDefined) { _isDefined = isDefined; }

		/// @brief get() для получения значения поля, соответстующего в классе
		[[nodiscard]] bool GetIsDefined() const { return _isDefined; }

		//[[nodiscard]] virtual const SharedValidator* GetValidator() const = 0;
		[[nodiscard]] virtual bool IsValidatorExist() const = 0;

		//virtual void SetValue(const std::string& value) = 0;

	private:
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

	template<typename T>
	class Argument : public ArgumentBase {
	public:
		using ArgumentBase::ArgumentBase;

		/// @brief конструктор класса
		/// конструктор для случая, когда есть как короткое, так и длинное имя
		Argument::Argument(char shortName, const char* longName, bool isValue, Validator<T>* validator) :
			ArgumentBase(shortName, longName, isValue), _validator(validator) {}

		/// конструктор для случая, когда нет короткого имени
		Argument::Argument(const char* longName, bool isValue, Validator<T>* validator) : 
			ArgumentBase('\0', longName, isValue), _validator(validator) {}

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetValue(const T& value) {
			_value = value;
		}
		bool IsValidatorExist() const override
		{
			if (_validator == nullptr) return false;
			return true;
		}
		/// @brief get() для получения значения поля, соответстующего в классе
		[[nodiscard]] T GetValue() const { return _value; }

	protected:
		///значение аргумента
		std::optional<T> _value;
		/// валидатор
		Validator<T>* _validator;
	};

	template<>
	class Argument<std::chrono::milliseconds> : public ArgumentBase {
	private:
		///значение аргумента
		std::chrono::milliseconds _value;
		/// валидатор
		Validator<std::chrono::milliseconds>* _validator;

	public:
		/// @brief конструктор класса
		/// конструктор для случая, когда есть как короткое, так и длинное имя
		Argument::Argument(char shortName, const char* longName, bool isValue, Validator<std::chrono::milliseconds>* validator = nullptr) :
			ArgumentBase(shortName, longName, isValue), _validator(validator) {}

		/// конструктор для случая, когда нет короткого имени
		Argument::Argument(const char* longName, bool isValue, Validator<std::chrono::milliseconds>* validator = nullptr) :
			ArgumentBase('\0', longName, isValue), _validator(validator) {}

		using ArgumentBase::ArgumentBase;
		
		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetValue(const std::chrono::milliseconds& value) {
			_value = value;
		}

		bool IsValidatorExist() const override
		{
			if (_validator == nullptr) return false;
			return true;
		}

		/// @brief get() для получения значения поля, соответстующего в классе
		[[nodiscard]] std::chrono::milliseconds GetValue() const { return _value; }
	};
}