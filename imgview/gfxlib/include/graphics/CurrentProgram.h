#pragma once

#include "pch.h"

#include "Program.h"

class CurrentProgram
{
public:
	static void Set(const Program& program);
	static void Unset();
	static Program& Get();

private:
	CurrentProgram() = delete;

	static inline std::optional<Program> m_program;
};
