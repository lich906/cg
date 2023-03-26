#include "pch.h"

#include "graphics/CurrentProgram.h"

void CurrentProgram::Set(const Program& program)
{
	m_program = program;
}

void CurrentProgram::Unset()
{
	m_program.reset();
}

Program& CurrentProgram::Get()
{
	if (m_program)
	{
		return *m_program;
	}

	throw std::logic_error("Current program was not set.");
}
