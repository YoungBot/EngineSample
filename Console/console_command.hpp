#pragma once

#ifndef _CONSOLE_COMMAND_HPP_
#define _CONSOLE_COMMAND_HPP_

#include <vector>
#include <string.h>
#include "Engine/Renderer/Fonts.hpp"
// all arguments


class ConsoleArguments
{
public:
	inline ConsoleArguments(char const** args) :m_args(args){}
	char const **m_args;
};


class ConsoleCommand;
extern std::vector<ConsoleCommand*>* s_all_commands;

typedef void(*console_command_t)(ConsoleArguments *args);
static std::vector<ConsoleCommand*>* GetAllCommands()
{
	if (s_all_commands == nullptr)
	{
		s_all_commands = new std::vector < ConsoleCommand* > ;
	}
	return s_all_commands;
}
class ConsoleCommand
{
public:
	inline ConsoleCommand(char const *name, console_command_t command)
	{		
		m_name = name;
		m_command = command;
		GetAllCommands()->push_back(this);
	}

	inline void run_command(ConsoleArguments *args)
	{
		m_command(args);
	}

	inline static ConsoleCommand* Find(char const *name)
	{
		for (unsigned int i = 0; i < s_all_commands->size(); i ++)
		{
			char* cmp = (char*)(*s_all_commands)[i]->m_name;
			if (!strcmp(cmp, name))
			{
				return (*s_all_commands)[i];
			}			
		}
		return nullptr;
	}

	char const *m_name;
	console_command_t m_command;

};


void RunConsoleCommand(char const *name, char const **args);
bool RunCommand(char const *name, ConsoleArguments *args);
void RunConsoleFromLine(char const *line);

#define CONSOLE_COMMAND(name) static void ConsoleCommand_##name##( ConsoleArguments *arg ); \
								static ConsoleCommand command_##name##(#name, ConsoleCommand_##name##); \
							 static void ConsoleCommand_##name##( ConsoleArguments *args )

#define COMMAND_REGISTER(name) static ConsoleCommand ConsoleCommand_##name##(#name, name)

#endif