#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("hello parent %d \n",getpid());
	int x = fork();
	printf("hello child %d \n",x);
	if(x == 0)
	{
		printf("child process execution, pid,ppid is %d,%d \n", getpid(),getppid());
	}
	else
	{
		printf("parent process execution, pid,ppid is %d,%d \n", getpid(),getppid());
	}
}
