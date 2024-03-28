#pragma once
#include <iostream>

namespace args_parse {
	class Argument {
		public:
			/// @brief  онструктор класса
			///  онструктор дл€ случа€, когда есть как короткое, так и длинное им€
			Argument(char shortName, const char* longName);

			///  онструктор дл€ случа€, когда нет короткого имени
			Argument(const char* longName);

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

			/// @brief  ѕроверка был ли определен аргумент
			bool IsDefined() const;

			/// @brief ћетод дл€ валидатора значени€ и сохранени€ его внутри объекта `Argument`
			virtual bool ValidValue(const std::string& value) {
				return false;
			}

		protected:
			/// ороткое описание аргумента
			char _shortName;
			///ƒлинное описание аргумента
			std::string _longName;
			///ƒополнительное описание аргумента
			std::string _description;
			///‘лаг дл€ проверки определен ли аргумент
			bool _isDefined;
	};
}