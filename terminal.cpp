#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#define MAX_SIZE 256

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
			char cwd[MAX_SIZE];
			
			getcwd(cwd, sizeof(cwd));
			
			std::cout <<  "Current working dir: " << cwd << std::endl;
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
			/*pid_t  pid;  
			char * commandString[3];

			string command="commandName";   // this is the ls unix command
			string argument1="-l";  // this is an argument for the ls

			commandString[0]=(char*) command.c_str();  //this is how to conver a string variable to a c_string
			commandString[1]=(char*) argument1.c_str();       
			commandString[2]=NULL;

			 pid = fork();

			 if (pid == 0) { // a child was created and you are inside it J

					if (execvp(commandString[0], commandString) < 0) {    // try to change the execution impage of the child
						//here using the execvp, the impage of execution will be replaced for the child by: ls -l. 
						//If it returns a negative value, that means something went wrong
						cout<<"*** ERROR: exec failed\n";     
						exit(1);
					}
				cout<<"A New Child was created J \n";  // will not execute this line since  //image of execution has been changed by execvp system call
			 } 
			 else if (pid < 0)   {   // no new child was created (fail)
					cout<<"No New Child Was created L\n"; 
					return 1;
			}
			else // must be the parent
			{  
				wait(0); // must wait for a child to finish
				//cout<<"I am the parent :)\n";   
			}
*/
		}





	}
	return 1;
}
