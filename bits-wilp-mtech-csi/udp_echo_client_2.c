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

int main(){
    int sd;
    struct sockaddr_in servaddr; // server and client socket address
    char serverline[MAXLINE], clientline[MAXLINE];
    socklen_t serverlinelen = sizeof(servaddr);
    
    // use bzero to erase memory and set to zero
    bzero(serverline, sizeof(serverline));
    bzero(clientline, sizeof(clientline));
 
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
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Take user input:
    printf("Enter message: ");
    gets(clientline);
    
    // Send it to server:
    if(sendto(sd, clientline, strlen(clientline), 0,(SA*)&servaddr, serverlinelen) < 0){
        printf("ERROR: Unable to send message\n");
        return -1;
    }
    
    // Receive the server's response:
    if(recvfrom(sd, serverline, sizeof(serverline), 0,(SA*)&servaddr, &serverlinelen) < 0){
        printf("ERROR: unable to receive server's msg\n");
        return -1;
    }
    
    printf("Response from server: %s\n", serverline);
    
    // Close the socket:
    // close(sd);
    
    return 0;
}

