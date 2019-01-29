// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

//#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main(int argc, char* argv[]) 
{ 
	int sockfd; 
	char buffer[MAXLINE]; 
	struct sockaddr_in	 servaddr; 

	memset(buffer, 0, MAXLINE);

	if ( argc <= 3 )
	{
		perror("Usage: client ip port message");
		return -1;
	}


	int portNo = atoi(argv[2]);
	if(portNo <= 0 || portNo >= 65535 )
	{
		perror("Invalid port");
		return -1;
	}	

	char message[256];
    	memset(message, 0, 256);	
	strncpy(message, argv[3], 256);

		
	printf("Trying to create socket\n");

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(portNo);

	 
	printf("Server address: %s\n", argv[1]);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);   //htons ntohl?
	//servaddr.sin_addr.s_addr = INADDR_ANY;
 
	
	socklen_t n, len; 


	printf("Sending message to server \n");
	
	sendto(sockfd, (const char *)message, strlen(message), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 


	printf("Sent message to server \n");
		
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("From Server : %s\n", buffer); 

	close(sockfd); 
	return 0; 
} 

