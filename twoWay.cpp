#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#define MSGSIZE 256

int main()
{
	std::string strName = "Andrew Nelson";
	std::string strDpt = "Computer Science";
	std::string strMail = "nelsona9980@my.uwstout.edu";
	char* fullName = (char*) strName.c_str();
	char* department = (char*) strDpt.c_str();
	char* email = (char*) strMail.c_str();

	char inbuf[MSGSIZE];
	int p[2], pid, nbytes;

	if (pipe(p) < 0)
		exit(1);

	if ((pid = fork()) > 0) {
		close(p[1]);
		while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) 
            printf("% s\n", inbuf); 
        if (nbytes != 0) 
            exit(2); 
	}
	else {
		close(p[0]);
		write(p[1], fullName, MSGSIZE);
		write(p[1], department, MSGSIZE);
		write(p[1], email, MSGSIZE); 
    }  
    return 0; 
}
