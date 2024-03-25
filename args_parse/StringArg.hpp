#pragma once
#include "argument.hpp"

namespace args_parse {

	class StringArg : public Argument {
	public:
		StringArg(const std::string& shortName, const std::string& longName);

		std::string GetValue() const;

		bool Matches(const std::string& arg) const override;

	private: bool _isDefined;
	};
}