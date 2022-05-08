#include <stdio.h>
#include <unistd.h>

int main()										
{
     fork();
     fork();
     fork();
     fork();
     fork();
     printf("in main\n");
     return 0;
}

