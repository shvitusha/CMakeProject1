#pragma once
#include "ArgsParser.hpp"
#include <string>
#include <chrono>
#include <sstream>

namespace args_parse {
	class SharedValidator;
	template<typename T>
	class Validator;

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
		bool HasValue() const { return _isValue; }

		/// @brief get() для получения значени¤ поля, соответстующего в классе
		std::string GetLongName() const { return _longName; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetLongName(const char* longName) { _longName = longName; }

		/// @brief get() для получения значения поля, соответстующего в классе
		char GetShortName() const { return _shortName; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetShortName(const char shortName) { _shortName = shortName; }

		/// @brief get() для получения значения поля, соответстующего в классе
		std::string GetDescription() const { return _description; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetDescription(const std::string& description) { _description = description; }

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetIsDefined(const bool isDefined) { _isDefined = isDefined; }

		/// @brief get() для получения значения поля, соответстующего в классе
		bool GetIsDefined() const { return _isDefined; }

		virtual const SharedValidator* GetValidator() const = 0;

		virtual void SetValue(const std::string& value) = 0;

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
		///значение аргумента
	};

	template<typename T>
	class Argument : public ArgumentBase {
	public:
		using ArgumentBase::ArgumentBase;

		///@brief возвращает указатель на объект Validator, используемый для проверки данных.
		///при отсутствии валидатора возвращается nullptr.
		const SharedValidator* GetValidator() const override { 
			static Validator<T> validator;
			return &validator;
		}

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetValue(const std::string& value) override {
			std::istringstream iss(value);
			iss >> _value;
		}

		/// @brief get() для получения значения поля, соответстующего в классе
		T GetValue() const { return _value; }

	protected:
		///значение аргумента
		T _value;
	};
	/*
	template<>
	class Argument<std::chrono::milliseconds> : public ArgumentBase {
	private:
		///значение аргумента
		std::chrono::milliseconds _value;

	public:
		///@brief возвращает указатель на объект Validator, используемый для проверки данных.
		///при отсутствии валидатора возвращается nullptr.
		const SharedValidator* GetValidator() const override {
			static Validator<std::chrono::milliseconds> validator;
			return &validator;
		}

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetValue(const std::string& value) override {
			// Здесь вы должны преобразовать строковое значение в ваш тип IpAddress
			// и присвоить его полю _value.
			// Например:
			//_value = ParseIpAddress(value);
		}

		/// @brief get() для получения значения поля, соответстующего в классе
		std::chrono::milliseconds GetValue() const { return _value; }
	};*/
}