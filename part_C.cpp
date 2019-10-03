#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#define MSGSIZE 256

int main()
{
	std::string strName = "Andrew Nelson\n";
	std::string strDpt = "Computer Science\n";
	std::string strMail = "nelsona9980@my.uwstout.edu";
	std::string storage;
	char* fullName = (char*) strName.c_str();
	char* department = (char*) strDpt.c_str();
	char* email = (char*) strMail.c_str();

	char inbuf[MSGSIZE];
	int p[2], pid, nbytes;

	if (pipe(p) < 0)
		exit(1);

	if ((pid = fork()) > 0) {//In parent

		close(p[1]);	//Close writing side of pipe
		dup2(p[0],0); //Change stdin to pipe
		std::getline(std::cin, storage);
		std::cout << storage << std::endl;
		std::getline(std::cin, storage);
		std::cout << storage << std::endl;
		std::getline(std::cin, storage);
		std::cout << storage << std::endl;
	}
	else if(pid ==0){
		close(p[0]);
		dup2(p[1], 1);
		std::cout << fullName;
		std::cout << department;
		std::cout << email;
		
    } 
	else{
		printf("Fork failed\n");
		exit(2);
	}
    return 0; 
}
