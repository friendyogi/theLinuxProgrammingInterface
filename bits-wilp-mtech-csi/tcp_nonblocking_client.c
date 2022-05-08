    #include <stdio.h>
    #include <netdb.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <fcntl.h> /* Added for the nonblocking socket */    

    #define PORT 4321    /* the port users will be connecting to */
    #define MAXLINE 100 /* max number of bytes we can get at once */
    #define SA struct sockaddr

    int main(int argc, char *argv[])
    {
        int sd, numbytes;  
        char line[MAXLINE];
        struct hostent *he;
        struct sockaddr_in clientaddr; /* connector's address information */

        if (argc != 2) {
            fprintf(stderr,"usage: client hostname\n");
            exit(1);
        }

        if ((he=gethostbyname(argv[1])) == NULL) {  /* get the host info */
            herror("gethostbyname");
            exit(1);
        }

        if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        clientaddr.sin_family = AF_INET;      /* host byte order */
        clientaddr.sin_port = htons(PORT);    /* short, network byte order */
        clientaddr.sin_addr = *((struct in_addr *)he->h_addr);
        bzero(&(clientaddr.sin_zero), 8);     /* zero the rest of the struct */

        if (connect(sd, (SA *)&clientaddr, sizeof(SA)) == -1) {
            perror("connect");
            exit(1);
        }
        sleep(1); 
	while (1){
		if (send(sd, "Hello, world!\n", 14, 0) == -1)
		      perror("send");
		printf("message sent to server \n");
		sleep(1);
	}
        close(sd);

        return 0;
    }


