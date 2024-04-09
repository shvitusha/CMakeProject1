#pragma once
#include "ArgsParser.hpp"
#include <string>

namespace args_parse {
	class Validator;
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
		bool HasValue() const { return _isValue; }

		///@brief возвращает указатель на объект Validator, используемый для проверки данных.
		///при отсутствии валидатора возвращается nullptr.
		virtual const Validator* GetValidator() const { return nullptr; }

		/// @brief конструктор
		virtual ~Argument() {}

		/// @brief get() для получения значени¤ поля, соответстующего в классе
		std::string GetLongName() const;

		/// @brief метод set() для присваивания значения полю, соответстующему в классе
		void SetLongName(const char* longName);

		/// @brief get() для получения значения поля, соответстующего в классе
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
		virtual void SetValue(std::string& value) {
		}

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

#pragma region StringArg
	class StringArg : public Argument {
		public:
			///наследование конструктора базового класса
			using Argument::Argument;
			
			///получение строкового значения аргумента
			std::string GetValue();

			///присваивание строкового значения аргументу
			void SetValue(std::string& value) override;

			/// @brief метод для получения указателя на объект валидатора, связанного с аргументом.
			///если для данного аргумента не определен валидатор, метод возвращает nullptr.
			const Validator* GetValidator() const override;

		private:
			std::string _value;
		};
#pragma endregion

#pragma region IntArg

	class IntArg : public Argument {
	public:
		///наследование конструктора базового класса
		using Argument::Argument;

		///получение числового значени¤ аргумента
		int getValue();

		///присваивание числового значения аргументу
		///value после валидации
		void SetValue(std::string& value) override;

		/// @brief метод для получения указателя на объект валидатора, связанного с аргументом.
		///если для данного аргумента не определен валидатор, метод возвращает nullptr.
		const Validator* GetValidator() const override;

	private:
		/// Значение аргумента
		int _value;
	};

#pragma endregion

#pragma region BoolArg
	class BoolArg : public Argument {
		public:
			///наследование конструктора базового класса
			using Argument::Argument;

			const Validator* GetValidator() const { return nullptr; }

			///Присваивание булевого значения аргументу
			void SetValue(std::string& value) override { _value = value; };

		private:
			std::string _value;
	};
#pragma endregion
}