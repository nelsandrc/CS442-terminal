#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <type_traits>
#define MAX_SIZE 256

void printHistory(std::vector<std::string> history);
void runCommand(std::string userSelection);


int main(){
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
    int size = userSelection.length(); // Size to make char array
    char charArray[50]; // char array
    strcpy(charArray, userSelection.c_str()); // setting char array to string
    // Iterate over array to get rid of escape sequences
    // Normalizes all unwanted chars
    for (int i = 0; i < size +1; i++) {
        if (charArray[i] == '\\') {
            charArray[i] = ' ';
            charArray[i + 1] = ' ';
        }
    }
    std::vector<char> temp; // Vector to store the word
    std::vector<std::string> tokens; // Vector to store tokens
    for (int j = 0; j < size + 1; j++) {
        // If the character is a space and temp is NOT empty
        // Or if j is at the end of the charArray and temp is NOT empty
        // Store temp into tokens and clear temp
        if (((charArray[j] == ' ') && (temp.size() != 0)) || ((j == size) && (temp.size() != 0))) {
            std::string word(temp.begin(), temp.end());
            tokens.push_back(word);
            temp.clear();
        } // If not space, store it in temp 
        else if (charArray[j] != ' '){
            temp.push_back(charArray[j]);
        }
    }
    // c_string array final answer
	int tsize = tokens.size();
    char *a[50];
	a[tsize] = NULL;
    for (int l = 0; l < tsize; l++) {
        strcpy(a[l],tokens[l].c_str());
    }
	
	 pid = fork();

	 if (pid == 0) { // a child was created and you are inside it J
		if (execvp(a[0], a) < 0) {    // try to change the execution impage of the child
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
