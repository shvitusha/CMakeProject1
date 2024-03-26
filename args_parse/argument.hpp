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
		virtual bool Matches(const std::string& arg) const;

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		std::string GetLongName() const;

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		std::string SetLongName(const char* longName) const;

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		std::string GetShortName() const;

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		std::string SetShortName(const char shortName) const;

		/// @brief get() дл€ получени€ значени€ пол€, соответстующего в классе
		std::string GetDescription() const;

		/// @brief ћетод set() дл€ присваивани€ значени€ полю, соответстующему в классе
		std::string SetDescription(const std::string& description) const;

	protected:
		/// ороткое описание аргумента
		char _shortName;
		///ƒлинное описание аргумента
		std::string _longName;
		///ƒополнительное описание аргумента
		std::string _description;
	};
}