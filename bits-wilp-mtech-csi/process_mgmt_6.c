// demonstrate orphan child process is sleeping while the parent process has exited
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h>

int main()
{
	pid_t pid;
	pid = getpid();
	printf("Current process ID is: %d\n", pid);
	printf("Forking the child process... \n");
	pid=fork();
	if(pid<0)
        	perror("fork:"); // could not create child process
	else if(pid==0){
        	printf("In Child: pid = %d, parent pid= %d\n", getpid(), getppid()); // part of code that child process executes
		printf("Child process is sleeping...\n");
		sleep(5);
	}
	else if (pid>0){// part of code that parent process executes 
		printf("Parent process completed...\n");
	}
	return 0;
} 

