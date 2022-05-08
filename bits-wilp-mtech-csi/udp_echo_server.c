#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 100
#define PORT 4321
#define SA struct sockaddr


// Main function containing following socket functions
// Socket
// Bind
// recvfrom
// sendto	
int main() {
	int n;
	int sd,bindfd; // delcare sockfd
	struct sockaddr_in servaddr, clientaddr; // server and client socket address
	socklen_t clientlen; // size of socket address structure pointed to by clientaddr
	char line[MAXLINE]; // user input will be received by this variable
		
	// create a UDP socket with IPv4 and datagram
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sd == -1 ) {
		printf("ERROR: Unable to create socket\n");
		exit(0);
	}
	else{
		printf("Socket created successfully...\n");
	}
	// use bzero to erase memory and set to zero
	bzero(&servaddr, sizeof(servaddr));
	
		
	// assign IP and PORT
	servaddr.sin_family = AF_INET; // IPv4
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
	
	// Infinite "for loop" for message exchange between server and client

	for ( ; ; ) {
		clientlen = sizeof(clientaddr);
        	bzero(line, MAXLINE); // use bzero to erase memory and set to zero
		n = recvfrom(sd, line, MAXLINE, 0, (SA*) &clientaddr, &clientlen); // take input from connection
		sendto(sd, line, n, 0, (SA*) &clientaddr, clientlen); // return the input as it is back to the connection, thus function as an "echo" server
	}

	return 0;
}

