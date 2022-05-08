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

int main() {
    int sd,bindfd; // delcare sockfd
    struct sockaddr_in servaddr, clientaddr;  // server and client socket address
    char serverline[MAXLINE], clientline[MAXLINE]; // user input will be received by this variable
    socklen_t clientlinelength = sizeof(clientaddr); // size of socket address structure pointed to by clientaddr
    
    // use bzero to erase memory and set to zero
    bzero(serverline, sizeof(servaddr));
    bzero(clientline, sizeof(clientaddr));
    
    // create a UDP socket with IPv4 and datagram
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ( sd == -1 ) {
		printf("ERROR: Unable to create socket\n");
		exit(0);
    }
    else{
		printf("Socket created successfully...\n");
    } 
    
    // assign IP and PORT
    servaddr.sin_family = AF_INET; // IP_v4
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
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
    
    // Receive client's message:
    if (recvfrom(sd, clientline, sizeof(clientline), 0, (SA*)&clientaddr, &clientlinelength) < 0){
        printf("ERROR: Server couldn't receive from client\n");
        return -1;
    }
    printf("Received a message from IP: %s and port: %i\n",
           inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
    
    printf("Message from client: %s\n", clientline);
    
    // Respond to client:
    strcpy(serverline, clientline);
    
    if (sendto(sd, serverline, strlen(serverline), 0,(SA*)&clientaddr, clientlinelength) < 0){
        printf("ERROR: server can't send message to client\n");
        return -1;
    }
    
    // Close the socket:
    //close(sd);
    
    return 0;
}
