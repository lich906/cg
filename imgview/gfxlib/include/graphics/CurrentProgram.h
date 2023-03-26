#pragma once

#include "pch.h"

#include "Program.h"

class CurrentProgram
{
public:
	/*
		Pass ownership of shader, since we will have global access to it.
	*/
	static void Set(const Program& shader);

	static Program& Get();

private:
	CurrentProgram() = delete;

	static inline std::optional<Program> m_program;
};
