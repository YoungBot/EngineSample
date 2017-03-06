#pragma once
#if !defined(__COMMAND__)
#define __COMMAND__

#include <list>
#include <string>

class CCommand
{
public:
	std::string name;
	std::list<std::string> arguments;

	bool GetString(int idx, std::string &out) const
	{
		if ((idx < (int)arguments.size()) && (idx >= 0)) {
			auto iter = arguments.begin();
			while (idx > 0) {
				--idx;
				++iter;
			}

			out = *iter;
			return true;
		}
		else {
			return false;
		}
	}

	bool GetInt(int idx, int *out) const
	{
		std::string s;
		if (GetString(idx, s)) {
			*out = atoi(s.c_str());
			return true;
		}

		return false;
	}

	CCommand(char *n);
};

typedef bool(*command_cb)(CCommand const*);
typedef std::list<CCommand*> CCommandList;


CCommandList ParseCommands(std::string command_line);
void FreeCommands(CCommandList commandList);


void RegisterCommand(std::string name, command_cb cb);

bool ProcessCommands(CCommandList commands);


#endif