#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
#include <string>
#define MAX 10 
  
int main() 
{ 
  
  int fd[2], i = 0; 
  pipe(fd); 
  pid_t pid = fork(); 
  
   if(pid > 0) { 
      wait(NULL); 

		// closing the standard input  
		close(0); 

		// no need to use the write end of pipe here so close it 
		close(fd[1]);  

		// duplicating fd[0] with standard input 0 
		dup(fd[0]);  
		char* info[MAX]; 

		// n stores the total bytes read succesfully 
		int n = read(fd[0], info, sizeof(info)); 
		for ( i = 0;i < n/4; i++) 

		// printing the array received from child process 
		printf("%s ", info[i]);  
  }  
  else if( pid == 0 ) { 
		//Inside child process, pass strings back to parent.
		char* info[3];
		std::string strName = "Andrew Nelson";
		std::string strDpt = "Computer Science";
		std::string strMail = "nelsona9980@my.uwstout.edu";
		info[0] = (char*) strName.c_str();
		info[1] = (char*) strDpt.c_str();
		info[3]= (char*) strMail.c_str();
  
		// no need to use the read end of pipe here so close it 
		close(fd[0]);  

		// closing the standard output 
		close(1);     

		// duplicating fd[0] with standard output 1 
		dup(fd[1]);   
		write(1, info, sizeof(info)); 
  }  
  
  else { 
      perror("error\n"); //fork() 
  } 
}  
