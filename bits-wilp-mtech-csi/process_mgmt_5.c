// demonstrate a zombie process is created if parent doesnot wait()
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
        	perror("fork:"); // could not create child process
	else if(pid==0){
        	printf("In Child: pid = %d, parent pid= %d\n", getpid(), getppid()); // part of code that child process executes
        	printf("child finishing...\n");
        	exit(0);
	}
	else if (pid>0){// part of code that parent process executes 
		wait(NULL); // comment this line if you want to see zombie in ps aux output
		while(1);
	}
} 

