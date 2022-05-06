#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main()
{
	struct sockaddr_in servaddr;
	
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr)); 
    	int port; 
	char ip[256];
	printf("PLEASE INPUT TARGET PORT NUMBER: ");
	scanf("%d",&port); 
	printf("PLEASE INPUT TARGET IP: ");
	scanf("%s\n" , ip );
	
	

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr( ip );
	
	
	char hello[100000];
	while (scanf ("%[^\n]%*c", hello)){
		int len = sendto(sockfd, hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

		if(len ==-1)
		{
		perror("failed to send");
		}
	}


	close(sockfd);
	
    return 0;
}



    

	
	
	
	



    
