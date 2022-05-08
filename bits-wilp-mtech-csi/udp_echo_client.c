#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define MAXLINE 100
#define PORT	 4321
#define SA struct sockaddr
	
int main() {
	int sd,n,linelen;
	char line[MAXLINE], recvline[MAXLINE +1]; //user input will be received by this variable
	struct sockaddr_in servaddr, clientaddr; // server and client socket address
	socklen_t clientlen; // size of socket address structure pointed to by clientaddr
	
	// create a UDP socket with IPv4 and of type DATAGRAM
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		printf("ERROR: Unable to create socket\n");
	}
	else{
		printf("Socket created successfully...\n");
	}
	// use bzero to erease memory and set to zero
	bzero(&servaddr, sizeof(servaddr));
	
	// assign IP and PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // we are using localhost here for simplicity

	int k ;
	for (;;) {
		bzero(line,sizeof(line));
		printf("Enter a string : ");
		k = 0;
		while ((line[n++] = getchar()) != '\n')
			;
		clientlen = sizeof(clientaddr);
		linelen = strlen(line);
		sendto(sd, line, linelen ,0, (SA*) &servaddr,sizeof(servaddr));
		bzero(line, sizeof(line));
		n = recvfrom(sd, recvline, MAXLINE, 0, (SA*) &servaddr,&clientlen);
		printf("From Server : %s", line);
		// compare the strings, if line == exit, compare first 4 characters
		// when client exits the c program execution, the value of line == exit
		if ((strncmp(line, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}	
	
	close(sd);
	return 0;
}

