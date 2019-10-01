#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#define MAX_SIZE 256

void printHistory(std::vector<std::string> history);
void runCommand(std::string userSelection);


int main()
{
	std::string userSelection = "";
	std::string commandName = "";
	std::vector <std::string> history;
	
	std::cout << "Starting terminal program. Type helpME for nonstandard command list.\n"
			  << "Enter all one token commands with a trailing space.\n";
	while (true) {
		std::cout << ">";
		std::getline(std::cin, userSelection);
		commandName = userSelection.substr(0, userSelection.find(" "));
		history.push_back(userSelection);

		if (commandName == "exit" || commandName == "Exit") {//Ends the terminal program.
			std::cout << "Terminal closing now.\n";
			return 0;

		}
		else if (commandName == "pwd") {//Prints the current working directory.
			char cwd[MAX_SIZE];
			
			getcwd(cwd, sizeof(cwd));
			
			std::cout <<  "Current working dir: " << cwd << std::endl;
		}
		else if (commandName == "helpME") {//Print the command list of nonstandard commands.
			std::cout << "Command List:\n"
					  << "1: history- Prints the list of past commands.\n";
		}
		else if (commandName == "history") {//Prints the list of past commands.
			printHistory(history);
		}
		else {//Run given command using execvp
			runCommand(userSelection);
		}
	}
	return 1;
}

void printHistory(std::vector<std::string> history){
	std::cout << "History: \n";
			for(int i = 0; i < history.size(); i++){
				std::cout << i+1 << ":  " << history[i] << std::endl;
			}
}

void runCommand(std::string userSelection){
	pid_t  pid;  
	std::vector<char*> tokenizedString;		
	char* cstring_conversion = new char[userSelection.length() + 1];

	std::strcpy(cstring_conversion, userSelection.c_str());

	char* currentToken = std::strtok(cstring_conversion, " \n\t\r");
	
	while (currentToken != nullptr) {
		tokenizedString.push_back(currentToken);
		currentToken = std::strtok(NULL, " ,\n\t\r.");
	}

	for (int i = 0; i < tokenizedString.size(); ++i) {
		std::cout << tokenizedString[i] << std::endl;
	}
	// INITIALIZE VARIABLES
	char * commandString[3];
	std::string command= tokenizedString[0];   // this is the ls unix command
	std::string argument1= tokenizedString[1];  // this is an argument for the ls

	commandString[0]=(char*) command.c_str();  //this is how to conver a string variable to a c_string
	commandString[1]=(char*) argument1.c_str();       
	commandString[2]=NULL;

	 pid = fork();

	 if (pid == 0) { // a child was created and you are inside it J

			if (execvp(commandString[0], commandString) < 0) {    // try to change the execution impage of the child
				//here using the execvp, the impage of execution will be replaced for the child by: ls -l. 
				//If it returns a negative value, that means something went wrong
				std::cout<<"*** ERROR: exec failed\n";     
				exit(1);
			}
		std::cout<<"A New Child was created J \n";  // will not execute this line since  //image of execution has been changed by execvp system call
	 } 
	 else if (pid < 0)   {   // no new child was created (fail)
			std::cout<<"No New Child Was created L\n"; 
	}
	else // must be the parent
	{  
		wait(0); // must wait for a child to finish
		//cout<<"I am the parent :)\n";   
	}
}

