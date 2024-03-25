#pragma once
#include "argument.hpp"

namespace args_parse {
	class ArgsParser {
	public:
		/// ������� ����� ����������.
		int argc;
		/// �������� ����������. ������ ���� ����� @a argc.
		const char** argv;
		ArgsParser(int _argc, const char** _argv) {
			argc = _argc;
			argv = _argv;
		}
	void Add(const Argument& arg);
	bool Parse();
	};
}