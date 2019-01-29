// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
//#define PORT    123
#define MAXLINE 1024 
  
// Driver code 
int main(int argc, char* argv[]) { 
    int sockfd; 
    char buffer[MAXLINE]; 

    memset(buffer, 0, MAXLINE);

    struct sockaddr_in servaddr, cliaddr; 

	if ( argc <= 1 )
	{
		perror("Please specify port to bind");
		return -1;
	}

	int portNo = atoi(argv[1]);
	if(portNo <= 0 || portNo >= 65535 )
	{
		perror("Invalid port");
		return -1;
	}	

	printf("Trying to bind port %d\n", portNo);
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(portNo); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

	printf("Sucessfully bound port, waiting for client...\n");
      
	socklen_t len=0, n=0; 
	while(1)
	{

		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
		buffer[n] = '\0'; 
		printf("Client : %s\n", buffer); 


		sendto(sockfd, (const char *)buffer, strlen(buffer),  
				MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
	    			len); 

	}
    return 0; 
} 
