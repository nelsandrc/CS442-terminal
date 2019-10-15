#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <type_traits>
#include <fcntl.h>
#define MAX_SIZE 256

void changeIO(int io, char* file);
void printHistory(std::vector<std::string> history);
void runCommand(std::string userSelection);
void runPipe(std::string userSelection);


int main(){
	std::string userSelection = "";
	std::string commandName = "";
	std::vector <std::string> history;
	bool isPipe = false;
	bool cont = true;
	
	std::cout << "Starting terminal program. Type helpME for nonstandard command list.\n"
			  << "Enter all one token commands with a trailing space.\n";
	while (cont == true ) {
		std::cout << ">";
		std::getline(std::cin, userSelection);
		commandName = userSelection.substr(0, userSelection.find(" "));
		history.push_back(userSelection);
		isPipe = (userSelection.find('|') != std::string::npos); //Determines if command includes a pipe for different handling.
		
		if(isPipe){
			runPipe(userSelection);
		}
		else if (commandName == "exit" || commandName == "Exit") {//Ends the terminal program.
			std::cout << "Terminal closing now.\n";
			cont = false;	
			exit(0);

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

void runPipe(std::string userSelection){
	int splitIndex = userSelection.find('|');
	std::string firstCommand = userSelection.substr(0,splitIndex);
	std::string secondCommand = userSelection.substr(splitIndex+1);
	std::cout << "First command: " << firstCommand << "\nSecond command: " << secondCommand << std::endl;

	int p[2], pid, nbytes;

	if (pipe(p) < 0)
		exit(1);
	pid = fork();
	if (pid == 0){
		runCommand(firstCommand);
		
	}
	else {
		wait(0);
	}
	pid = fork();
	if (pid == 0){
		runCommand(secondCommand);
	}
	else {
		wait(0);
	}
}

void printHistory(std::vector<std::string> history){
	std::cout << "History: \n";
			for(int i = 0; i < history.size(); i++){
				std::cout << i+1 << ":  " << history[i] << std::endl;
			}
}

void runCommand(std::string userSelection){
	int originIN = dup(0);
	int originOUT = dup(1);
	int size = userSelection.length(); // Size to make char array
    char charArray[size + 1]; // char array
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
            if (temp[0] == '<') {
				std::string word(temp.begin() + 1, temp.end());
				changeIO(0,(char*)word.c_str());
			} else if (temp[0] == '>') {
				std::string word(temp.begin() + 1, temp.end());
				changeIO(1,(char*)word.c_str());
			} else {
				std::string word(temp.begin(), temp.end());
            	tokens.push_back(word);
			}
            temp.clear();
        } // If not space, store it in temp 
        else if (charArray[j] != ' '){
            temp.push_back(charArray[j]);
        }
    }
    // c_string array final answer
    char* a[tokens.size() + 1];
	a[tokens.size()] = NULL;
    for (int l = 0; l < tokens.size(); l++) {
        a[l] = (char*) tokens[l].c_str();
    }
	
	int pid = fork();

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
		dup2(originIN, 0);
		dup2(originOUT, 1);
		//cout<<"I am the parent :)\n";   
	}
}

void changeIO(int io, char* file) {
    int fd;
    // If changing input
    if (io == 0) {
        fd = open(file, O_RDONLY);
    } else if (io == 1) {
        fd = open(file, O_WRONLY | O_APPEND);
    } 
	else {
        std::cout << "Invalid io value" << std::endl;
        return;
    }
    if (fd < 0) {
        std::cout << "Can not open the file" << std::endl;
       return;
    }
    dup2(fd,io);
    close(fd);
}
