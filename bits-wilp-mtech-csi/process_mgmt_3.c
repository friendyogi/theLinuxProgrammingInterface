#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdio.h> 

int   main()  
{  
	int pid1,pid2;  
        printf("FIRST\n");    
 pid1=fork();  
      if(pid1==0) {  
            printf("SECOND \n");    
      pid2=fork();  
             printf("SECOND \n");  
    }  else   {     
        printf("THIRD\n");  
      }  
} 

