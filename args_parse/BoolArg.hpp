#pragma once
#include "argument.hpp"

namespace args_parse {

	class BoolArg : public Argument {
	public:
		BoolArg(const std::string& shortName, const std::string& longName);

		bool IsDefined() const;

		bool Matches(const std::string& arg) const override;

	private: bool _isDefined;
	};
}