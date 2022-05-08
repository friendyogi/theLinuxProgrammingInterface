#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAXLINE 100
#define PORT 4321 
#define SA struct sockaddr

int str_echo(int confd)
{
    int n;
    char line[MAXLINE];

    for ( ; ; ) {
        bzero(line, MAXLINE); // use bzero to erase memory and set to zero
        read(confd, line, sizeof(line)); // take input from connection
        write(confd, line, sizeof(line)); // return the input as it is back to the connection, thus function as an "echo" server
    }
}

// Main function containing following socket functions
// Socket
// Bind
// Listen
// Accept
int main()
{
	int sd, bindfd, listenfd, confd;
	socklen_t clientlen; // size of socket address structure pointed to by clientaddr
	struct sockaddr_in servaddr, clientaddr; // serrver and client socket address

	// create a TCP socket with IPv4 and of type stream socket
	sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sd == -1) {
		printf("ERROR: Unable to create socket\n");
		exit(0);
	}
	else{
	    printf("Socket created successfully...\n");
	}
	// use bzero to erase memory and set to zero
	bzero(&servaddr, sizeof(servaddr));

	// assign IP and PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);


	// Bind local address to a socket
	// second argument is pointer to a protocol-specific address
	// third argument is the size of this address structure
	bindfd = bind(sd, (SA*)&servaddr, sizeof(servaddr));
	if (bindfd == 0) {
		printf("Socket binded successfully...\n");
	}
	else{
	    printf("ERROR: Unable to bind socket\n");
	    exit(0);
	}

	// Since we are creating a TCP socket, so we will use a listen function
	// Listen function will convert the active socket to a passive socket
	// second argument is the max number of connections
	// if I want to let only 1 client to connect, then the value of second argument will be 1
	listenfd = listen(sd, 5);
	if (listenfd == 0) {
	    printf("Socket is now listening..\n");
	}
	else{
		printf("ERROR: Socket is unable to listen \n");
		exit(0);
	}

	// Infinite "for loop" for message exchange between server and client
	for ( ; ; ) {
	    clientlen = sizeof(clientaddr);
	    confd = accept(sd, (SA*)&clientaddr, &clientlen);
	    if (confd >= 0){
    	    	printf("Server accepted the connection...\n");
    	    }
    	    else{
    		printf("ERROR: Server failed to accept connection\n");
    		exit(0);
    	    }
	    str_echo(confd); // Function
	}

	// Close the socket
	close(sd);
}
