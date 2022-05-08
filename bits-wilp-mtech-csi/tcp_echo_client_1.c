#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void func(int sd)
{
	char line[MAX];
	int n;
	for (;;) {
		bzero(line, sizeof(line));
		printf("Enter a string : ");
		n = 0;
		while ((line[n++] = getchar()) != '\n')
			;
		write(sd, line, sizeof(line)); // send the line/string to socket
		bzero(line, sizeof(line));
		read(sd, line, sizeof(line)); // read the line/string from the socket
		printf("From Server : %s", line);
		// compare the strings, if line == exit, compare first 4 characters
		// when client exits the c program execution, the value of line == exit
		if ((strncmp(line, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main()
{
	int sd, connfd;
	struct sockaddr_in servaddr, cliaddr;

	// create a TCP socket with IPv4 and of type stream socket
	//sd = socket(AF_INET, SOCK_STREAM, 0);
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
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // we are using localhost here for simplicity
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sd);

	// close the socket
	close(sd);
}
