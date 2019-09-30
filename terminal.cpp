#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#define MSGSIZE 256

int main()
{
	std::string userSelection = "";
	std::string commandName = "";
	std::cout << "Starting terminal program. Type helpME for nonstandard command list.\n"
			  << "Enter all one token commands with a trailing space.\n";
	while (true) {
		std::cout << ">";
		std::getline(std::cin, userSelection);
		commandName = userSelection.substr(0, userSelection.find(" "));

		if (commandName == "exit" || commandName == "Exit") {//Ends the terminal program.
			std::cout << "Terminal closing now.\n";
			return 0;

		}
		else if (commandName == "pwd") {//Prints the current working directory.
			std::cout << "PWD\n";
		}
		else if (commandName == "helpME") {//Print the command list of nonstandard commands.
			std::cout << "Command List:\n"
					  << "1: \'history\' - Prints the list of past commands.\n";
		}
		else if (commandName == "history") {//Prints the list of past commands.
			std::cout << "history\n";
		}
		else {//Run given command using execvp
			std::cout << "other command\n";

		}
	}
	return 1;
}
