//==========================================================
//console_command.cpp
//==========================================================
#include "console_command.hpp"
#include "Engine/Utility/Utility.hpp"
std::vector<ConsoleCommand*>* s_all_commands = nullptr;



void RunConsoleCommand(char const *name, char const **args)
{
	ConsoleArguments arg_obj(args);
	RunCommand(name, &arg_obj);
	//Utility::FireEvent(name);
}

char const** split(char const *line)
{
	std::vector<std::string> resultString;
	std::string tokenPtr = (char*)line;
	std::string res;
	do
	{
		res = Fonts::CutString(tokenPtr, ' ');
		resultString.push_back(res.c_str());
	} while (strcmp(tokenPtr.c_str(), ""));
	char** result = new char*[resultString.size()];
	for (unsigned int i = 0 ; i < resultString.size() ; i++)
	{
		result[i] = new char[resultString[i].size()+1];// (char*)resultString[i].c_str();
		for (unsigned int j = 0; j < resultString[i].size(); j++)
		{
			result[i][j] = resultString[i][j];
		}
		result[i][resultString[i].size()] = '\0';
	}
	return (const char**)result;
}

bool RunCommand(char const *name, ConsoleArguments *args) 
{
   ConsoleCommand* command = ConsoleCommand::Find(name);
   if (nullptr == command) {
      return false;
   }
   command->run_command(args);
   return true;
}

void RunConsoleFromLine( char const *line ) 
{
   char const **args = split(line);
   RunConsoleCommand( args[0], args + 1 );
}

