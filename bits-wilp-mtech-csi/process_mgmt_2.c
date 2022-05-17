#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdio.h> 

int  main()  
{  
	int val;
    val = 5;  
    if(fork())  
        wait(&val);  
    val++;  
    printf("%d\n", val);  
    return val;  
}  

