#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int confd)
{
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(confd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("From client: %s\t To client : ", buff);
		bzero(buff, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n')
			;

		// and send that buffer to client
		write(confd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Main function containing following socket functions
// Socket
// Bind
// Listen
// Accept
int main()
{
	int sd, bindfd, listenfd, confd, len;
	struct sockaddr_in servaddr, cli;

	// create a TCP socket with IPv4 and of type stream socket
	sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sd == -1) {
		printf("ERROR: Unable to create socket\n");
		exit(0);
	}
	else{
	    printf("Socket created successfully...\n");
	}
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
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
		
	len = sizeof(cli);

	// Accept connection and return the next completed connection from the front of the completed connection queue
	confd = accept(sd, (SA*)&cli, &len);
	if (confd >= 0){
	    printf("Server accepted the connection...\n");
	}
	else{
		printf("ERROR: Server failed to accept connection\n");
		exit(0);	    
	}
		

	// Function for chatting between client and server
	func(confd);

	// Close the socket
	close(sd);
}

