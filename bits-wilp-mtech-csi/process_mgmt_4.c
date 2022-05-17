#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdio.h> 

void forkme(int n)   {   
	if(n > 0)     
         {         fork();  
	printf("forked\n");
            forkme(n-1);
	}
}                      

int main(int argc, char ** argv)  
 {  
forkme(4) ;
 }  


