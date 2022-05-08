
    
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
    #define QUEUE 10     /* how many pending connections queue will hold */
    #define MAXLINE 100

int    main()
    {
        int 			sd, new_fd;  /* listen on sock_fd, new connection on new_fd */
        struct 	sockaddr_in 	servaddr;    /* my address information */
        struct 	sockaddr_in 	clientaddr; /* connector's address information */
        socklen_t		clientlen;
	char			line[MAXLINE];
	int 			n,i;
	int			last_fd;	/* Thelast sd that is connected	*/

        if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }
	
	last_fd = sd;

        servaddr.sin_family = AF_INET;         /* host byte order */
        servaddr.sin_port = htons(PORT);     /* short, network byte order */
        servaddr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
        bzero(&(servaddr.sin_zero), 8);        /* zero the rest of the struct */

        if (bind(sd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1) {
            perror("bind");
            exit(1);
        }

        if (listen(sd, QUEUE) == -1) {
            perror("listen");
            exit(1);
        }

      	if ((new_fd = accept(sd, (struct sockaddr *)&clientaddr, 	&clientlen)) == -1) {
       		perror("accept");
        			}
        fcntl(last_fd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
        fcntl(new_fd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/

	while(1){
		for (i=sd;i<=last_fd;i++){
			printf("Round number %d\n",i);
       			if (i == sd){
		 		clientlen = sizeof(struct sockaddr_in);
        			if ((new_fd = accept(sd, (struct sockaddr *)&clientaddr, &clientlen)) == -1) {
        				perror("accept");
        			}
         			printf("server: got connection from %s\n", inet_ntoa(clientaddr.sin_addr)); 
    	    			fcntl(new_fd, F_SETFL, O_NONBLOCK);
				last_fd = new_fd;
			}
			else{
	    			n=recv(new_fd,line,sizeof(line),0);
				if (n < 1){ 
					perror("recv - non blocking \n");
	    				printf("Round %d, and the data read size is: n=%d \n",i,n);
				}
				else{
			        	line[n] = '\0';
	    				printf("The string is: %s \n",line);
            				if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
                				perror("send");
				}
	    		}
		}
	}

        
    }

